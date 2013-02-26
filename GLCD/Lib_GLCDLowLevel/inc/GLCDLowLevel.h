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

// *****************************
// GLCD WG12864 Manager (Header)
// *****************************

#ifndef _GLCD_LOW_LEVEL_H_
#define _GLCD_LOW_LEVEL_H_

#include <stdint.h>

// ************
// LCD commandsGLCDLowLevel_DISPLAY_HEIGHT
// ************
#define LCD_ON								0x3F
#define LCD_OFF								0x3E
#define LCD_DISP_START						0xC0
#define LCD_SET_ADD							0x40
#define LCD_SET_PAGE						0xB8
#define LCD_BUSY_FLAG						0x80

// *************
// LCD constants
// *************
#define GLCDLowLevel_DISPLAY_WIDTH 			320
#define GLCDLowLevel_DISPLAY_HEIGHT			240
#define GLCDLowLevel_DISPLAY_PAGE_SIZE 		8
#define GLCDLowLevel_DISPLAY_HEIGHT_PAGES	GLCDLowLevel_DISPLAY_HEIGHT/GLCDLowLevel_DISPLAY_PAGE_SIZE
#define GLCDLowLevel_EN_DELAY_VALUE 		1

// Video Memory RAM
uint8_t	GLCDLowLevel_VideoRAM[GLCDLowLevel_DISPLAY_WIDTH][GLCDLowLevel_DISPLAY_HEIGHT_PAGES];
uint8_t GLCDLowLevel_VideoRAM_aux;

// *******************************
// Structures and Type Definitions
// *******************************
typedef uint8_t byte;

// ************************
// Low level GLCD Functions
// ************************
void GLCDLowLevel_Init ();
void GLCDLowLevel_SwapBuffer ();
void GLCD_ClearText(void);
void GLCD_SetCursorAddress(unsigned int address);
void GLCD_TextGoTo(unsigned char x, unsigned char y);
void GLCD_WriteText(char * tekst);


//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------

// ************************
// 			RA8835
// ************************
#define 	RA8835_SYSTEM_SET   	0x40 	//Initialize device and display
#define 	RA8835_SLEEP_IN   		0x53	// Enter standby mode
#define 	RA8835_DISP_OFF   		0x58	// Enable display
#define 	RA8835_DISP_ON   		0x59	// Disable display
#define 	RA8835_SCROLL   		0x44	// Set display start address and display regions
#define 	RA8835_CSRFORM   		0x5d	// Set cursor type
#define 	RA8835_CGRAM_ADR   	    0x5c	// Set start address of character generator RAM
#define 	RA8835_CSRDIR_U   		0x4e	// Set direction of cursor movement UP
#define 	RA8835_CSRDIR_D   		0x4f	// Set direction of cursor movement DOWN
#define 	RA8835_CSRDIR_L   		0x4d	// Set direction of cursor movement LEFT
#define 	RA8835_CSRDIR_R   		0x4c	// Set direction of cursor movement RIGHT
#define 	RA8835_HDOT_SCR   		0x5a	// Set horizontal scroll position
#define 	RA8835_OVLAY   		    0x5b	// Set display overlay format
#define 	RA8835_CSRW   			0x46	// Set cursor address
#define 	RA8835_CSRR   			0x47	// Read cursor address
#define 	RA8835_MWRITE   		0x42	// Write to display memory
#define 	RA8835_MREAD   		    0x43	// Read from display memory

#define 	RA8835_SCR_WIDTH   	    319
#define 	RA8835_M0   			0x00	// Select the internal character generator ROM
#define 	RA8835_M1   			0x00	// Select the memory configuration for user-definable characters.
											// The CG RAM1 and CG RAM2 address spaces are not contiguous

#define 	RA8835_M2   			0x00	// Select the height of the character bitmaps
											// M2 = 0: 8-pixel character height (2716 or equivalent ROM)
											// M2 = 1: 16-pixel character height (2732 or equivalent ROM)

#define 	RA8835_WS   			0x00	// Select the LCD drive method.
											// W/S = 0: Single-panel drive
											// W/S = 1: Dual-panel drive

