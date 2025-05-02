#include <pic18f458.h>

// Configuration bits (these are examples — adapt to your needs)
#pragma config FOSC = HS
#pragma config WDT = OFF
#pragma config LVP = OFF

void main(void)
{
    TRISCbits.TRISC2 = 0;     // Set RC2 as output (PWM output pin)
    PR2 = 74;                 // Set PWM period (sets frequency)
    
    CCP1CON = 0b00001100;     // Configure CCP1 in PWM mode
    CCPR1L = 18;              // Set duty cycle (high 8 bits)
    CCP1CONbits.DC1B1 = 0;    // Set duty cycle (low 2 bits)
    CCP1CONbits.DC1B0 = 0;

    T2CON = 0b00000101;       // Timer2 ON, prescaler 1:4
    TMR2 = 0;                 // Clear Timer2

    while (1)
    {
        // PWM runs independently once set up
    }
}
