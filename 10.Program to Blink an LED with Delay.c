// Include standard header for PIC
#include <xc.h>

// CONFIGURATION BITS (example for PIC18F4550)
// You must set proper CONFIG for your device
#pragma config FOSC = HS    // High-Speed Oscillator
#pragma config WDT = OFF    // Watchdog Timer disabled
#pragma config LVP = OFF    // Low Voltage Programming disabled
#pragma config PBADEN = OFF // PORTB<4:0> pins are digital I/O on Reset
#pragma config MCLRE = ON   // MCLR pin enabled

// Define CPU frequency for delay calculations
#define _XTAL_FREQ 20000000  // 20 MHz crystal (adjust if different)

void main(void) {
    // Step 1: Configure the pin connected to LED as output
    TRISD0 = 0;  // Make RD0 an output pin (0 = Output)

    // Step 2: Initially turn off the LED
    LATD0 = 0;   // Clear RD0 (LED OFF)

    // Step 3: Loop forever to blink the LED
    while(1) {
        LATD0 = 1;    // Turn ON LED
        __delay_ms(500);  // Delay 500 milliseconds

        LATD0 = 0;    // Turn OFF LED
        __delay_ms(500);  // Delay 500 milliseconds
    }
}