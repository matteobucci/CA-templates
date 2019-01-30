#include "button.h"
#include "lpc17xx.h"

extern int down0;
extern int down1;
extern int down2;

/* This is called when bit 10 is deselected */
void EINT0_IRQHandler (void){

	NVIC_DisableIRQ(EINT0_IRQn);				//Disable interrupt for this button
	LPC_PINCON->PINSEL4    &= ~(1 << 20);		//GPIO MODE: Allows read values of pins
	down0 =1;									//RIT Handler will know that the button is pressed

	LPC_SC->EXTINT &= (1 << 0);					//Clear pending interrupts
}


/* This is called when bit 11 is deselected */
void EINT1_IRQHandler (void){

	NVIC_DisableIRQ(EINT1_IRQn);				//Disable interrupt for this button
	LPC_PINCON->PINSEL4    &= ~(1 << 22);		//GPIO MODE: Allows read values of pins
	down1 =1;									//RIT Handler will know that the button is pressed 

	LPC_SC->EXTINT &= (1 << 1);					//Clear pending interrupts
}

/* This is called when bit 12 is deselected */
void EINT2_IRQHandler (void){

	NVIC_DisableIRQ(EINT2_IRQn);				//Disable interrupt for this button
	LPC_PINCON->PINSEL4    &= ~(1 << 24);		//GPIO MODE: Allows read values of pins
	down2 =1;									//RIT Handler will know that the button is pressed

	LPC_SC->EXTINT &= (1 << 2);					//Clear pending interrupts
}


