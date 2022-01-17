/*
 * ADC_interface.h
 *
 *  Created on: Oct 30, 2021
 *      Author: moham
 */

#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

#define ADC_u8_SINGLE_ENDED_CH0		0
#define ADC_u8_SINGLE_ENDED_CH1		1
#define ADC_u8_SINGLE_ENDED_CH2		2
#define ADC_u8_SINGLE_ENDED_CH3		3
#define ADC_u8_SINGLE_ENDED_CH4		4
#define ADC_u8_SINGLE_ENDED_CH5		5
#define ADC_u8_SINGLE_ENDED_CH6		6
#define ADC_u8_SINGLE_ENDED_CH7		7

void ADC_Init(void);

void ADC_voidEnable(void);

void ADC_voidDisable(void);

uint8 ADC_u8StartConverstionSynch(uint8 Copy_u8Channel,uint16* Copy_pu16Result);

/*NOTE : ENABLE THE GLOBAL INTERRUPT ENABLE TO USE THIS FUNCTION*/
uint8 ADC_u8StartConverstionAsynch(uint8 Copy_u8Channel,uint16* Copy_pu16Result,void (*Copy_pvNotificationFunc)(void));

#endif /* ADC_INTERFACE_H_ */
