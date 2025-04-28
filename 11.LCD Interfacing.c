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

// Explanation of Key Code Parts
// LCD Pin Configuration:

// RS (Register Select): Selects whether you are sending command (RS=0) or data (RS=1).

// E (Enable): Used to latch the data into the LCD on the rising edge.

// D4-D7 (Data Pins): Used to send 4-bit data (higher and lower nibbles).

// Functions:

// LCD_Command: Sends a command to the LCD (like clearing the display or moving the cursor).

// LCD_Data: Sends a data byte (used for characters).

// LCD_Init: Initializes the LCD (sets it up for 4-bit mode, turns on display).

// LCD_String: Displays a string of characters on the LCD.

// Main Loop:

// The program first initializes the LCD, clears the screen, and displays a string on the first line.

// Then it moves the cursor to the second line and displays another string.

// 4. MPLAB X IDE Setup
// Create New Project:

// Open MPLAB X IDE.

// Select File ➔ New Project ➔ Standalone Project.

// Select PIC18F458 as your device.

// Choose XC8 Compiler.

// Code Implementation:

// Create a new file called main.c.

// Copy and paste the code provided above.

// Configuration Bits:

// Set the correct configuration bits for your PIC18F458 (such as the oscillator and watchdog settings).
// Example configuration bits:

// c
// Copy
// Edit
// #pragma config FOSC = HS    // High-Speed Oscillator
// #pragma config WDT = OFF    // Watchdog Timer disabled
// #pragma config LVP = OFF    // Low Voltage Programming disabled
// Build and Program:

// Build the project (hammer icon).

// Connect your PIC18F458 to the programmer (e.g., PICkit 3).

// Click Make and Program Device (green arrow) to upload the code to your PIC.

// 5. Proteus Simulation Setup
// Open Proteus:

// Create a new project and add the PIC18F458.

// Add a 16x2 LCD module.

// Wire the LCD's RS, RW, E, D4, D5, D6, D7 pins to PORTC of the PIC18F458.

// Connect the VSS pin of the LCD to ground and VDD to 5V.

// Optionally, you can add a potentiometer to control the contrast (connected to the V0 pin).

// Run Simulation:

// Click Run in Proteus. You should see the text "Hello, PIC18F458!" on the first line and "LCD Interfacing" on the second line of the LCD.

// 6. Conclusion
// This program shows how to interface a 16x2 LCD with PIC18F458 using a 4-bit mode. The code initializes the LCD, sends commands, and displays text.
//  You can use MPLAB X IDE to compile and program the PIC, and Proteus to simulate the circuit.
