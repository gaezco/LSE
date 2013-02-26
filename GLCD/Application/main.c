/*
   ********************* Authors *********************
   ***** Laboratorio de Sistemas Embebidos (LSE) *****
   *****    http://laboratorios.fi.uba.ar/lse    *****
   ******************* 20/12/2011 ********************
     Ezequiel Espósito <ezequiel.esposito@gmail.com>
         Alan Kharsansky <akharsa@gmail.com>
       Federico Roasio <federoasio@gmail.com>
     Daniel Schermuk <daniel.schermuk@gmail.com>
   ***************************************************
   *****************  Modificacion  ******************
   ******************* 22/02/2013 ********************
			Gaston Conessa <gaezco@gmail.com>
		Hernan Barrios <barrioshernan@hotmail.com>
   ***************************************************
*/

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#include "GLCDLowLevel.h"
#include "MicroInterface.h"
#include "lpc17xx_gpio.h"
#include "lpc17xx_pinsel.h"
#endif



#include "definitions.h"
uint8_t chkText5, chkText6;

int main( void )
{
	// Start the Graphic User Interface Library
	StartGUI ();

	// Build the graphic interface and start the GLCD
	GLCD_ClearText();
	CreateGUI ();

	// Create FreeRTOS Semaphores
	vSemaphoreCreateBinary (semaphore_TouchInterrupt);

	// Start the Touch Panel Library
	StartTouchPanel ();

	// Configuration of the external interrupt
	ConfigExternalInterrupt ();

	// Start the ADC
	CAD_Inicializacion ( 200000 );

	// Create the task
	xTaskCreate (Task_TouchPanel, "Task_GLCD", 300, NULL, 1, NULL);

   	// Start the scheduler of FreeRTOS
	vTaskStartScheduler();

	for( ;; );

	return 0;
}

void StartGUI ()
{
	GUI_DefineHeapMalloc ( pvPortMalloc );
	GUI_DefineHeapFree ( vPortFree );
	GUI_StartLibrary ();
}

