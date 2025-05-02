#include <xc.h>  // Correct usage, no semicolon

// Configuration bits (you must configure these properly for your hardware setup)
// These are just placeholders, adjust to your actual oscillator and settings
#pragma config FOSC = HS     // High Speed Oscillator
#pragma config WDTE = OFF    // Watchdog Timer Disable

#define mybit PORTBbits.RB4

void Todelay(void);

void main(void) {
    TRISBbits.TRISB4 = 0;  // Set RB4 as output

    while(1) {
        mybit = 1;     // Turn LED ON
        Todelay();     // Delay
        mybit = 0;     // Turn LED OFF
        Todelay();     // Delay
    }
}

void Todelay(void) {
    T0CON = 0x07;       // Timer0 ON, 16-bit, internal clock, prescaler 1:256
    T0CONbits.TMR0ON = 0; // Turn OFF timer to safely load value

    TMR0H = 0xFF;       // High byte
    TMR0L = 0xEE;       // Low byte -> this gives small delay (~1ms or so at 4 MHz)

    INTCONbits.TMR0IF = 0; // Clear overflow flag
    T0CONbits.TMR0ON = 1;  // Turn Timer0 ON

    while (INTCONbits.TMR0IF == 0);  // Wait for overflow

    T0CONbits.TMR0ON = 0;  // Stop Timer0
    INTCONbits.TMR0IF = 0; // Clear flag again (safety)
}
