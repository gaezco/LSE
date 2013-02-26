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

#ifndef INTERFACE_GLCD_H_
#define INTERFACE_GLCD_H_

// *********************************
// LPC pins assigned to LCD WG320240
// *********************************
#define LCD_CSEL_PORT		0
#define CSEL				11

#define LCD_CMD_PORT		0
#define READ				8
#define WRITE				9
#define A0					10

#define LCD_DATA_PORT		0
#define DB0					21
#define DB1					22

void MicroInterface_Init ();
void MicroInterface_Bit_WriteLow (uint8_t port, uint8_t pin);
void MicroInterface_Bit_WriteHigh (uint8_t port, uint8_t pin);
void MicroInterface_Byte_WriteData (uint8_t buf);
void GLCD_WriteData(uint8_t dataToWrite);
void GLCD_WriteCommand(uint8_t  commandToWrite);


#endif /* INTERFACE_GLCD_H_ */
