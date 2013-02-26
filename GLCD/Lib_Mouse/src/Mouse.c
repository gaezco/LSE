/*
* Copyright(C) NXP Semiconductors, 2012
* All rights reserved.
*
* Software that is described herein is for illustrative purposes only
* which provides customers with programming information regarding the
* LPC products.  This software is supplied "AS IS" without any warranties of
* any kind, and NXP Semiconductors and its licensor disclaim any and
* all warranties, express or implied, including all implied warranties of
* merchantability, fitness for a particular purpose and non-infringement of
* intellectual property rights.  NXP Semiconductors assumes no responsibility
* or liability for the use of the software, conveys no license or rights under any
* patent, copyright, mask work right, or any other intellectual property rights in
* or to any products. NXP Semiconductors reserves the right to make changes
* in the software without notification. NXP Semiconductors also makes no
* representation or warranty that such application will be suitable for the
* specified use without further testing or modification.
*
* Permission to use, copy, modify, and distribute this software and its
* documentation is hereby granted, under NXP Semiconductors' and its
* licensor's relevant copyrights in the software, without fee, provided that it
* is used in conjunction with NXP Semiconductors microcontrollers.  This
* copyright, permission, and disclaimer notice must appear in all copies of
* this code.
*/

/** \file
 *
 *  Main source file for the Mouse demo. This file contains the main tasks of
 *  the demo and is responsible for the initial application hardware configuration.
 */

#include "Mouse.h"

/** Buffer to hold the previously generated Mouse HID report, for comparison purposes inside the HID class driver. */
static uint8_t PrevMouseHIDReportBuffer[sizeof(USB_MouseReport_Data_t)];

/** LPCUSBlib HID Class driver interface configuration and state information. This structure is
 *  passed to all HID Class driver functions, so that multiple instances of the same class
 *  within a device can be differentiated from one another.
 */
USB_ClassInfo_HID_Device_t Mouse_HID_Interface =
	{
		.Config =
			{
				.InterfaceNumber              = 0,

				.ReportINEndpointNumber       = MOUSE_EPNUM,
				.ReportINEndpointSize         = MOUSE_EPSIZE,
				.ReportINEndpointDoubleBank   = false,

				.PrevReportINBuffer           = PrevMouseHIDReportBuffer,
				.PrevReportINBufferSize       = sizeof(PrevMouseHIDReportBuffer),
			},
	};
#if defined(USB_DEVICE_ROM_DRIVER)
extern void CALLBACK_UsbdHid_SetReportChange(bool newstate);
#endif
/** Main program entry point. This routine contains the overall program flow, including initial
 *  setup of all components and the main program loop.
 */
void Mouse_Device(void)
{
	SetupHardware();

	sei();

	for (;;)
	{
		#if defined(USB_DEVICE_ROM_DRIVER)
		USB_MouseReport_Data_t report;
		uint16_t reportsize;
		uint8_t reportID = 0;

		memset(&report, 0, sizeof(USB_MouseReport_Data_t));
		CALLBACK_HID_Device_CreateHIDReport(&Mouse_HID_Interface,&reportID,HID_REPORT_ITEM_In,&report,&reportsize);
		if(memcmp(&report, Mouse_HID_Interface.Config.PrevReportINBuffer, Mouse_HID_Interface.Config.PrevReportINBufferSize))
		{
			memcpy(Mouse_HID_Interface.Config.PrevReportINBuffer,&report,Mouse_HID_Interface.Config.PrevReportINBufferSize);
			CALLBACK_UsbdHid_SetReportChange(true);
		}
		#else
		HID_Device_USBTask(&Mouse_HID_Interface);
		USB_USBTask();
		#endif
	}
}

/** Configures the board hardware and chip peripherals for the demo's functionality. */
void SetupHardware(void)
{
	USB_Init();
#if defined(USB_DEVICE_ROM_DRIVER)
	UsbdHid_Init();
#endif
	USB_Connect();
}

void USB_Connect(void)
{
#ifdef __LPC17XX__
	GPIO_SetDir(USB_CONNECT_GPIO_PORT_NUM,(1<<USB_CONNECT_GPIO_BIT_NUM),1);				//output
	GPIO_ClearValue(USB_CONNECT_GPIO_PORT_NUM,(1<<USB_CONNECT_GPIO_BIT_NUM));			//pull up D+
#endif
}

/** Event handler for the library USB Configuration Changed event. */
void EVENT_USB_Device_ConfigurationChanged(void)
{
	bool ConfigSuccess = true;

	ConfigSuccess &= HID_Device_ConfigureEndpoints(&Mouse_HID_Interface);

	USB_Device_EnableSOFEvents();

//	LEDs_SetAllLEDs(ConfigSuccess ? LEDMASK_USB_READY : LEDMASK_USB_ERROR);
}

/** Event handler for the library USB Control Request reception event. */
void EVENT_USB_Device_ControlRequest(void)
{
	HID_Device_ProcessControlRequest(&Mouse_HID_Interface);
}

/** Event handler for the USB device Start Of Frame event. */
void EVENT_USB_Device_StartOfFrame(void)
{
	HID_Device_MillisecondElapsed(&Mouse_HID_Interface);
}

