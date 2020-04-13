/*
 * adc.c
 *
 *  Created on: 4 kwi 2020
 *      Author: Tomek
 */

#include "adc.h"


void ADC_Initalize(void){

	ADCSRA |= (1<<ADEN); // w³¹czenie ADC
	ADCSRA |= (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0); //preskaler 128		#define REF_256 (1<<REFS1)|(1<<REFS0)
										  	  	  	  	  	  	  	  //#define REF_VCC (1<<REFS0)
	ADMUX |=  REF_VCC;  //REF_VCC;//REF_256;
}

uint16_t ADC_Measure(){
	ADMUX |= (1<<MUX2) | (1<<MUX0); //(ADMUX & 0xb11111000) | kanal;

	ADCSRA |= (1<<ADSC);

	while( ADCSRA & (1<<ADSC) );

	return ADC;
}




