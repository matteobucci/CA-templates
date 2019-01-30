#ifndef __JOYSTICK
#define __JOYSTICK

/*
	Joystick
	P1.25 Select (Active Low)
	P1.26 Down (Active Low)
	P1.27 Left (Active Low)
	P1.28 Right (Active Low)
	P1.29 Up (Active Low)
	
	Port to read
			LPC_GPIO1->FIOPIN
	Es. 
			if((LPC_GPIO1->FIOPIN & (1<<J_BIT_SELECT)) == 0){	// Joytick Select pressed 
*/

#define J_BIT_SELECT	25
#define J_BIT_DOWN		26
#define J_BIT_LEFT		27
#define J_BIT_RIGHT		28
#define J_BIT_UP		29


/* lib_joystick */
void joystick_init(void);

/* funct_joystick */
void joystick_On (unsigned int num);

void onSelectPressed(void);
void onUpPressed(void);
void onUpLongPressed(void);
void onDownPressed(void);
void onLeftPressed(void);
void onRightPressed(void);

#endif
