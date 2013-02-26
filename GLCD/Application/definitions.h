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

#ifndef DEFINITIONS_H_
#define DEFINITIONS_H_

// GUI library includes
#include "GLCDgui.h"
#include "window.h"
#include "button.h"
#include "Check.h"
#include "textSlider.h"
#include "text.h"
#include "picture.h"
#include "SystemFont5x7.h"
#include "GLCDguiEvent.h"
#include "Mouse.h"
// Bitmaps includes
#include "fiuba.h"
// Touch Panel library
#include "touchPanel.h"
// FreeRTOS library includes
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
// CMSIS and Drivers includes
#include "adc.h"
#include "extern.h"
#include "lpc17xx_adc.h"
#include "lpc17xx_pinsel.h"

// General Defines
#define ON	1
#define OFF	0

// Touch Panel (pins defines)
#define		XMAS_PORT		0
#define 	XMAS_PIN		25
#define 	XMENOS_PORT		0
#define 	XMENOS_PIN		26
#define 	YMAS_PORT		0
#define 	YMAS_PIN		23
#define 	YMENOS_PORT		0
#define 	YMENOS_PIN		24

// External Interrupt defines
#define 	EINT3			0x00000008
#define 	EINT3_EDGE		0x00000008
#define 	EINT3_RISING	0x00000008

// Refresh timer for detect the event over the touch panel
#define		TOUCH_REFRESH_T		50

// Function for start the graphic library
void StartGUI ();
// Function for build the graphic interface and start the GLCD
void CreateGUI ();

// Function for configure the external interrupt for detect activity on the screen
void ConfigExternalInterrupt();

// GUI events handlers
void wndHome_picFiuba_OnClik ( void* parameter );
void wndHome_btnSettings_OnClik ( void* parameter );
void wndCredits_btnBack_OnClik ( void* parameter );
void wndHome_btnCredits_OnClik ( void* parameter );
void wndMenu_btnMouse_OnClik ( void* parameter );
void wndMenu_btnTeclado_OnClik ( void* parameter );
void wndMenu_btnBack_OnClik ( void* parameter );
void wndMouse_btnBack_OnClik ( void* parameter );
void wndMouse_btnChange_OnClik ( void* parameter );
void wndTeclado_btnBack_OnClik ( void* parameter );
void wndCredits_btnData_OnClik( void* parameter );
void wndCredits_chkText5_OnClik ( void* parameter );
void wndCredits_chkText6_OnClik ( void* parameter );
void wndData_btnBack_OnClik( void* parameter );

// FreeRTOS task for synchronize the Touch Panel library
void Task_TouchPanel( void *pvParameters );

// FreeRTOS semaphore for synchronize the external interrupt with the touch panel task
xSemaphoreHandle semaphore_TouchInterrupt;

#endif /* DEFINITIONS_H_ */
