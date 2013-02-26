/**************************************************************************//**

 * @file     CAD_V2.h

 * @brief
 * 	PROGRAMA DE INICIALIZACION DEL CONVERSOR ANALOGICO DIGITAL
 *	LPC 1769

 * @note
 *	HERNAN BARRIOS - GASTON CONESSA
 *

 ******************************************************************************/


#ifndef __ADC_H 							/* In DMA mode, BURST mode and ADC_INTERRUPT flag need to be set. */
#define __ADC_H								/* In BURST mode, ADC_INTERRUPT need to be set. */


#define ADC_INTERRUPT_FLAG	0				/* 1 is interrupt driven, 0 is polling */
#define BURST_MODE			0   			/* Burst mode works in interrupt driven mode only. */
#define ADC_DEBUG			1

#define ADC_OFFSET          0x10
#define ADC_INDEX           4


#define ADC_ADINT           0x00010000


  /* Table 534: A/D Data Registers (AD0DR0 to AD0DR7 - 0x4003 4010 to 0x4003 402C) bit description */
  /* 30 OVERRUN 	This bit is 1 in burst mode if the results of one or more conversions was (were) lost and overwritten before the conversion that produced the result in the RESULT bits.This bit is cleared by reading this register. */
  /* 31 DONE 		This bit is set to 1 when an A/D conversion completes. It is cleared when this register is read. */


#define ADC_DONE            0x80000000		/* Mascara para saber si termino de convertir el CAD*/
#define ADC_OVERRUN         0x40000000		/* Mascara para saber si exisitio OVERRUN en la conversion del CAD*/


#define ADC_NUM				8				/* CAD de 8 Bits */
//#define CAD_CLOCK			1000000			/* Ajusto a 1Mhz */

void CAD_Inicializacion ( uint32_t CAD_CLOCK );
extern uint32_t CAD_Lectura ( uint8_t NumCanal );
void ADC_IRQHandler (void);

#endif


 /*****************************************************************************
**                            FINAL DEL ARCHIVO
******************************************************************************/

