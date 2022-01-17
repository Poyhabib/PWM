/*
 * ADC_reg.h
 *
 *  Created on: Oct 30, 2021
 *      Author: moham
 */

#ifndef ADC_REG_H_
#define ADC_REG_H_


#define ADMUX *((volatile uint8*)0x27)
#define ADMUX_REFS1	7
#define ADMUX_REFS0	6
#define	ADMUX_ADLAR	5
#define ADMUX_MUX4	4
#define ADMUX_MUX3	3
#define ADMUX_MUX2	2
#define ADMUX_MUX1	1
#define ADMUX_MUX0	0


#define	ADCSRA	*((volatile uint8*)0x26)
#define ADCSRA_ADEN 7
#define ADCSRA_ADSC 6
#define ADCSRA_ADATE 5
#define ADCSRA_ADIF 4
#define ADCSRA_ADIE 3
#define ADCSRA_ADPS0	0
#define ADCSRA_ADPS1	1
#define ADCSRA_ADPS2	2

#define ADCH *((volatile uint8*)0x25)
#define ADCL *((volatile uint8*)0x24)


#define ADC	*((volatile uint16*)0x24)




#endif /* ADC_REG_H_ */
