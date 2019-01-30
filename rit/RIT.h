#ifndef __RIT_H
#define __RIT_H

#include "../adc/adc.h"

/* init_RIT.c */
extern uint32_t init_RIT( uint32_t RITInterval );
extern void enable_RIT( void );
extern void disable_RIT( void );
extern void reset_RIT( void );
/* IRQ_RIT.c */
extern void RIT_IRQHandler (void);

//Buttons functions
void handleButton0 (void);
void handleButton1 (void);
void handleButton2 (void);
void onButton0Pressed(void);
void onButton1Pressed(void);
void onButton2Pressed(void);

#endif /* end __RIT_H */