void CreateGUI ()
{


	// Window "Home"
	GUI_Window_Create ( "Home", "None", WHITE, "Home", NULL, NULL, NULL );
	GUI_Text_Create ( "Home", "txtAp1", 150, 60, WHITE, "", BLACK, "FIUBA" );
	GUI_Text_Create ( "Home", "txtAp2", 150, 80, WHITE, "", BLACK, " LSE " );
	GUI_Text_Create ( "Home", "txtAp3", 125, 100 , WHITE, "", BLACK, "GLCD Library" );
	GUI_Button_Create ( "Home", "btnHome1", 20, 75, 125, 135, BLACK, "", WHITE, "Settings",
						wndHome_btnSettings_OnClik, NULL, NULL, NULL );
	GUI_Button_Create ( "Home", "btnHome2", 20, 75, 125, 175, BLACK, "", WHITE, "Credits",
						wndHome_btnCredits_OnClik, NULL, NULL, NULL );
	GUI_Picture_Create ( "Home", "picFiuba1", 5, 16, 35, 40, fiuba, BLACK,
						wndHome_btnCredits_OnClik );


	// Window "Credits"
	GUI_Window_Create ( "Credits", "Home", WHITE, "Credits", NULL, NULL, NULL );
	GUI_Text_Create ( "Credits", "txtInfo1", 100, 40, WHITE, "", BLACK,  " Ezequiel Esposito " );
	GUI_Text_Create ( "Credits", "txtInfo2", 100, 60, WHITE, "", BLACK,  "  Alan Kharsansky  " );
	GUI_Text_Create ( "Credits", "txtInfo3", 100, 80, WHITE, "", BLACK,  "  Daniel Schermuk  " );
	GUI_Text_Create ( "Credits", "txtInfo4", 100, 100, WHITE, "", BLACK, "  Federico Roasio  " );
	GUI_Text_Create ( "Credits", "txtInfo5", 100, 120, WHITE, "", BLACK, "  Gaston Conessa   " );
	GUI_Text_Create ( "Credits", "txtInfo6", 100, 140, WHITE, "", BLACK, "  Hernan Barrios  " );
	GUI_Check_Create ( "Credits", "btnCheck5", 10, 10, 200, 120, BLACK, "", WHITE, OFF,
							wndCredits_chkText5_OnClik, NULL, NULL, NULL );
	GUI_Check_Create ( "Credits", "btnCheck6", 10, 10, 200, 140, BLACK, "", WHITE, OFF,
						wndCredits_chkText6_OnClik, NULL, NULL, NULL );
	GUI_Button_Create ( "Credits", "btnData", 20, 75, 115, 170, BLACK, "", WHITE, "Ver Datos",
							wndCredits_btnData_OnClik, NULL, NULL, NULL );
	GUI_Button_Create ( "Credits", "btnBack1", 20, 75, 115, 210, BLACK, "", WHITE, "Back",
						wndCredits_btnBack_OnClik, NULL, NULL, NULL );
	chkText5 = OFF;
	chkText6 = OFF;

	// Window "Menu"
	GUI_Window_Create ( "Menu", "Home", WHITE, "Menu", NULL, NULL, NULL );
	GUI_Button_Create ( "Menu", "btnMouse", 20, 75, 120, 50, BLACK, "", WHITE, "Mouse",
						wndMenu_btnMouse_OnClik, NULL, NULL, NULL );
	GUI_Button_Create ( "Menu", "btnTeclado", 20, 75, 120, 100, BLACK, "", WHITE, "Teclado",
						wndMenu_btnTeclado_OnClik, NULL, NULL, NULL );
	GUI_Button_Create ( "Menu", "btnBack2", 20, 75, 120, 180, BLACK, "", WHITE, "Back",
						wndMenu_btnBack_OnClik, NULL, NULL, NULL );

	// Window "Mouse"
	GUI_Window_Create ( "Mouse", "Menu", WHITE, "Mouse", NULL, NULL, NULL );
	GUI_Button_Create ( "Mouse", "Izquierdo", 30, 100, 20, 210, BLACK, "", WHITE, "IZQ",
						wndMouse_btnChange_OnClik, NULL, NULL, NULL );
	GUI_Button_Create ( "Mouse", "Derecho", 30, 100, 200, 210, BLACK, "", WHITE, "DER",
								wndMouse_btnChange_OnClik, NULL, NULL, NULL );
	GUI_Button_Create ( "Mouse", "btnBack5", 20, 50, 135, 220, BLACK, "", WHITE, "Back",
						wndMouse_btnBack_OnClik , NULL, NULL, NULL );


	// Window "Teclado"
	GUI_Window_Create ( "Teclado", "Menu", WHITE, "Teclado" ,NULL, NULL, NULL );

	GUI_Button_Create ( "Teclado", "btnBack4", 20, 50, 135, 220, BLACK, "", WHITE, "Back",
						wndTeclado_btnBack_OnClik, NULL, NULL, NULL );

	GUI_Window_Draw ( "Home" );


	// Window "DATA1"
	GUI_Window_Create ( "Data1", "Credits", WHITE, "Datos", NULL, NULL, NULL );
	GUI_Text_Create ( "Data1", "txtInfo1", 25, 40, WHITE, "", BLACK,     " Gaston Conessa  " );
	GUI_Text_Create ( "Data1", "txtInfo2", 25, 60, WHITE, "", BLACK,  "    Paron: 88103  " );
	GUI_Text_Create ( "Data1", "txtInfo3", 25, 80, WHITE, "", BLACK,  "    Email: gaezco@gmail.com  " );
	GUI_Button_Create ( "Data1", "btnBack1", 20, 75, 115, 180, BLACK, "", WHITE, "Back",
						wndData_btnBack_OnClik, NULL, NULL, NULL );

	// Window "DATA1"
	GUI_Window_Create ( "Data2", "Credits", WHITE, "Datos", NULL, NULL, NULL );
	GUI_Text_Create ( "Data2", "txtInfo1", 25, 40, WHITE, "", BLACK,     " Hernan Barrios  " );
	GUI_Text_Create ( "Data2", "txtInfo2", 25, 60, WHITE, "", BLACK,  "    Padron: 85979 " );
	GUI_Text_Create ( "Data2", "txtInfo3", 25, 80, WHITE, "", BLACK,  "    Email: barrioshernan@hotmail.com " );
	GUI_Button_Create ( "Data2", "btnBack1", 20, 75, 115, 180, BLACK, "", WHITE, "Back",
						wndData_btnBack_OnClik, NULL, NULL, NULL );
}

void wndHome_btnSettings_OnClik ( void* parameter )
{
	GUI_Window_Draw ( "Menu" );
}

void wndHome_btnCredits_OnClik ( void* parameter )
{
	GUI_Window_Draw ( "Credits" );
}

void wndCredits_btnBack_OnClik ( void* parameter )
{
	GUI_Window_Draw ( "Home" );
}

void wndMenu_btnMouse_OnClik( void* parameter )
{
	GUI_Window_Draw ( "Mouse" );
	Mouse_Device();
}

void wndMenu_btnTeclado_OnClik ( void* parameter )
{
	GUI_Window_Draw ( "Teclado" );
}

void wndMenu_btnBack_OnClik ( void* parameter )
{
	GUI_Window_Draw ( "Home" );
}

void wndMouse_btnBack_OnClik ( void* parameter )
{
	GUI_Window_Draw ( "Menu" );
}

void wndMouse_btnChange_OnClik ( void* parameter )
{
	GUI_Window_Draw ( "Menu" );
}

void wndTeclado_btnBack_OnClik( void* parameter )
{
	GUI_Window_Draw ( "Menu" );
}

void wndData_btnBack_OnClik( void* parameter )
{
	GUI_Window_Draw ( "Credits" );
}

