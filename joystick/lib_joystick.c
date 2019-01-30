#include "lpc17xx.h"
#include "joystick.h"

/*----------------------------------------------------------------------------
  Function that initializes joysticks and switch them off
 *----------------------------------------------------------------------------*/

void joystick_init(void) {

	//We don't have to do something strange since 
	//there are no interrupts and the direction and the mode
	//are the only things that we need to setup.
	LPC_PINCON->PINSEL3 &= ~(3<<18);	//PIN mode GPIO (00b value per P1.25)
	LPC_PINCON->PINSEL3 &= ~(3<<20);	//PIN mode GPIO (00b value per P1.25)
	LPC_PINCON->PINSEL3 &= ~(3<<22);	//PIN mode GPIO (00b value per P1.25)
	LPC_PINCON->PINSEL3 &= ~(3<<24);	//PIN mode GPIO (00b value per P1.25)
	LPC_PINCON->PINSEL3 &= ~(3<<26);	//PIN mode GPIO (00b value per P1.25)


	LPC_GPIO1->FIODIR   &= ~(1<<J_BIT_SELECT);	//P1.25 Input (joysticks on PORT1 defined as Input)
	LPC_GPIO1->FIODIR   &= ~(1<<J_BIT_DOWN);	//P1.25 Input (joysticks on PORT1 defined as Input)
	LPC_GPIO1->FIODIR   &= ~(1<<J_BIT_LEFT);	//P1.25 Input (joysticks on PORT1 defined as Input)
	LPC_GPIO1->FIODIR   &= ~(1<<J_BIT_RIGHT);	//P1.25 Input (joysticks on PORT1 defined as Input)
	LPC_GPIO1->FIODIR   &= ~(1<<J_BIT_UP);	//P1.25 Input (joysticks on PORT1 defined as Input)
	
	//Untested version (should be the same)
	//LPC_PINCON->PINSEL3 &= ~((3<<18) | (3<<20) | (3<<22) | (3<<24) | (3<<26));
	//LPC_GPIO1->FIODIR   &= ~((1<<J_BIT_SELECT) | (1<<J_BIT_DOWN) | (1<<J_BIT_LEFT) | (1<<J_BIT_RIGHT) | (1<<J_BIT_UP));

}


