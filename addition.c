#include <xc.h>

void main(void) {
    unsigned int i,x,y;
    
    TRISB=0;
    LATB=0;
    
    x=0x04;
    y=0x05;
    i=x+y;
    
    PORTC=x;
    PORTD=y;
    PORTB=i;
    
    return;
}