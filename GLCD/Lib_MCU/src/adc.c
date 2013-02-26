#include "LPC17xx.h"
#include "adc.h"

volatile uint32_t ADC0Value[ADC_NUM];
volatile uint32_t ADC0IntDone = 0;
volatile uint32_t ADCValue;

#if BURST_MODE
volatile uint32_t channel_flag; 
#endif

#if ADC_INTERRUPT_FLAG


/******************************************************************************
 ** Function name:		ADC_IRQHandler
 **
 ** Descriptions:		ADC interrupt handler
 **
 ** parameters:			None
 ** Returned value:		None
 **
 ******************************************************************************/
 void ADC_IRQHandler (void)
 {
   uint32_t regVal;

   regVal = LPC_ADC->ADSTAT;		/* Read ADC will clear the interrupt */
   if ( regVal & 0x0000FF00 )	/* check OVERRUN error first */
   {
 	regVal = (regVal & 0x0000FF00) >> 0x08;
 	/* if overrun, just read ADDR to clear */
 	/* regVal variable has been reused. */
 	switch ( regVal )
 	{
 	  case 0x01:
 		regVal = LPC_ADC->ADDR0;
 	  break;
 	  case 0x02:
 		regVal = LPC_ADC->ADDR1;
 	  break;
 	  case 0x04:
 		regVal = LPC_ADC->ADDR2;
 	  break;
 	  case 0x08:
 		regVal = LPC_ADC->ADDR3;
 	  break;
 	  case 0x10:
 		regVal = LPC_ADC->ADDR4;
 	  break;
 	  case 0x20:
 		regVal = LPC_ADC->ADDR5;
 	  break;
 	  case 0x40:
 		regVal = LPC_ADC->ADDR6;
 	  break;
 	  case 0x80:
 		regVal = LPC_ADC->ADDR7;
 	  break;
 	  default:
 	  break;
 	}
 	LPC_ADC->ADCR &= 0xF8FFFFFF;	/* stop ADC now */
 	ADC0IntDone = 1;
 	return;
   }

   if ( regVal & ADC_ADINT )
   {
 	switch ( regVal & 0xFF )	/* check DONE bit */
 	{
 	  case 0x01:
 		ADC0Value[0] = ( LPC_ADC->ADDR0 >> 4 ) & 0xFFF;
 	  break;
 	  case 0x02:
 		ADC0Value[1] = ( LPC_ADC->ADDR1 >> 4 ) & 0xFFF;
 	  break;
 	  case 0x04:
 		ADC0Value[2] = ( LPC_ADC->ADDR2 >> 4 ) & 0xFFF;
 	  break;
 	  case 0x08:
 		ADC0Value[3] = ( LPC_ADC->ADDR3 >> 4 ) & 0xFFF;
 	  break;
 	  case 0x10:
 		ADC0Value[4] = ( LPC_ADC->ADDR4 >> 4 ) & 0xFFF;
 	  break;
 	  case 0x20:
 		ADC0Value[5] = ( LPC_ADC->ADDR5 >> 4 ) & 0xFFF;
 	  break;
 	  case 0x40:
 		ADC0Value[6] = ( LPC_ADC->ADDR6 >> 4 ) & 0xFFF;
 	  break;
 	  case 0x80:
 		ADC0Value[7] = ( LPC_ADC->ADDR7 >> 4 ) & 0xFFF;
 	  break;
 	  default:
 	  break;
 	}
 #if BURST_MODE
 	channel_flag |= (regVal & 0xFF);
 	if ( (channel_flag & 0xFF) == 0xFF )
 	{
 	  /* All the bits in have been set, it indicates all the ADC
 	  channels have been converted. */
 	  LPC_ADC->ADCR &= 0xF8FFFFFF;	/* stop ADC now */
 	  ADC0IntDone = 1;
 	}
 #else
 	LPC_ADC->ADCR &= 0xF8FFFFFF;	/* stop ADC now */
 	ADC0IntDone = 1;
 #endif
   }
   return;
 }
 #endif