#define 	RA8835_IV   			0x01	// Screen origin compensation for inverse display.
											// IV = 0: Screen top-line correction
											// IV = 1: No screen top-line correction

#define 	RA8835_FX   			0x07	// Define the horizontal character size
#define 	RA8835_FY   			0x07	// Set the vertical character size
#define 	RA8835_WF   			0x01	// Select the AC frame drive waveform period. WF is usually set to 1.
											// WF = 0: 16-line AC drive
											// WF = 1: two-frame AC drive

#define 	RA8835_CR   			0x27   	// Display addresses per line  ( 320/8 = 40 )
#define 	RA8835_TCR   			47		// ?????????????????????????????????
#define 	RA8835_LF   			239		// Set the height, in lines, of a frame
#define 	RA8835_APL   			40		// Define the horizontal address range of the virtual screen.
#define 	RA8835_APH   			0x00	// APL is the least significant byte of the address.

#define 	RA8835_LINES   		    30
#define 	RA8835_SAD1L   		    0x00
#define 	RA8835_SAD1H   		    0x00
#define 	RA8835_SL1   			0xf0	// SL1 and SL2 set the number of lines per scrolling screen.
#define 	RA8835_SAD2L   		    0x80
#define 	RA8835_SAD2H   		    0x25
#define 	RA8835_SL2   			0xf0	// SL1 and SL2 set the number of lines per scrolling screen.
#define 	RA8835_SAD3L   		    0x00
#define 	RA8835_SAD3H  			0x4b
#define 	RA8835_SAD4L   		    0x00
#define 	RA8835_SAD4H   		    0x00

#define 	RA8835_CRX   			0x04	// Set the horizontal size of the cursor from the character origin
#define 	RA8835_CRY   			0x86	// Set the location of an underscored cursor in lines
#define 	RA8835_CM   			0x01	// Set the cursor shape. Always set CM to 1 when in graphics mode.
											// CM = 0: Underscore cursor
											// CM = 1: Block cursor

#define 	RA8835_MX0   			0x01	// MX0 and MX1 set the layered screen composition method,
#define 	RA8835_MX1   			0x00	// which can be either OR, AND, Exclusive-OR or Priority- OR
											// MX1 = 0, MX0 = 1 --> Exclusive-OR

#define 	RA8835_DM1   			0x00	// DM1 and DM2 specify the display mode of screen blocks 1 and 3, respectively.
#define 	RA8835_DM2   			0x00	// DM1/2 = 0: Text mode
											// DM1/2 = 1: Graphics mode

#define 	RA8835_OV   			0x00	// Specifies two- or three-layer composition in graphics mode.
											// OV = 0: Two-layer composition
											// OV = 1: Three-layer composition
											// Set OV to 0 for mixed text and graphics mode.

#define 	RA8835_SAGL   			0x00	// Specifies the CG RAM start address.
#define 	RA8835_SAGH   			0x48

#define 	RA8835_SCRD   			0x00	// Specifies the number of pixels to scroll
#define 	RA8835_FLASH   		    0x56
#define 	RA8835_TEXTSIZE   		((RA8835_SAD2H << 8) + RA8835_SAD2L)

#define		RA8835_GRAPHICSTART	    ((RA8835_SAD2H << 8) + RA8835_SAD2L)

#define 	RA8835_GRAPHICSIZE   	((RA8835_SL2+1) * (RA8835_SCR_WIDTH+1))>>3
#define 	RA8835_MEM_END   		10800
#define 	RA8835_SYS_P1   		0x10 | (RA8835_IV << 5) | (RA8835_WS << 3) | (RA8835_M2 << 2) | (RA8835_M1 << 1) | RA8835_M0
#define 	RA8835_SYS_P2   		0x00 | (RA8835_WF << 7) | RA8835_FX
#define 	RA8835_CSRF_P2   		0x00 | (RA8835_CM << 7) | RA8835_CRY
#define 	RA8835_OVLAY_P1   		0x00 | (RA8835_OV << 4) | (RA8835_DM2 << 3) | (RA8835_DM1 << 2) | (RA8835_MX1 << 1) | RA8835_MX0


#endif
