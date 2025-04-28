#include <xc.h>


void main(void) {
    unsigned char a = 10;   // 8-bit number 1 (0 to 255)
    unsigned char b = 12;   // 8-bit number 2 (0 to 255)
    unsigned int result;    // 16-bit to store the product (because 8-bit × 8-bit = max 65535)
    
    TRISD = 0;    
    LATD = 0;
    
    result = a * b;    // Perform multiplication
    
    PORTD = result;
    
    while(1);    // Infinite loop to hold output
}
