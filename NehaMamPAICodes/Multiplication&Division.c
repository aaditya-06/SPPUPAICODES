#include <xc.h>           // Use the correct include
#include <pic18f4550.h>   // MCU-specific header
#pragma config FOSC = HS  // Adjust config bits as per your hardware
#pragma config WDT = OFF
#pragma config LVP = OFF

#define _XTAL_FREQ 8000000 // Set your oscillator frequency (example: 8 MHz)

int main(void) {
    int num1 = 0x06, num2 = 0x02;
    int d = 0;
    d = num1 / num2; // Simple division

    TRISD = 0x00;     // PORTD as output
    PORTD = d;        // Output result

    int n1 = 0x23, n2 = 0x10;
    int prod = 0;

    for (int i = 0; i < n2; i++) {
        prod += n1;  // Multiply using repeated addition
    }

    TRISB = 0x00;     // PORTB as output
    PORTB = prod;     // Output product

    while(1);         // Infinite loop to maintain output

    return 0;
}
