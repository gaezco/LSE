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
 *  Header file for Mouse.c.
 */

#ifndef _MOUSE_H_
#define _MOUSE_H_

	/* Includes: */


		#include "touchPanel.h"
		#include "lpc17xx_gpio.h"
		#include "USB.h"

		#include <stdbool.h>
		#include <string.h>

		#include "Descriptors.h"

	/* Macros: */
		/** LED mask for the library LED driver, to indicate that the USB interface is not ready. */
		#define LEDMASK_USB_NOTREADY      LEDS_LED1

		/** LED mask for the library LED driver, to indicate that the USB interface is enumerating. */
		#define LEDMASK_USB_ENUMERATING  (LEDS_LED2 | LEDS_LED3)

		/** LED mask for the library LED driver, to indicate that the USB interface is ready. */
		#define LEDMASK_USB_READY        (LEDS_LED2 | LEDS_LED4)

		/** LED mask for the library LED driver, to indicate that an error has occurred in the USB interface. */
		#define LEDMASK_USB_ERROR        (LEDS_LED1 | LEDS_LED3)


		#define USB_CONNECT_GPIO_PORT_NUM			0
		#define USB_CONNECT_GPIO_BIT_NUM			21

		#define JOY_UP				0x01
		#define JOY_DOWN			0x02
		#define JOY_LEFT			0x04
		#define JOY_RIGHT			0x08
		#define JOY_PRESS			0x10
		#define NO_BUTTON_PRESSED	0x00
		#define BUTTONS_BUTTON1 	0x01

		/**
		 * Deprecated functions, used for compatible only
		 */
		#define sei()
		#define puts_P(x)		puts(x)
		#define PSTR(x)			x
		#define printf_P		printf

	/* Function Prototypes: */
		void Mouse_Device(void);
		void SetupHardware(void);
		void USB_Connect(void);
		void EVENT_USB_Device_Connect(void);
		void EVENT_USB_Device_Disconnect(void);
		void EVENT_USB_Device_ConfigurationChanged(void);
		void EVENT_USB_Device_ControlRequest(void);
		void EVENT_USB_Device_StartOfFrame(void);

		bool CALLBACK_HID_Device_CreateHIDReport(USB_ClassInfo_HID_Device_t* const HIDInterfaceInfo,
		                                         uint8_t* const ReportID,
		                                         const uint8_t ReportType,
		                                         void* ReportData,
		                                         uint16_t* const ReportSize);
		void CALLBACK_HID_Device_ProcessHIDReport(USB_ClassInfo_HID_Device_t* const HIDInterfaceInfo,
		                                          const uint8_t ReportID,
		                                          const uint8_t ReportType,
		                                          const void* ReportData,
		                                          const uint16_t ReportSize);
		uint8_t Joystick_GetStatus(void);
		uint32_t Buttons_GetStatus(void);
#endif

