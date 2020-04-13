/*
 * adc.h
 *
 *  Created on: 4 kwi 2020
 *      Author: Tomek
 */

#ifndef ADC_FILES_ADC_H_
#define ADC_FILES_ADC_H_

#include <avr/io.h>

#define REF_256 (1<<REFS1)|(1<<REFS0)
#define REF_VCC (1<<REFS0)



void ADC_Initalize(void);
uint16_t ADC_Measure();


#endif /* ADC_FILES_ADC_H_ */
