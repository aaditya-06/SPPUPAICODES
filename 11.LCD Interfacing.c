// Embedded C code to initialize and control a 16x2 LCD connected to 
// a PIC18F458 using the 4-bit mode for communication.

#include <xc.h>  // Include the standard header for PIC
#define _XTAL_FREQ 20000000  // 20 MHz Oscillator frequency (adjust as needed)

// Define LCD control pins
#define RS LATCbits.LATC0   // Register Select pin
#define E  LATCbits.LATC1   // Enable pin

// Define LCD data pins (D4-D7)
#define D4 LATCbits.LATC2
#define D5 LATCbits.LATC3
#define D6 LATCbits.LATC4
#define D7 LATCbits.LATC5

// Function to send a command to the LCD (4-bit mode)
void LCD_Command(unsigned char cmd) {
    RS = 0;                // Command mode
    LATC = (LATC & 0xC0) | (cmd >> 4);  // Send upper nibble
    E = 1;                  // Generate Enable pulse
    __delay_ms(2);
    E = 0;
    
    LATC = (LATC & 0xC0) | (cmd & 0x0F);  // Send lower nibble
    E = 1;
    __delay_ms(2);
    E = 0;
}

// Function to send data to the LCD (4-bit mode)
void LCD_Data(unsigned char data) {
    RS = 1;                // Data mode
    LATC = (LATC & 0xC0) | (data >> 4);  // Send upper nibble
    E = 1;                  // Generate Enable pulse
    __delay_ms(2);
    E = 0;
    
    LATC = (LATC & 0xC0) | (data & 0x0F);  // Send lower nibble
    E = 1;
    __delay_ms(2);
    E = 0;
}

// Function to initialize the LCD
void LCD_Init() {
    TRISC = 0x00;   // Set PORTC as output for control and data pins
    __delay_ms(20);  // Wait for LCD to power up

    LCD_Command(0x02); // Initialize LCD in 4-bit mode
    LCD_Command(0x28); // 2 lines, 5x7 matrix
    LCD_Command(0x0C); // Display ON, Cursor OFF
    LCD_Command(0x06); // Entry Mode, Increment cursor
    LCD_Command(0x01); // Clear display
    __delay_ms(2);     // Delay for clear display
}

// Function to display a string on the LCD
void LCD_String(const char *str) {
    while(*str) {
        LCD_Data(*str);   // Send each character to LCD
        str++;            // Move to the next character
    }
}

void main(void) {
    // Initialize the LCD
    LCD_Init();

    // Display messages on LCD
    LCD_String("Hello, PIC18F458!");  // Display first line
    LCD_Command(0xC0);                 // Move cursor to second line
    LCD_String("LCD Interfacing");

    while(1);  // Infinite loop
}
