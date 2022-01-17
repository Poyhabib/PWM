/*
 * ADC_private.h
 *
 *  Created on: Oct 30, 2021
 *      Author: moham
 */

#ifndef ADC_PRIVATE_H_
#define ADC_PRIVATE_H_

#define AREF 1
#define AVCC 2
#define INTERNAL_2650mv 3


#define EIGHT_BIT 1
#define TEN_BIT 2

#define ENABLED	1
#define DISABLED 2

#define DIVIDE_BY_2		0
#define DIVIDE_BY_4		2
#define DIVIDE_BY_8		3
#define DIVIDE_BY_16	4
#define DIVIDE_BY_32	5
#define DIVIDE_BY_64	6
#define DIVIDE_BY_128	7

#define PRESCALER_BIT_MASK	0b11111000
#define CHANNEL_BIT_MASK	0b11100000

#define IDLE	1
#define Busy	2
 
#endif /* ADC_PRIVATE_H_ */
