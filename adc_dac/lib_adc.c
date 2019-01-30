#include "lpc17xx.h"
#include "adc.h"


void ADC_init (void) {

	//The pin need to be setup to that functionality.
	//We are forcing some bits.
	LPC_PINCON->PINSEL3 |=  (3UL<<30);      /* P1.31 is AD0.5                     */

	//Supply power to the right unit
	LPC_SC->PCONP       |=  (1<<12);		//Enable power to ADC block

	//Select the functionality of the pin using control register
	LPC_ADC->ADCR        =  (1<< 5) |	// Select AD0.5 pin
                          (4<< 8) |		// ADC clock is 25MHz/5 (This value + 1 is the divisor of the clock)
                          (1<<21);		// Enable ADC (Set to 0 to put it in power down mode)

	//Enabling global interrupt: every event will trigger an interrupt
	LPC_ADC->ADINTEN     =  (1<< 8);		// Global enable interrupt. Other bits [0:7] are used to interrupt single channels

	NVIC_EnableIRQ(ADC_IRQn);				// Enable ADC Interrupt
}

//We use the control register to make the conversion start.
//There is a nice part on table 532 of manual that concert
//START values in the ADCR. 
//We are using 001 that is called START CONVERSION NOW
void ADC_start_conversion (void) {
	LPC_ADC->ADCR |=  (1<<24);			// Start A/D Conversion 				*/
}