/*****************************************************************************
** Nombre de la funcion:		ADC_Inicializacion
**
** Descripcion:					Inicializar el CAD
**
** Parametros de entrada:		Frecuencia de trabajo del ADC
** Parametros de salida:		Ninguno
**
*****************************************************************************/
void CAD_Inicializacion ( uint32_t CAD_CLOCK )
{

  uint32_t pclkdiv, pclk;						/* Defino las variables a utilizar dentro de la funcion */

  LPC_SC->PCONP |= (1 << 12);					/* Habilito el CLOCK dentro del controlador CAD */
												/* PCONP -> Rregistro 12  ->  PCADC A/D converter (ADC) power/clock control bit */

  ADCValue = 0x00; 								/* Limpio los valores actuales del CAD */


 /*  	TABLA PINSEL1 */

 /*		PINSEL1		PINAME 		FUN C/01 */
 /*		15:14 		P0.23[1] 	GPIO Port 0.23 */
 /*		17:16 		P0.24[1] 	GPIO Port 0.24 */
 /*		19:18 		P0.25 		GPIO Port 0.25 */
 /*		21:20 		P0.26 		GPIO Port 0.26 */


  /* Configuro los pines como entradas CAD */

  LPC_PINCON->PINSEL1 &= ~0x003FC000;			/* P0.23~26, A0.0~3, FUNCION 01 */
  LPC_PINCON->PINSEL1 |= 0x00154000;


  /* No configuro pull-up / pull-down en esos pines del CAD. (function 10)*/

  LPC_PINCON->PINMODE1 &= ~0x003FC000;
  LPC_PINCON->PINMODE1 |= 0x002A8000;



  /* Configuro la frecuencia del trabajo del clock. Segun el manual tenemos la siguiente especificacion: */
  /* Clock: In the PCLKSEL0 register (Table 40), select PCLK_ADC. To scale the clock for the ADC, see bits CLKDIV in Table 531. */
  /* 25:24 PCLK_ADC Peripheral clock selection for ADC. 00 */
  /* Los bits 24~25 son para configurar el CAD */


  pclkdiv = (LPC_SC->PCLKSEL0 >> 24) & 0x03;
  switch ( pclkdiv )
  {
	case 0x00:
	default:
	  pclk = SystemCoreClock/4;
	break;
	case 0x01:
	  pclk = SystemCoreClock;
	break;
	case 0x02:
	  pclk = SystemCoreClock/2;
	break;
	case 0x03:
	  pclk = SystemCoreClock/8;
	break;
  }



  /* Configuro el CAD Control Register */

  LPC_ADC->ADCR = ( 0x01 << 0 ) |  						/* SEL=1,select channel 0~7 on ADC0 */
		( ( pclk  / CAD_CLOCK - 1 ) << 8 ) |  			/* CLKDIV = Fpclk / CAD_CLOCK - 1 */
		( 0 << 16 ) | 									/* BURST = 0, no BURST, Conversions are software controlled and require 65 clocks.*/
		( 1 << 21 ) |  									/* PDN = 1, normal operation */
		( 0 << 24 ) |  									/* START = 0 A/D conversion stops */
		( 0 << 27 );									/* EDGE = 0 (CAP/MAT singal falling,trigger A/D conversion) */



  /* En caso de querer trabajar el CAD utilizando interrupciones */

#if ADC_INTERRUPT_FLAG			/* Si quiero trabajar utilizando la interrupcion del CAD */
  NVIC_EnableIRQ(ADC_IRQn);
#if BURST_MODE					/* Si quiero trabajar utilizando BURST mode */
  LPC_ADC->INTEN = 0xFF;		/* Habilito todas las interrupciones */
#else
  LPC_ADC->INTEN = 0x1FF;		/* Habilito todas las interrupciones */
#endif
#endif
  return;

}


/*****************************************************************************
** Nombre de la funcion:		CAD_Lectura
**
** Descripcion:					Leer un canal del CAD
**
** Parametros de entrada:		Numero del canal
** Parametros de salida:		Valor leido, en caso de usar interrupciones, se retorna el numero de canal
**
*****************************************************************************/
uint32_t CAD_Lectura ( uint8_t NumCanal )
{
#if !ADC_INTERRUPT_FLAG								/* En caso de no trabajar con interrupcion de CAD */

  uint32_t regVal, ADC_Data;						/* Defino las variables a utilizar dentro de la funcion */

#endif


  if ( NumCanal >= ADC_NUM )						/* Comparo el canal a leer, con la cantidad de canales que tenemos*/
  {
	NumCanal = 0;									/* En caso de no especificar un canal correcto, configuro leer el canal 0 */
  }


  LPC_ADC->ADCR &= 0xFFFFFF00;
  LPC_ADC->ADCR |= (1 << 24) | (1 << NumCanal);		/* Selecciono el canal y arranco el CAD (OJO, PROBAR QUE NO SEA BIT 0 Y NO 1!!!!) */



  /* Table 534: A/D Data Registers (AD0DR0 to AD0DR7 - 0x4003 4010 to 0x4003 402C) bit description */
  /* 30 OVERRUN 	This bit is 1 in burst mode if the results of one or more conversions was (were) lost and overwritten before the conversion that produced the result in the RESULT bits.This bit is cleared by reading this register. */
  /* 31 DONE 		This bit is set to 1 when an A/D conversion completes. It is cleared when this register is read. */



#if !ADC_INTERRUPT_FLAG								/* En caso de no trabajar con interrupcion de CAD */
  while ( 1 )										/* Espero hasta que termine el CAD */
  {
	 regVal = *(volatile unsigned long *)(LPC_ADC_BASE 	/* Leo el DRx para obtener el estado del CADx. (DR: Data Registers) */
	  			+ ADC_OFFSET + ADC_INDEX * NumCanal);	/* Si el CADx termino de convertir, salgo del bucle de espera */
	  	if ( regVal & ADC_DONE )
	  	{
	  	  break;
	  	}
  }


  LPC_ADC->ADCR &= 0xF8FFFFFF;						/* Paro el CAD */
  if ( regVal & ADC_OVERRUN )						/* Consulto si no ocurrio OVERRUN en la conversion */
  {
	return ( 0 );									/* Si existio OVERRUN devuelvo el valor 0 y salgo de la funcion */
  }

 /* Table 534: A/D Data Registers (AD0DR0 to AD0DR7 - 0x4003 4010 to 0x4003 402C) bit description */
 /*  15:4 RESULT 	When DONE is 1, this field contains a binary fraction representing the voltage on the AD0[n] pin, as it falls within the range of VREFP to VREFN. Zero in the field indicates that the voltage on */
 /* the input pin was less than, equal to, or close to that on VREFN, while 0xFFF indicates that the voltage on the input was close to, equal to, or greater than that on VREFP. */

  ADC_Data = ( regVal >> 4 ) & 0xFFF;				/* Leo el valor medido del CADx, el cual lo tengo copiado en regVal del DR. Lo corro 4 posiciones a la derecha y hago una and con la mascara FFF*/
  return ( ADC_Data );								/* Si no ocurrio OVERRUN devuelvo el valor medido */


#else
  return ( NumCanal );								/* Si trabajo con interrupcion, la lectura del CAD esta contemplada en el handler. Por lo tanto devuelvo el numero del canal */

#endif
}
