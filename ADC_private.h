/***************************************************************************************************************************************************************************************/
/************************************************* SWE     : ADC DRIVER    *************************************************************************************************************/
/************************************************* BY      : Youssef Ayman *************************************************************************************************************/
/************************************************* Date    : 27Aug20       *************************************************************************************************************/
/************************************************* Version : v1.0          *************************************************************************************************************/
/***************************************************************************************************************************************************************************************/

# ifndef ADC_PRIVATE_H
# define ADC_PRIVATE_H

# define ADMUX  		*((volatile u8*)0x27)   //ADC multiplexer selection register
# define ADMUX_REFS1  				7			//Reference selection bit1
# define ADMUX_REFS0  				6			//Reference selection bit0
# define ADMUX_ADLAR  				5			//ADC left adjust result(if it is one)


# define ADCSRA  		*((volatile u8*)0x26)   //ADC control and status register A
# define ADCSRA_ADEN				7			//ADC enable
# define ADCSRA_ADSC				6           //Start conversion
# define ADCSRA_ADATE				5           //Auto trigger enable
# define ADCSRA_ADIF				4           //Interrupt flag
# define ADCSRA_ADIE				3           //Interrupt enable
# define ADCSRA_ADPS2				2           //Prescaler bit2
# define ADCSRA_ADPS1				1           //Prescaler bit1
# define ADCSRA_ADPS0				0           //Prescaler bit0


# define ADC  			*((volatile u16*)0x24)  //ADC Pointer to ADCL address that takes the remaining ADCH bits after
# define ADCH  			*((volatile u8*)0x25)   //ADC High register
# define ADCL  			*((volatile u8*)0x24)   //ADC Low register


# define DIV_BY_2  			 0
# define DIV_BY_2_AGAIN  	 1
# define DIV_BY_4  			 2
# define DIV_BY_8  			 3
# define DIV_BY_16  	     4
# define DIV_BY_32 			 5
# define DIV_BY_64 			 6
# define DIV_BY_128  		 7


#endif

