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
#include "MicroInterface.h"
#include "lpc17xx_gpio.h"


uint32_t i;

inline void MicroInterface_Init ()
{
	// Set as digital outputs LCD control lines
	FIO_SetDir (LCD_CMD_PORT, (1<<READ), 1);
	FIO_SetDir (LCD_CMD_PORT, (1<<WRITE), 1);
	FIO_SetDir (LCD_CMD_PORT, (1<<A0), 1);
	FIO_SetDir (LCD_CSEL_PORT, (1<<CSEL), 1);

	// Set as digital outputs LCD data lines
	FIO_ByteSetDir (LCD_DATA_PORT, 0, 0xFF, 1);
	FIO_SetDir(0,(1<<DB0),1);
	FIO_SetDir(0,(1<<DB1),1);
}

inline void MicroInterface_Bit_WriteLow (uint8_t port, uint8_t pin)
{
	// LCD control lines are physical inverter
	FIO_SetValue(port,(1<<pin));
}

inline void MicroInterface_Bit_WriteHigh (uint8_t port, uint8_t pin)
{
	// LCD control lines are physical inverter
	FIO_ClearValue(port,(1<<pin));
}


void MicroInterface_Byte_WriteData (uint8_t buf)
{
	// The buf byte is inverter because the data lines are
	// physical inverted

	FIO_ByteSetValue(LCD_DATA_PORT,0,~buf);
	FIO_ByteClearValue(LCD_DATA_PORT,0,buf);

	// This is because DB0 and DB1 are not physical connected to the
	// same port byte nibble.
	// This is specific for the actual hardware. In future
	// implementations should be omitted.
	if ( (buf & 1) == 1 )
		MicroInterface_Bit_WriteHigh (0, DB0);
	else
		MicroInterface_Bit_WriteLow (0, DB0);

	if ( (buf & 2) == 2 )
		MicroInterface_Bit_WriteHigh (0, DB1);
	else
		MicroInterface_Bit_WriteLow (0, DB1);

}


void GLCD_WriteData(uint8_t dataToWrite)
{

	MicroInterface_Bit_WriteLow (LCD_CMD_PORT, A0);		 // lcd_A0 = 0;
	MicroInterface_Bit_WriteLow (LCD_CSEL_PORT, CSEL);   // lcd_CS = 0;
	MicroInterface_Bit_WriteHigh (LCD_CMD_PORT, WRITE);	 // lcd_WR = 1;
	MicroInterface_Bit_WriteLow (LCD_CMD_PORT, WRITE);	 // lcd_WR = 0;
	MicroInterface_Bit_WriteHigh (LCD_CMD_PORT, READ);	 // lcd_RD = 1;
	MicroInterface_Byte_WriteData (dataToWrite);
	for(i=0;i<10;i++);
	MicroInterface_Bit_WriteLow (LCD_CMD_PORT, READ);	 // lcd_RD = 0;

}


void GLCD_WriteCommand(uint8_t commandToWrite)
{

	MicroInterface_Bit_WriteLow (LCD_CMD_PORT, WRITE);	 // lcd_WR = 0;
	MicroInterface_Bit_WriteHigh (LCD_CMD_PORT, A0);	 // lcd_A0 = 1;
	MicroInterface_Bit_WriteLow (LCD_CSEL_PORT, CSEL);   // lcd_CS = 0;
	MicroInterface_Bit_WriteHigh (LCD_CMD_PORT, READ);	 // lcd_RD = 1;
	MicroInterface_Byte_WriteData (commandToWrite);
	for(i=0;i<10;i++);
	MicroInterface_Bit_WriteLow (LCD_CMD_PORT, READ);	 // lcd_RD = 0;

}



