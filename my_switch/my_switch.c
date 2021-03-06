#include <stdint.h>
#include "inc/tm4c123gh6pm.h"

#define 	MASK 		0x04  //variable MASK = LED pin position. 0x02 = RED, 0x04=BLUE and 0x08 = GREEN

void PortFunctionInit(void)
{
		volatile uint32_t ui32Loop;   
	
		// Enable the clock of the GPIO port that is used for the on-board LED and switch.
    SYSCTL_RCGC2_R = SYSCTL_RCGC2_GPIOF;

    //
    // Do a dummy read to insert a few cycles after enabling the peripheral.
    //
    ui32Loop = SYSCTL_RCGC2_R;

		// Unlock GPIO Port F
		GPIO_PORTF_LOCK_R = 0x4C4F434B;   
		GPIO_PORTF_CR_R |= 0x01;           // allow changes to PF0

    // Set the direction of LED as output
    GPIO_PORTF_DIR_R |= MASK;
	
		// Set the direction of PF0 (SW2) as input by clearing the bit
    GPIO_PORTF_DIR_R &= ~0x01;
	
    // Enable both LED and PF0 for digital function.
    GPIO_PORTF_DEN_R |= MASK + 0x01;
	
		//Enable pull-up on PF0
		GPIO_PORTF_PUR_R |= 0x01; 
}

int main(void)
{	
		//initialize the GPIO ports	
		PortFunctionInit();
	
    //
    // Loop forever.
    //
    while(1)
			{
        if((GPIO_PORTF_DATA_R&0x01)==0x01) //SW2 is NOT pressed
				{
						// Turn on the LED.
						GPIO_PORTF_DATA_R |= MASK;
				}
				else
				{
						// Turn off the LED.
						GPIO_PORTF_DATA_R &= ~MASK;
				}
    }
}
