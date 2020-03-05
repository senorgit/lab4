#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "driverlib/sysctl.h"

#define 	MASK		0x08 //Define MASK as LED variable.  In this case it's 0x08 or GREEn LED

void PortFunctionInit(void)
{
  	volatile uint32_t ui32Loop;   
	  // Enable the GPIO port that is used for the on-board LED.    
    SYSCTL_RCGC2_R = SYSCTL_RCGC2_GPIOF;
    
    // Do a dummy read to insert a few cycles after enabling the peripheral.    
    ui32Loop = SYSCTL_RCGC2_R;

    // Enable the GPIO pin for the red LED (PF1).  Set the direction as output, and
    // enable the GPIO pin for digital function.    
    GPIO_PORTF_DIR_R |= MASK;
    GPIO_PORTF_DEN_R |= MASK;
}


int main(void)
{	
		//initialize the GPIO ports	
		PortFunctionInit();
	
    // Turn on the LED.
    GPIO_PORTF_DATA_R |= MASK;
	
    // Loop forever.    
    while(1)
    {
        // Delay for a bit.
				SysCtlDelay(10000000);	

        // Toggle the LED.
        GPIO_PORTF_DATA_R ^= MASK;				
    }
}
