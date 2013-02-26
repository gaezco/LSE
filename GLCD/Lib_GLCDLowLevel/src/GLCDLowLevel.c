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

#include <stdint.h>
#include "GLCDLowLevel.h"
#include "MicroInterface.h"

// ******************
// Private Attributes
// ******************
int _delayCounter; // Used for EN_DELAY Macro

// ***************
// Private Methods
// ***************

void GLCDLowLevel_Init()
{
	MicroInterface_Init();  				// Init  ports

	//////////////////////////////////
	//			SYSTEM_SET			//
	//////////////////////////////////

	GLCD_WriteCommand(RA8835_SYSTEM_SET);	//Writng into command register System set

	GLCD_WriteData(RA8835_SYS_P1);			//P1  M0: Internal CG ROM
											//    M1: CG RAM is 32 characters maximum
											//    M2: 8-pixel character height
											//    W/S: Two-panel drive
											//    IV: No top-line compensation

	GLCD_WriteData(RA8835_SYS_P2);			//P2  FX: Horizontal character size = 8 pixels
											//    WF: Two-frame AC drive

	GLCD_WriteData(RA8835_FY);				//P3  FY: Vertical character size = 8 pixels

	GLCD_WriteData(RA8835_CR);				//P4  C/R: 39 display addresses per line

	GLCD_WriteData(RA8835_TCR);			//P5  TC/R: Total address range per line

	GLCD_WriteData(RA8835_LF);				//P6  L/F: 239 display lines

	GLCD_WriteData(RA8835_APL);			//P7  APL: Virtual screen horizontal size is 40 addresses

	GLCD_WriteData(RA8835_APH);			//P8  APL: Virtual screen horizontal size is 40 addresses


	//////////////////////////////////
	//			  SCROLL			//
	//////////////////////////////////

	GLCD_WriteCommand(RA8835_SCROLL);		//Scrolling

	GLCD_WriteData(RA8835_SAD1L);			//P1  First screen block start address set to 0x0000
	GLCD_WriteData(RA8835_SAD1H);			//P2  First screen block start address set to 0x0000

	GLCD_WriteData(RA8835_SL1);			//P3  Display lines in first screen block = 240

	GLCD_WriteData(RA8835_SAD2L);			//P4  Second screen block start address set to 0x1000

	GLCD_WriteData(RA8835_SAD2H);			//P5  Second screen block start address set to 0x1000


	GLCD_WriteData(RA8835_SL2);			//P6  Display lines in second screen block = 240


	GLCD_WriteData(RA8835_SAD3L);			//P7  Third screen block start address set to 0x0000
	GLCD_WriteData(RA8835_SAD3H);			//P8 Third screen block start address set to 0x0000

	GLCD_WriteData(RA8835_SAD4L);			//P9  Fourth screen block start address set to 0x0000
	GLCD_WriteData(RA8835_SAD4H);			//P10  Fourth screen block start address set to 0x0000


	//////////////////////////////////
	//			  HDOT SCR			//
	//////////////////////////////////

	GLCD_WriteCommand(RA8835_HDOT_SCR);	// HDOT
	GLCD_WriteData(RA8835_SCRD);			// 0 pixels scroll



	//////////////////////////////////
	//			 OVERLAY			//
	//////////////////////////////////

	GLCD_WriteCommand(RA8835_OVLAY);		// OVERLAY

	GLCD_WriteData(RA8835_OVLAY_P1);		//  MX 1, MX 0: Inverse video superposition
											//  DM 1: First screen block is text mode
											//  DM 2: Third screen block is text mode

	//////////////////////////////////
	//			DISPLAY OFF			//
	//////////////////////////////////

	GLCD_WriteCommand(RA8835_DISP_OFF);	//Display off

	GLCD_WriteData(RA8835_FLASH);			//FC1, FC0: Flash cursor at 2 Hz
											//FP1, FP0: First screen block ON
											//FP3, FP2: Second and fourth screen blocks ON
											//FP5, FP4: Third screen block ON


	//////////////////////////////////
	//			 CSRW			    //
	//////////////////////////////////

	GLCD_WriteCommand(RA8835_CSRW);
	GLCD_WriteData(RA8835_SAD1L);
	GLCD_WriteData(RA8835_SAD1H);

	//////////////////////////////////
	//			 CSRFORM			//
	//////////////////////////////////

	GLCD_WriteCommand(RA8835_CSRFORM);		//Cursor type  CSRFORM

	GLCD_WriteData(RA8835_CRX);			//Horizontal cursor size = 6 pixels

	GLCD_WriteData(RA8835_CRY);			//Vertical cursor size = 9 pixels


	//////////////////////////////////
	//			DISPLAY ON			//
	//////////////////////////////////

	GLCD_WriteCommand(RA8835_DISP_ON);		// Display on

	//GLCD_WriteData(RA8835_FLASH);		//FC1, FC0: Flash cursor at 2 Hz
											//FP1, FP0: First screen block ON
											//FP3, FP2: Second and fourth screen blocks ON
											//FP5, FP4: Third screen block ON

	//////////////////////////////////
	//			 CURSOR				//
	//////////////////////////////////

	GLCD_WriteCommand(RA8835_CSRDIR_D);	// Set direction of cursor movement RIGHT


	//////////////////////////////////
	//			 CG RAM				//
	//////////////////////////////////

	GLCD_WriteCommand(RA8835_CGRAM_ADR);
	GLCD_WriteData(RA8835_SAGL);
	GLCD_WriteData(RA8835_SAGH);

}


void GLCD_TextGoTo(unsigned char x, unsigned char y)
{
GLCD_SetCursorAddress((y * 40) + x);
}


void GLCD_SetCursorAddress(unsigned int address)
{
GLCD_WriteCommand(RA8835_CSRW);
GLCD_WriteData((unsigned char)(address & 0xFF));
GLCD_WriteData((unsigned char)(address >> 8));
}


void GLCD_ClearText(void)
{
int i;
GLCD_TextGoTo(0,0);
GLCD_WriteCommand(RA8835_CSRDIR_R);
GLCD_WriteCommand(RA8835_MWRITE);
for(i = 0; i < 50000; i++)
	GLCD_WriteData(0x00);
GLCD_WriteCommand(RA8835_CSRDIR_D);
}


void GLCD_WriteText(char * tekst)
{
GLCD_WriteCommand(RA8835_MWRITE);
while(*tekst)
	GLCD_WriteData(*tekst++);
}


void GLCDLowLevel_SwapBuffer(){


	uint32_t a,b;
	int8_t c,d;
	for (a=0; a<40; a++){

		GLCD_WriteCommand(0x46);
		GLCD_WriteData(RA8835_SAD2L + a);
		GLCD_WriteData(RA8835_SAD2H);
		GLCD_WriteCommand(RA8835_MWRITE);

		for (b=0; b<30; b++){
			for (c=0; c<8; c++){
				for (d=0; d<8; d++){

					if (d-c >= 0){
						GLCDLowLevel_VideoRAM_aux+= (((0x01 << c) & GLCDLowLevel_VideoRAM[(a*8)+(7-d)][b]) << (d-c));
					}
					else {
						GLCDLowLevel_VideoRAM_aux+= (((0x01 << c) & GLCDLowLevel_VideoRAM[(a*8)+(7-d)][b]) >> (c-d));
					}

				}
				GLCD_WriteData(GLCDLowLevel_VideoRAM_aux);
				GLCDLowLevel_VideoRAM_aux=0;

			}

		}

	}
}
