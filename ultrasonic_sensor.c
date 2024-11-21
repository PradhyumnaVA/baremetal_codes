#include "lpc17xx.h" // Include LPC17xx header file

#define high 1
#define low 0

#define TrigPin 29
#define EchoPin 27

void delayMicerosecond(int m_sec){
    unsigned int i;
    for(i=0; i<(m_sec*100); i++);
}

void DigWrite(int Pin_number, int Pin_state){
    switch(Pin_state){
        case high:
            LPC_GPIO1->FIOSET |= (1 << Pin_number);
        case low:
            LPC_GPIO1->FIOCLR |= (1 << Pin_number);
    }
}

int echo_duration(int Pin_number){
    unsigned int count=0;
    unsigned int pin_state;
    while(1){
        pin_state = (LPC_GPIO2->FIOPIN & (1 << Pin_number)) >> Pin_number;
        if(!pin_state) count++;
        else if (pin_state){
            break;
        } 
    }
    return(count*100);
}

int main() {
    float distance; 
    unsigned int duration;
    // output
    LPC_GPIO1->FIODIR |= (1 << TrigPin);
    // input
    LPC_GPIO1->FIODIR &= ~(1 << EchoPin);

    while(1){
        // clear the trigger pin
        DigWrite(TrigPin,low);
        delayMicerosecond(2);

        // send a pulse for 10us
        DigWrite(TrigPin,high);
        delayMicerosecond(10);
        DigWrite(TrigPin,low);

        // read Echo pin, get the duration in microsecond
        duration = echo_duration(EchoPin);

        // calculate distance in cm
        distance = duration * 0.034/2;
    }
}