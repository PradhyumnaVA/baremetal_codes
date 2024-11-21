#include "lpc17xx.h" // Include LPC17xx header file

void delayMicerosecond(int m_sec){
    unsigned int i;
    for(i=0; i<(m_sec*100); i++);
}

int main() {
	
    unsigned int j; 
    // Set P0.19 and P0.21 as output
    LPC_GPIO0->FIODIR |= (1 << 19) | (1 << 21); // setting bit 19 and 21 to 1

    while (1) {
        // setting the outputs of pins 19 and 21 to 1
        LPC_GPIO0->FIOSET |= (1 << 19) | (1 << 21);

        // delay 
        // for(j=0;j<100000;j++);
        delayMicerosecond(1000);

        // setting the outputs of pins 19 and 21 to 0
        LPC_GPIO0->FIOCLR |= (1 << 19) | (1 << 21);
        
        for(j=0;j<100000;j++);
    }
}