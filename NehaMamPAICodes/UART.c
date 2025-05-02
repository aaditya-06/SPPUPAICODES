#include <xc.h>

// CONFIG
#pragma config FOSC = HS     // High Speed Oscillator
#pragma config WDT = OFF     // Watchdog Timer off
#pragma config LVP = OFF     // Low Voltage Programming off

#define _XTAL_FREQ 8000000   // Define crystal frequency

void main()
{
    unsigned char a[] = "WELCOME";  // String to transmit
    int i;

    TRISB = 0x00;           // Set PORTB as output (optional, not used here)
    TRISCbits.TRISC6 = 0;   // TX pin as output
    TRISCbits.TRISC7 = 1;   // RX pin as input (not used, but good practice)

    SPBRG = 0x4D;           // Baud rate for 9600 @ 8MHz, BRGH = 0
    TXSTAbits.BRGH = 0;     // Low speed
    TXSTAbits.SYNC = 0;     // Asynchronous mode
    RCSTAbits.SPEN = 1;     // Enable Serial Port (TX/ RX)
    TXSTAbits.TXEN = 1;     // Enable transmitter

    for (i = 0; a[i] != '\0'; i++)
    {
        while (!PIR1bits.TXIF);  // Wait for TXREG to be empty
        TXREG = a[i];            // Transmit character
    }

    while(1); // Infinite loop
}
