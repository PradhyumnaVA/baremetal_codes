#include "lpc17xx.h" // Include LPC17xx header file

int main() {
	
    unsigned int pin1_state=0, pin2_state=0;
    
    // Set P0.19 and P0.21 as output
    LPC_GPIO0->FIODIR |= (1 << 19) | (1 << 21); // setting bit 19 and 21 to 1
    
    // Set P2.10 and P2.12 as input &= ~(1 << 5)
    LPC_GPIO2->FIODIR &= ~(1 << 10); //| ~(1 << 12);

    while (1) {
            // reading input from pin P2.10 and storing in pin1_state
            pin1_state = (LPC_GPIO2->FIOPIN & (1 << 10)) >> 10;
						
            
            // setting state of led connected to P0.19 
            // based on the state of the switch
            switch(pin1_state){
                case 1: 
                    LPC_GPIO0->FIOSET |= (1 << 19);
                    break;

                case 0:
                    LPC_GPIO0->FIOCLR |= (1 << 19);
                    break;

                default:
                    LPC_GPIO0->FIOCLR |= (1 << 19) | (1 << 21);
                    break;
            }
            
    }
}