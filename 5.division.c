#include <xc.h>

void main(void) {
    unsigned char a = 20;   // 8-bit number 1 (dividend)
    unsigned char b = 4;    // 8-bit number 2 (divisor)
    unsigned char result;   // 8-bit result is enough for division
    
    TRISD = 0;    // Set PORTD as output
    LATD = 0;     // Clear PORTD initially
    
    result = a / b;    // Perform division
    
    PORTD = result;    // Output result on PORTD
    
    while(1);    // Infinite loop to hold output
}
