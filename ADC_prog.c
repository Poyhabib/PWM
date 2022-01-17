/*
 * ADC_prog.c
 *
 *  Created on: Oct 30, 2021
 *      Author: mohamed amer
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ERR_TYPE.h"
#include "ADC_private.h"
#include "ADC_reg.h"
#include "ADC_config.h"
#include "ADC_interface.h"

/*Pointer to function to hold notification function address*/
static void (*ADC_pvNotificationFunc)(void)=NULL;

/*pointer to u16 to hold the conversion result*/
static uint16* ADC_pu16Result=NULL;

/*global variable to hold the ADC peripheral busy state*/
static uint8 ADC_u8BusyState=IDLE;


void ADC_Init(void)
{

#if ADC_u8_REF_SELECTION == AREF
		CLR_BIT(ADMUX,ADMUX_REFS0);
		CLR_BIT(ADMUX,ADMUX_REFS1);
#elif ADC_u8_REF_SELECTION == AVCC
		/*Select ref : AVCC*/
		SET_BIT(ADMUX,ADMUX_REFS0);
		CLR_BIT(ADMUX,ADMUX_REFS1);
#elif ADC_u8_REF_SELECTION == INTERNAL_2650mv
		SET_BIT(ADMUX,ADMUX_REFS0);
		SET_BIT(ADMUX,ADMUX_REFS1);
#else
#error "Error in ADC Reference Selection BITS Configuration"
#endif

		/*Enable RESOLUTION*/
#if ADC_u8_RESOLUTION==EIGHT_BIT

		SET_BIT(ADMUX,ADMUX_ADLAR);

#elif ADC_u8_RESOLUTION==TEN_BIT
		CLR_BIT(ADMUX,ADMUX_ADLAR);
#else
#error "Error in ADC RESOLUTION Configuration"
#endif


		/*ADC Enable*/
#if ADC_u8_ENABLE_INIT_STATE==ENABLED
		SET_BIT(ADCSRA,ADCSRA_ADEN);
#elif ADC_u8_ENABLE_INIT_STATE==DISBALED
		CLR_BIT(ADCSRA,ADCSRA_ADEN);
#else
#error "ERROR in ADC INITAIL STATE Configuration"
#endif


		/*ADC PREscaler division factor*/
		ADCSRA &= PRESCALER_BIT_MASK;
		ADCSRA |= ADC_u8_PRESCALER;


}

void ADC_voidEnable(void)
{
	SET_BIT(ADCSRA,ADCSRA_ADEN);
}

void ADC_voidDisable(void)
{

	CLR_BIT(ADCSRA,ADCSRA_ADEN);
}




uint8 ADC_u8StartConverstionSynch(uint8 Copy_u8Channel,uint16* Copy_pu16Result)
{

	uint8 Local_u8ErrorState=OK;
	uint32 Local_u32Counter=0;
	if(Copy_pu16Result!=NULL)
	{
		if(ADC_u8BusyState==IDLE)
		{
		/*Set Channel*/
		ADMUX &= CHANNEL_BIT_MASK;
		ADMUX |= Copy_u8Channel;

		/*ADC start conversion*/
		SET_BIT(ADCSRA,ADCSRA_ADSC);
		/* wait (polling) for conversion complete flag , or wait until timeout passes*/
		while((GET_BIT(ADCSRA,ADCSRA_ADIF) == 0) && (Local_u32Counter != ADC_u32_TIMEOUT_VALUE))
		{
			Local_u32Counter++;
		}

		if(Local_u32Counter == ADC_u32_TIMEOUT_VALUE)
		{
			/*Loop is broken because timeout passed without flag*/
			Local_u8ErrorState=TIMEOUT_ERR;

		}
		else
		{
			/*flag is raised before timeout*/
			/*Clear the conversion complete flag*/
			SET_BIT(ADCSRA,ADCSRA_ADIF);

			/*return the result*/
#if ADC_u8_RESOLUTION==EIGHT_BIT
			*Copy_pu16Result= ADCH;
#elif ADC_u8_RESOLUTION==TEN_BIT	
			*Copy_pu16Result= ADC;
#endif
		}
	}

	else
	{
		Local_u8ErrorState=BUSY_ERR;
	}
	}
	else
	{
		Local_u8ErrorState=NULL_POINTER;
	}

	return Local_u8ErrorState;

}


uint8 ADC_u8StartConverstionAsynch(uint8 Copy_u8Channel,uint16* Copy_pu16Result,void (*Copy_pvNotificationFunc)(void))
{

	uint8 Local_u8ErrorState=OK;
	if((Copy_pu16Result!=NULL) && (Copy_pvNotificationFunc!= NULL))

	{

		/*Storing the address on the function to the global variable*/
		ADC_pvNotificationFunc = Copy_pvNotificationFunc;

		/*Store the result variable address globally*/
		ADC_pu16Result=Copy_pu16Result;

		/*Set Channel*/
		ADMUX &= CHANNEL_BIT_MASK;
		ADMUX |= Copy_u8Channel;

		/*ADC start conversion*/
		SET_BIT(ADCSRA,ADCSRA_ADSC);



		/*ADC interrupt Enable*/
		SET_BIT(ADCSRA,ADCSRA_ADIE);


	}
	else
	{

		Local_u8ErrorState=NOK;
	}


	return Local_u8ErrorState;
}

/*ADC ISR*/
void __vector_16(void) __attribute__((signal));

void __vector_16(void)
{

	/*Get The conversion Result*/
#if ADC_u8_RESOLUTION==EIGHT_BIT
	*ADC_pu16Result= ADCH;
#elif ADC_u8_RESOLUTION==TEN_BIT
	*ADC_pu16Result= ADC;
#endif

	/*Disable ADC interrupt Enable*/
	CLR_BIT(ADCSRA,ADCSRA_ADIE);

	/*Invoke The callback notification function*/
	if(ADC_pvNotificationFunc!=NULL)
	{
		ADC_pvNotificationFunc();
	}
	else
	{
		/*Do nothing*/
	}




}
