#include "lpc17xx.h"
#include "RIT.h"
#include "../led/led.h"
#include "../timer/timer.h"

int down0 = 0; //Button 0
int down1 = 0; //Button 1
int down2 = 0; //Button 2

void RIT_IRQHandler (void){

	/* Button management */
	handleButton0();
	handleButton1();
	handleButton2();

	/* Joystick management */
	handleJoystick();

	LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
}

void handleButton0(){

	if(down0!=0){ 
		if((LPC_GPIO2->FIOPIN & (1<<10)) == 0){ // KEY0 pressed
			down0++;				
			switch(down0){
				case 2: //Button press confirmed. Handle its action.
						onButton0Pressed();
					break;
				default:
					break;
			}
		}
		else { //Button released
			down0 = 0;			
			NVIC_EnableIRQ(EINT0_IRQn);				// Set interrupt handler for button
			LPC_PINCON->PINSEL4    |= (1 << 20);	// Select interrupt mode for button
		}
	}
}

void handleButton1(){
	if(down1!=0){ 
		if((LPC_GPIO2->FIOPIN & (1<<11)) == 0){	// KEY1 pressed
			down1++;				
			switch(down1){
				case 2: //Button press confirmed. Handle its action.
					onButton1Pressed();
					break;
				default:
					break;
			}
		}
		else {	//Button released
			down1 = 0;
			NVIC_EnableIRQ(EINT1_IRQn);				// Set interrupt handler for button
			LPC_PINCON->PINSEL4    |= (1 << 22);	// Select interrupt mode for button
		}
	}
}

void handleButton2(){
	if(down2!=0){ 
		if((LPC_GPIO2->FIOPIN & (1<<12)) == 0){	// KEY2 pressed
			down2++;				
			switch(down2){
				case 2: //Button press confirmed. Handle its action.
					onButton2Pressed();
					break;
				default:
					break;
			}
		}
		else {	//Button released
			down2 = 0;			
			NVIC_EnableIRQ(EINT2_IRQn);				// Set interrupt handler for button
			LPC_PINCON->PINSEL4    |= (1 << 24);	// Select interrupt mode for button
		}
	}
}

void onButton0Pressed(){
	//Action to perform when a debounced press happens in button0
}

void onButton1Pressed() {
	//Action to perform when a debounced press happens in button0
}

void onButton2Pressed() {
	//Action to perform when a debounced press happens in button0
}

void handleJoystick(){
	
	static int select = 0;
	static int up = 0;
	static int down = 0;
	static int left = 0;
	static int right = 0;
	
	//Handle SELECT
	if((LPC_GPIO1->FIOPIN & (1<<J_BIT_SELECT)) == 0){	// Joytick Select pressed 
		select++;
		switch(select){
			case 1:
				onSelectPressed();
				break;
			default:
				break;
		}
	}
	else{ select = 0; }
	
	//Handle UP
	if((LPC_GPIO1->FIOPIN & (1<<J_BIT_UP)) == 0){	// Joytick Up pressed 
		up++;
		switch(up){
			case 1:
				onUpPressed();
				break;
			default:
				break;
		}
	}
	else{ up = 0; }
	
	//Handle DOWN
	if((LPC_GPIO1->FIOPIN & (1<<J_BIT_DOWN)) == 0){	// Joytick Down pressed 
		down++;
		switch(down){
			case 1:
				onDownPressed();
				break;
			default:
				break;
		}
	}
	else{ down = 0; }
	
	//Handle LEFT
	if((LPC_GPIO1->FIOPIN & (1<<J_BIT_LEFT)) == 0){	// Joytick Left pressed 
		left++;
		switch(left){
			case 1:
				onLeftPressed();
				break;
			default:
				break;
		}
	}
	else{ left = 0; }
	
	//Handle RIGHT
	if((LPC_GPIO1->FIOPIN & (1<<J_BIT_RIGHT)) == 0){	// Joytick Right pressed 
		right++;
		switch(right){
			case 1:
				onRightPressed();
				break;
			default:
				break;
		}
	}
	else{ right = 0; }
	
	
}

