#include <pic18f458.h> // Correct include
#define ldata PORTB
#define rs PORTCbits.RC1
#define en PORTCbits.RC0

void delay();
void lcdcmd(unsigned char);
void lcdval(unsigned char);

void main() {
    TRISB = 0x00; // Set PORTB as output
    TRISC = 0x00; // Set PORTC as output

    // LCD initialization sequence
    lcdcmd(0x38); // 8-bit, 2 line, 5x7 matrix
    delay();
    lcdcmd(0x0E); // Display on, cursor blinking
    delay();
    lcdcmd(0x01); // Clear display
    delay();
    lcdcmd(0x06); // Entry mode - cursor increment
    delay();
    lcdcmd(0x86); // Move cursor to line 1, position 6
    delay();

    // Send characters to LCD
    lcdval('H');
    lcdval('E');
    lcdval('L');
    lcdval('L');

    while(1); // Infinite loop
}

void lcdcmd(unsigned char cmd) {
    rs = 0;
    ldata = cmd;
    en = 1;
    delay();
    en = 0;
    delay();
}

void lcdval(unsigned char data) {
    rs = 1;
    ldata = data;
    en = 1;
    delay();
    en = 0;
    delay();
}

void delay() {
    for(int i = 0; i <= 2000; i++) {
        // crude delay
    }
}
