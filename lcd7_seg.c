	/*Port2 Connected to data lines of all 7 segement displays and port1 pin 27 for enabling display
	   a
	  ----
	f|  g |b
	 |----|
	e|    |c
	  ----  . dot
	   d
	
	*/
	
#include <LPC17xx.h>
unsigned char data[]={0x000000c0, 0x000000f9, 0x000000a4, 0x000000b0, 0x00000099};

int main(void) {
    unsigned int count1 = 0, count2=0;
	unsigned int i,j;

    
    // Set Port 2 as output for segment data
    LPC_GPIO2->FIODIR = 0x000000FF; // Set lower 8 bits as output
    
    // Set Pin 27 and Pin 29 on Port 1 as output for enabling displays
    LPC_GPIO1->FIODIR |= (1 << 27) | (1 << 29); // Enable pins 27 and 29

    while (1) {
        if (count1 > 4){ 
					count1 = 0;
					//count2++;
				}
				else if (count1>4)			// Reset count if it exceeds available data
				for(i=0;i<2000;i++){
        // Enable first display (Pin 27)
        LPC_GPIO2->FIOPIN = data[count1]; // Send data to Port 2
        LPC_GPIO1->FIOSET = (1 << 27); // Set Pin 27 high
        for (j = 0; j < 500; j++); // Delay
        LPC_GPIO1->FIOCLR = (1 << 27); // Set Pin 27 low
					
				// Enable second display (Pin 29)
        LPC_GPIO2->FIOPIN = data[count2]; // Send same data or different if needed
        LPC_GPIO1->FIOSET = (1 << 29); // Set Pin 29 high
        for (j = 0; j < 500; j++); // Delay
        LPC_GPIO1->FIOCLR = (1 << 29); // Set Pin 29 low
        }
        count1++; // Move to next digit
    }
}

