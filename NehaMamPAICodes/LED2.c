#include <xc.h>

// Configuration bits (you must configure them based on your setup)
#pragma config FOSC = HS    // High-speed oscillator
#pragma config WDTE = OFF   // Watchdog Timer off
#pragma config LVP = OFF    // Low-voltage programming off

void delay(void);

void main(void) {
    TRISB = 0x00; // Set all PORTB pins as output

    while(1) {
        PORTB = 0xFF;  // Turn ON all LEDs
        delay();

        PORTB = 0x00;  // Turn OFF all LEDs
        delay();
    }
}

void delay(void) {
    for (volatile long i = 0; i < 20000; i++); // crude delay
}
