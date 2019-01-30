#include "lpc17xx.h"
#include "timer.h"

/******************************************************************************
** Function name:		enable_timer
**
** Descriptions:		Enable timer
**
** parameters:			timer number: 0 or 1 or 2
** Returned value:		None
**
******************************************************************************/
void enable_timer( uint8_t timer_num ){
	
	switch(timer_num){
		case 0:
			LPC_TIM0->TCR = 1;
		break;
		
		case 1:
			LPC_TIM1->TCR = 1;
		break;
		
		case 2:
			LPC_TIM2->TCR = 1;
		break;
		
		case 3:
			LPC_TIM3->TCR = 1;
		break;
	}
	
	return;
}

/******************************************************************************
** Function name:		disable_timer
**
** Descriptions:		Disable timer
**
** parameters:			timer number: 0 or 1 or 2
** Returned value:		None
**
******************************************************************************/
void disable_timer( uint8_t timer_num ){
	
	switch(timer_num){
		case 0:
			LPC_TIM0->TCR = 0;
		break;
		
		case 1:
			LPC_TIM1->TCR = 0;
		break;
		
		case 2:
			LPC_TIM2->TCR = 0;
		break;
		
		case 3:
			LPC_TIM3->TCR = 0;
		break;
	}
	
  return;
}

/******************************************************************************
** Function name:		reset_timer
**
** Descriptions:		Reset timer
**
** parameters:			timer number: 0 or 1 or 2
** Returned value:		None
**
******************************************************************************/
void reset_timer( uint8_t timer_num )
{
  uint32_t regVal;
	
	switch(timer_num){
		case 0:
			regVal = LPC_TIM0->TCR;
			regVal |= 0x02;
			LPC_TIM0->TCR = regVal;
		break;
		
		case 1:
			regVal = LPC_TIM1->TCR;
			regVal |= 0x02;
			LPC_TIM1->TCR = regVal;
		break;
		
		case 2:
			regVal = LPC_TIM2->TCR;
			regVal |= 0x02;
			LPC_TIM2->TCR = regVal;
		break;
		
		case 3:
			regVal = LPC_TIM3->TCR;
			regVal |= 0x02;
			LPC_TIM3->TCR = regVal;
		break;
	}

  return;
}

uint32_t init_timer ( uint8_t timer_num, uint32_t TimerInterval )
{
	/**
	First bit	-> Interrupt ( 0 disabled 1 enabled )
	Second bit	-> Reset ( 0 enabled 1 disabled )
	Third bit	-> Stop (0 enabled 1 disabled )
	7 possible values
	**/
	switch(timer_num){
		case 0:
			LPC_TIM0->MR0 = TimerInterval;
			LPC_TIM0->MCR = 3;				/* Interrupt and Reset on MR1 */
			NVIC_EnableIRQ(TIMER0_IRQn);
			return (1);

		case 1:
			LPC_TIM1->MR0 = TimerInterval;
			LPC_TIM1->MCR = 3;				/* Interrupt and Reset on MR1 */
			NVIC_EnableIRQ(TIMER1_IRQn);
			return (1);
		
		case 2:
			LPC_TIM2->MR0 = TimerInterval;
			LPC_TIM2->MCR = 3;				/* Interrupt and Reset on MR1 */
			NVIC_EnableIRQ(TIMER2_IRQn);
			return (1);
			
		case 3:
		LPC_TIM3->MR0 = TimerInterval;
		LPC_TIM3->MCR = 3;				/* Interrupt and Reset on MR1 */
		NVIC_EnableIRQ(TIMER3_IRQn);
		return (1);
	}
	
  return (0);
}

uint32_t is_timer_enabled ( uint8_t timer_num){
	
	uint32_t regVal = 0;
	
	switch(timer_num){
		case 0:
			regVal = LPC_TIM0->TCR;
			break;
		case 1:
			regVal = LPC_TIM1->TCR;
			break;		
		case 2:
			regVal = LPC_TIM2->TCR;
			break;
		case 3:
			regVal = LPC_TIM3->TCR;
			break;
	}

	regVal &= 0x00000001;
	return regVal; //Should be 1 if enabled, 0 if disabled
}

uint32_t read_timer_value ( uint8_t timer_num){
	switch(timer_num){
		case 0:
			return LPC_TIM0->TC;
		case 1:
			return LPC_TIM1->TC;
		case 2:
			return LPC_TIM2->TC;
		case 3:
			return LPC_TIM3->TC;
	}
	return 0;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
