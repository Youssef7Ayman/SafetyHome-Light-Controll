/*
 * main.c
 *
 *  Created on: Sep 24, 2022
 *      Author: hp
 */
# include "STD_TYPES.h"
# include "BIT_MATH.h"
# include "DIO_interface.h"
# include "LCD_interface.h"
# include "KPD_interface.h"
# include "ADC_interface.h"
# include "GIE_interface.h"
# include "TIMER_interface.h"
# include "UART_interface.h"
# include <util/delay.h>

void ISR_Temp_LDR_Servo_Readings (void);
u16 TEMP,LIGHT;

int main ()
{
/*----------------------------------------------------------LCD--------------------------------------------------------------------------------*/
	DIO_VidSetPortDirection(Port_A,0b11100000); // LCD CMD Pins  : Port_A {7,6,5--->OutPut} RS,RW,E respectively only
	DIO_VidSetPortDirection(Port_C,0b11111111); // LCD DATA Pins : Port_C {7,6,5,4,3,2,1,0--->OutPut}
//---------------------------------------------------------------------------------------------------------------------------------------------
/*----------------------------------------------------------ADC--------------------------------------------------------------------------------*/
	DIO_VidSetPinDirection(Port_A,Pin0,Input); // Channel_A0 for LM35 [Potentiometer]
	DIO_VidSetPinDirection(Port_A,Pin6,Input); // Channel_A6 for LDR
//---------------------------------------------------------------------------------------------------------------------------------------------
/*---------------------------------------------------------UART--------------------------------------------------------------------------------*/
	DIO_VidSetPinDirection(Port_D,Pin0,Input);      //UART RX pin in Controller
	DIO_VidSetPinDirection(Port_D,Pin1,Output);		//UART TX pin in Controller
//---------------------------------------------------------------------------------------------------------------------------------------------
/*-------------------------------------------------------Servo Motor-------------------------------------------------------------------------*/
	DIO_VidSetPinDirection(Port_D,Pin5,Output); // Servo Motor Pin--> PD5
//---------------------------------------------------------------------------------------------------------------------------------------------
/*-------------------------------------------------------Buzzer&LED-------------------------------------------------------------------------*/
	DIO_VidSetPinDirection(Port_D,Pin7,Output); // Buzzerr Pin--> PD7
	DIO_VidSetPinDirection(Port_B,Pin0,Output); // LED Pin--> PB0
//---------------------------------------------------------------------------------------------------------------------------------------------

	LCD_VidInit();
	ADC_VidInit();
	UART_VidInit();
	TIMER0_VidNormalInit();
	TIMER0_Normal_u8SetCallBack(ISR_Temp_LDR_Servo_Readings);
	TIMER1_VidFPWMInit();
	TIMER2_VidFPWMInit();

	GIE_VidEnable();

	u8 Arr[10]={'-','-','-','-','-','-','-','-','-','-'};
	u8 Recieve,i=0,Temp,Light;

	while (1)
	{
		if(TEMP>=Temp)
		{
			DIO_VidSetPinValue(Port_B,Pin0,PinHigh);
		}
		else
		{
			DIO_VidSetPinValue(Port_B,Pin0,PinLow);
		}

		if(LIGHT<=900)
		{
			Timer2_VidSetDuty(100);
		}
		else
		{
			Timer2_VidSetDuty(100-LIGHT);
		}
		while (1)
		{
			Recieve=UART_u8RecieveData();
			UART_VidSendData(Recieve);
			Arr[i]=Recieve;
			i++;
			if (Arr[i]=='E')
			{
				break;
			}
		}
		Temp=Arr[1]-48;
		Temp=Temp*10+Arr[2]-48;


		i=0;
	}
}

void ISR_Temp_LDR_Servo_Readings (void)
{
	static u8 count=0;
	count++;
	if (count==62)
	{
		UART_VidSendString("TEMP = "); 	TEMP=((ADC_u16GetChannelReading(Channel_A0))*500)/1024;	UART_VidSendValue(TEMP);
		UART_VidPuttyNewLine();
		UART_VidSendString("LDR  = ");	LIGHT=ADC_u16GetChannelReading(Channel_A6);				UART_VidSendValue(LIGHT);
		UART_VidPuttyNewLine();
		UART_VidSendString("Servo Angle = ");	u16 Angle=ADC_u16GetChannelReading(Channel_A0);
		if (Angle<=0)
		{
			Angle=0;
		}
		else if (Angle>=180)
		{
			Angle=180;
		}
		Timer1_VidSetAngle(Angle);
		UART_VidSendValue(Angle);
		UART_VidPuttyNewLine();
		UART_VidSendString("----------------------------------------");
		UART_VidPuttyNewLine();

		count=0;
	}
}







