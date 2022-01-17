/*
 * ADC_config.h
 *
 *  Created on: Oct 30, 2021
 *      Author: moham
 */

#ifndef ADC_CONFIG_H_
#define ADC_CONFIG_H_


/*Reference selection Bits, Options: 1-AREF, Internal Vref turned off
 	 	 	 	 	 	 	 	 	 2-AVCC with external capacitor at AREF pin
 	 	 	 	 	 	 	 	 	 3-Internal 2.56V Voltage Reference with external capacitor at AREF pin*/

#define ADC_u8_REF_SELECTION		AVCC


/*Choose your resolution	, options: 1- EIGHT_BIT
 * 									   2- TEN_BIT*/

#define ADC_u8_RESOLUTION	TEN_BIT
/*Choose your Enable Initial State	, options: 1-ENABLED		
											   2-DISBALED*/

#define ADC_u8_ENABLE_INIT_STATE	ENABLED

#define ADC_u8_AUTO_TRIG_SRC	//to be continued from page 216





/*Choose your ADC PREscaler disvision factor	, options:  1-DIVIDE_BY_2
															2-DIVIDE_BY_4
															3-DIVIDE_BY_8
															4-DIVIDE_BY_16
															5-DIVIDE_BY_32
															6-DIVIDE_BY_64
															7-DIVIDE_BY_128
															*/

#define ADC_u8_PRESCALER	DIVIDE_BY_128

#define ADC_u32_TIMEOUT_VALUE	500

#endif /* ADC_CONFIG_H_ */
