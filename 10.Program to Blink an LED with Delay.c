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

// Microcontroller (PIC18FXXX) has ports like PORTD.

// Each pin can be set as input (read) or output (send signal).

// TRISD0 = 0 makes pin RD0 an output.

// LATD0 = 1 sets RD0 HIGH (LED ON).

// LATD0 = 0 sets RD0 LOW (LED OFF).

// __delay_ms(500) is a built-in function (XC8) that creates a 500ms pause.

// Thus, the LED turns ON, waits 0.5 sec, turns OFF, waits 0.5 sec — and repeats forever.

// 🖥 Software Setup (MPLAB X IDE):
// Create a new Standalone Project for your PIC18F device.

// Select XC8 Compiler.

// Paste the code into main.c.

// Set the oscillator frequency in code and Proteus the same (e.g., 20MHz).

// Build ➔ Program ➔ Done!

// 🛠 Hardware Setup (Proteus):
// Open Proteus.

// Place PIC18FXXX device (e.g., PIC18F4550).

// Connect a 20MHz crystal oscillator between OSC1 and OSC2 pins, with two 22pF capacitors to ground.

// Connect RD0 pin to:

// LED (anode to RD0)

// Series 330Ω resistor

// Ground

// VDD and VSS pins connected to power and ground properly.

//  Run simulation — LED will blink ON and OFF with 0.5s delay.