#include <xc.h>
#include <stdint.h>
#include <PIC18F4550.h>

// Configuration Bits
#pragma config FOSC = HS       // High-speed Oscillator
#pragma config WDT = OFF       // Watchdog Timer off
#pragma config LVP = OFF       // Low-voltage Programming off
#pragma config PBADEN = OFF    // Disable PORTB analog on reset

#define _XTAL_FREQ 8000000     // 8MHz external crystal

// LCD pin definitions
#define LCD_DATA PORTD
#define rs PORTEbits.RE0
#define rw PORTEbits.RE1
#define en PORTEbits.RE2

// Function Prototypes
void ADC_Init(void);
unsigned int Get_ADC_Result(void);
void msdelay(unsigned int time);
void init_LCD(void);
void LCD_command(unsigned char cmd);
void LCD_data(unsigned char data);
void LCD_write_string(char *str);

// Main Function
void main(void)
{
    char msg1[] = "LM35 Interface";
    char msg2[] = "Temp.:";
    char msg3[] = {0xDF, 'C', '\0'};  // Degree symbol + 'C'
    
    unsigned char Hundreds, Tens, Ones;
    unsigned int adc_val;
    unsigned char temp;

    TRISD = 0x00;      // LCD data lines
    TRISE = 0x00;      // LCD control lines
    ADCON1 = 0x0F;     // Default all as digital, overridden by ADC_Init()

    ADC_Init();
    init_LCD();

    LCD_write_string(msg1);
    LCD_command(0xC0);  // Move to second line
    LCD_write_string(msg2);

    while (1)
    {
        adc_val = Get_ADC_Result(); // 10-bit ADC result from AN0

        // Convert ADC result to temperature in Celsius:
        // ADC step = 5V / 1024 ≈ 4.88mV
        // LM35 output = 10mV/°C → Temp = ADC × 4.88 / 10 = ADC × 0.488
        temp = (adc_val * 488) / 1000;

        // Display result on LCD
        LCD_command(0xC7);  // Position cursor after "Temp.:"

        Hundreds = (temp / 100) + 0x30;
        LCD_data(Hundreds);

        Tens = ((temp % 100) / 10) + 0x30;
        LCD_data(Tens);

        Ones = (temp % 10) + 0x30;
        LCD_data(Ones);

        LCD_write_string(msg3);  // Display "°C"
        msdelay(500);
    }
}

// ADC Initialization
void ADC_Init(void)
{
    ADCON0 = 0x01; // ADC ON, Channel 0 (AN0)
    ADCON1 = 0x0E; // Set AN0 as analog, others digital
    ADCON2 = 0xA9; // Right justified, 12 TAD, Fosc/8
}

// Get ADC Result from AN0
unsigned int Get_ADC_Result(void)
{
    ADCON0bits.GO = 1;             // Start conversion
    while (ADCON0bits.GO);         // Wait for completion
    return ((ADRESH << 8) + ADRESL);  // Combine high and low bytes
}

// Delay in milliseconds (approximate)
void msdelay(unsigned int time)
{
    while (time--)
    {
        __delay_ms(1);
    }
}

// Initialize 16x2 LCD
void init_LCD(void)
{
    LCD_command(0x38); // 8-bit, 2 line, 5x7 matrix
    msdelay(5);
    LCD_command(0x0C); // Display ON, Cursor OFF
    msdelay(5);
    LCD_command(0x01); // Clear display
    msdelay(5);
    LCD_command(0x80); // Move cursor to 1st line
    msdelay(5);
}

// Send Command to LCD
void LCD_command(unsigned char cmd)
{
    LCD_DATA = cmd;
    rs = 0;
    rw = 0;
    en = 1;
    msdelay(2);
    en = 0;
}

// Send Data to LCD
void LCD_data(unsigned char data)
{
    LCD_DATA = data;
    rs = 1;
    rw = 0;
    en = 1;
    msdelay(2);
    en = 0;
}

// Write String to LCD
void LCD_write_string(char *str)
{
    while (*str != '\0')
    {
        LCD_data(*str++);
    }
}
