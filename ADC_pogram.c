/***************************************************************************************************************************************************************************************/
/************************************************* SWE     : ADC DRIVER    *************************************************************************************************************/
/************************************************* BY      : Youssef Ayman *************************************************************************************************************/
/************************************************* Date    : 27Aug20       *************************************************************************************************************/
/************************************************* Version : v1.0          *************************************************************************************************************/
/***************************************************************************************************************************************************************************************/

# include "STD_TYPES.h"
# include "BIT_MATH.h"
# include "ADC_interface.h"
# include "ADC_private.h"
# include "ADC_config.h"



void ADC_VidInit (void)
{
	/*AVCC as reference voltage*/
	SET_BIT(ADMUX,ADMUX_REFS0);
	CLR_BIT(ADMUX,ADMUX_REFS1);

	/*Activate Right adjust result*/
	CLR_BIT(ADMUX,ADMUX_ADLAR);

	/*Set PreScalar*/
	ADCSRA &= 0b11111000;
	ADCSRA |= PRESCALAR_VALUE;

	/*Enable peripheral*/
	SET_BIT(ADCSRA,ADCSRA_ADEN);

}


u16 ADC_u16GetChannelReading (u8 Copy_u8Channel)
{
	/*Clear the MUX bits in ADMUX register*/
	ADMUX &= 0b11100000;

	/*Set the required channel into the MUX bits*/
	ADMUX |= Copy_u8Channel;

	/*Start Conversion*/
	SET_BIT(ADCSRA,ADCSRA_ADSC);

	/*Polling (busy waiting) until the conversion complete , flag is set*/
	while ((GET_BIT(ADCSRA,ADCSRA_ADIF))==0);

	/*Clear the conversion complete flag*/
	SET_BIT(ADCSRA,ADCSRA_ADIF);

	/*Return the reading*/
	return ADC;

}