/** HID class driver callback function for the creation of HID reports to the host.
 *
 *  \param[in]     HIDInterfaceInfo  Pointer to the HID class interface configuration structure being referenced
 *  \param[in,out] ReportID    Report ID requested by the host if non-zero, otherwise callback should set to the generated report ID
 *  \param[in]     ReportType  Type of the report to create, either HID_REPORT_ITEM_In or HID_REPORT_ITEM_Feature
 *  \param[out]    ReportData  Pointer to a buffer where the created report should be stored
 *  \param[out]    ReportSize  Number of bytes written in the report (or zero if no report is to be sent
 *
 *  \return Boolean true to force the sending of the report, false to let the library determine if it needs to be sent
 */
bool CALLBACK_HID_Device_CreateHIDReport(USB_ClassInfo_HID_Device_t* const HIDInterfaceInfo,
                                         uint8_t* const ReportID,
                                         const uint8_t ReportType,
                                         void* ReportData,
                                         uint16_t* const ReportSize)
{
	USB_MouseReport_Data_t* MouseReport = (USB_MouseReport_Data_t*)ReportData;

	uint8_t JoyStatus_LCL    = Joystick_GetStatus();
	uint8_t ButtonStatus_LCL = Buttons_GetStatus();

	if (JoyStatus_LCL & JOY_UP)
	  MouseReport->Y = -1;
	else if (JoyStatus_LCL & JOY_DOWN)
	  MouseReport->Y =  1;

	if (JoyStatus_LCL & JOY_LEFT)
	  MouseReport->X = -1;
	else if (JoyStatus_LCL & JOY_RIGHT)
	  MouseReport->X =  1;

	if (JoyStatus_LCL & JOY_PRESS)
	  MouseReport->Button |= (1 << 0);

	if (ButtonStatus_LCL & BUTTONS_BUTTON1)
	  MouseReport->Button |= (1 << 1);

	*ReportSize = sizeof(USB_MouseReport_Data_t);
	return true;
}

/** HID class driver callback function for the processing of HID reports from the host.
 *
 *  \param[in] HIDInterfaceInfo  Pointer to the HID class interface configuration structure being referenced
 *  \param[in] ReportID    Report ID of the received report from the host
 *  \param[in] ReportType  The type of report that the host has sent, either HID_REPORT_ITEM_Out or HID_REPORT_ITEM_Feature
 *  \param[in] ReportData  Pointer to a buffer where the received report has been stored
 *  \param[in] ReportSize  Size in bytes of the received HID report
 */
void CALLBACK_HID_Device_ProcessHIDReport(USB_ClassInfo_HID_Device_t* const HIDInterfaceInfo,
                                          const uint8_t ReportID,
                                          const uint8_t ReportType,
                                          const void* ReportData,
                                          const uint16_t ReportSize)
{
	// Unused (but mandatory for the HID class driver) in this demo, since there are no Host->Device reports
}

uint8_t Joystick_GetStatus(void)
{

/*
  	uint8_t ret = NO_BUTTON_PRESSED;
 	uint16_t x, y, x1, y1;
	uint16_t i;
	// Start the Touch Panel Library
	StartTouchPanel ();

	// Configuration of the external interrupt
	ConfigExternalInterrupt ();

	// Start the ADC
	ADC_Init (LPC_ADC, 100000);

	Task_TouchPanel(&x, &y);
	for (i=0; i < 1000; i++);
	Task_TouchPanel(&x1, &y1);

	if( (y1 > y+10) & ( ((x1 - x)^2) < 100) )
	{
		ret |= JOY_UP;
	}
	else if( (y1 < y-10) & ( ((x1 - x)^2) < 100) )
	{
		ret |= JOY_DOWN;
	}
	else if( (x1 < x-10) & ( ((y1 - y)^2) < 100) )
	{
		ret |= JOY_LEFT;
	}
	else if( (x1 > x+10) & ( ((y1 - y)^2) < 100) )
	{
		ret |= JOY_RIGHT;
	}
	else if( ( ((x1 - x)^2) < 100) & ( ((y1 - y)^2) < 100) )
	{
		ret |= JOY_PRESS;
	}

*/


/*
	if((GPIO_ReadValue(JOYSTICK_UP_GPIO_PORT_NUM) & (1<<JOYSTICK_UP_GPIO_BIT_NUM)) == 0x00)
	{
		ret |= JOY_UP;
	}
	else if((GPIO_ReadValue(JOYSTICK_DOWN_GPIO_PORT_NUM) & (1<<JOYSTICK_DOWN_GPIO_BIT_NUM)) == 0x00)
	{
		ret |= JOY_DOWN;
	}
	else if((GPIO_ReadValue(JOYSTICK_LEFT_GPIO_PORT_NUM) & (1<<JOYSTICK_LEFT_GPIO_BIT_NUM)) == 0x00)
	{
		ret |= JOY_LEFT;
	}
	else if((GPIO_ReadValue(JOYSTICK_RIGHT_GPIO_PORT_NUM) & (1<<JOYSTICK_RIGHT_GPIO_BIT_NUM)) == 0x00)
	{
		ret |= JOY_RIGHT;
	}
	else if((GPIO_ReadValue(JOYSTICK_PRESS_GPIO_PORT_NUM) & (1<<JOYSTICK_PRESS_GPIO_BIT_NUM)) == 0x00)
	{
		ret |= JOY_PRESS;
	}
*/
	return JOY_LEFT;
}

uint32_t Buttons_GetStatus(void)
{
	uint8_t ret = NO_BUTTON_PRESSED;

	///ALGO!!!!!!!!!!!
	return ret;

}