void wndCredits_btnData_OnClik( void* parameter )
{

	if ((chkText5 == ON) && (chkText6 == OFF))
		GUI_Window_Draw ( "Data1" );

	if ((chkText5 == OFF) && (chkText6 == ON))
		GUI_Window_Draw ( "Data2" );

	if ((chkText5 == ON) && (chkText6 == ON))
		GUI_Window_Draw ( "Credits" );

}

void wndCredits_chkText5_OnClik ( void* parameter )
{

	if (chkText5 == ON)
	{
		GUI_Check_Create ( "Credits", "btnCheck", 10, 10, 200, 120, BLACK, "", BLACK, OFF,
								wndCredits_chkText5_OnClik, NULL, NULL, NULL );
		chkText5 = OFF;
	}
	else
	{
		GUI_Check_Create ( "Credits", "btnCheck", 10, 10, 200, 120, BLACK, "", BLACK, ON,
								wndCredits_chkText5_OnClik, NULL, NULL, NULL );
		chkText5 = ON;
	}

	GUI_Window_Draw ( "Credits" );
}

void wndCredits_chkText6_OnClik ( void* parameter )
{

	if (chkText6 == ON)
	{
		GUI_Check_Create ( "Credits", "btnCheck", 10, 10, 200, 140, BLACK, "", BLACK, OFF,
								wndCredits_chkText6_OnClik, NULL, NULL, NULL );
		chkText6 = OFF;
	}
	else
	{
		GUI_Check_Create ( "Credits", "btnCheck", 10, 10, 200, 140, BLACK, "", BLACK, ON,
								wndCredits_chkText6_OnClik, NULL, NULL, NULL );
		chkText6 = ON;
	}

	GUI_Window_Draw ( "Credits" );
}

void EINT3_IRQHandler (void)
{
	portBASE_TYPE xHigherPriorityTaskWoken;

	NVIC_DisableIRQ(EINT3_IRQn); 			// Disable the interrupt

	LPC_SC->EXTINT = EINT3; 				// Clear the external interrupt flag
	LPC_GPIOINT->IO0IntClr = 0x01000000; 	// Clear the specific pin interrupt flag

	// Give semaphore
	xSemaphoreGiveFromISR (semaphore_TouchInterrupt, &xHigherPriorityTaskWoken);
}

void ConfigExternalInterrupt ( )
{
	// Configuration of the external interrupt
	LPC_GPIOINT->IO0IntEnF = 0x01000000; 	// Port0.24 (falling edge)
	LPC_SC->EXTMODE = EINT3_EDGE; 			// INT3 edge trigger
	LPC_SC->EXTPOLAR = 0;					// INT3 is falling edge

	// Enable the external interrupt
	NVIC_EnableIRQ(EINT3_IRQn);				// Enable the interrupt
	LPC_SC->EXTINT = EINT3; 				// Clear the external interrupt flag
	LPC_GPIOINT->IO0IntClr = 0x01000000; 	// Clear the specific pin interrupt flag
}

void Task_TouchPanel( void *pvParameters )
{
	portTickType xLastWakeTime;
	uint8_t isEventDetected = 0;
	TouchPanel_TEvent event;
	GLCDgui_TEvent GUIEvent;
	int a;

	for( ;; )
	{
		// Take semaphore
		xSemaphoreTake (semaphore_TouchInterrupt, portMAX_DELAY);

		// Execute until an event is detected
		do
		{
			// TouchPanel_Read must be invoked some times to determine if an event exist
			isEventDetected = TouchPanel_Read ( &(event) );

			// Delay until execute TouchPanel_Read again
			vTaskDelay (50/portTICK_RATE_MS);

		} while ( isEventDetected == 0 );

		// When the do-while stop the event must be raised using the GUI library
		switch (event.eventType)
		{
			case CLICK:
				GUIEvent.xCoordinate = event.xCoordinate;
				GUIEvent.yCoordinate = event.yCoordinate;
				GUIEvent.eventType = GLCD_CLICK;
				GUI_Window_RaiseEvent (&GUIEvent);
			//	GUI_Window_RedrowActiveWindow ();
			break;

			case DOUBLECLICK:

			break;

			case SCROLL_LEFTTORIGHT:
				GUIEvent.xCoordinate = event.xCoordinate;
				GUIEvent.yCoordinate = event.yCoordinate;
				GUIEvent.eventType = GLCD_SCROLL_LEFTTORIGHT;
				GUI_Window_RaiseEvent (&GUIEvent);
			break;

			case SCROLL_RIGHTTOLEFT:
			break;

			case DRAG:
			break;

			case DROP:
			break;

			case NOEVENT:
				a = 2;
			break;
		}

		isEventDetected = 0;

		// Start and configure the external interrupt
		ConfigExternalInterrupt ( );
	}
}

void vApplicationMallocFailedHook ( void )
{
	for( ;; );
}

void vApplicationStackOverflowHook ( xTaskHandle *pxTask, signed char *pcTaskName )
{
	for( ;; );
}

void vApplicationIdleHook ( void )
{

}

void vApplicationTickHook ( void )
{

}

