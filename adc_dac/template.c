
//-------------------------------------------------------------------------
	

//These number represent values of the sin. Depending on the frequency are saved on the DAC the sound made by the board will be different.
uint16_t SinTable[45] =
{
    410, 467, 523, 576, 627, 673, 714, 749, 778,
    799, 813, 819, 817, 807, 789, 764, 732, 694, 
    650, 602, 550, 495, 438, 381, 324, 270, 217,
    169, 125, 87 , 55 , 30 , 12 , 2  , 0  , 6  ,   
    20 , 41 , 70 , 105, 146, 193, 243, 297, 353
};


//This handler needs to be called X times every second in order to sound properly
//45 values are present on the table
//25Mhz is the frequency of the processor
//0xFFF is the maximum value that we can read
void TIMER0_IRQHandler (void){

	static int ticks=0;
	/* DAC management */
	LPC_DAC->DACR = SinTable[ticks]<<6;
	ticks++;
	if(ticks==45) ticks=0;


	LPC_TIM0->IR = 1;			/* clear interrupt flag */
	return;
}

//-------------------------------------------------------------------------

//This handler need to be called every 50ms (RIT)
//When conversion will be ready it will trigger another interrupt
void RIT_IRQHandler (void){
	ADC_start_conversion();
}

//-------------------------------------------------------------------------


/*----------------------------------------------------------------------------
  A/D IRQ: Executed when A/D Conversion is ready (signal from ADC peripheral)
 *----------------------------------------------------------------------------*/
unsigned short AD_current;
unsigned short AD_last = 0xFF;     /* Last converted value               */

// k=1/f'*f/n  k=f/(f'*n) k=25MHz/(f'*45)  -> 45 is the values that make a complete sin
//const int freqs[8]={4240,3779,3367,3175,2834,2525,2249,2120};
/* 
131Hz		k=4240 C3
147Hz		k=3779
165Hz		k=3367
175Hz		k=3175
196Hz		k=2834
220Hz		k=2525
247Hz		k=2249
262Hz		k=2120 C4
*/
const int freqs[8]={2120,1890,1684,1592,1417,1263,1125,1062};
/*
262Hz	k=2120		c4
294Hz	k=1890
330Hz	k=1684
349Hz	k=1592
392Hz	k=1417
440Hz	k=1263
494Hz	k=1125
523Hz	k=1062		c5
*/

void ADC_IRQHandler(void) {
  	
	//We are reading the conversion result.
  AD_current = ((LPC_ADC->ADGDR>>4) & 0xFFF);	//First 4 bits are useless
												//4096 bits are possible (12bit)
												//12 bits (0xFFF) are saved because I only need them

	if(AD_current != AD_last){ //If value has changed
		//8 possible index. 8 possible leds. I use a proportion to retrieve the right index.
		LED_Off(AD_last*7/0xFFF);		// ad_last : AD_max = x : 7 		LED_Off((AD_last*7/0xFFF));	
		LED_On(AD_current*7/0xFFF);		// ad_current : AD_max = x : 7 		LED_On((AD_current*7/0xFFF));	

		disable_timer(0);
		reset_timer(0);
		init_timer(0,freqs[AD_current*7/0xFFF]);	//The frequency of the timer depends on the sound we want to achieve
		enable_timer(0);
		
		AD_last = AD_current;
	}
}












 