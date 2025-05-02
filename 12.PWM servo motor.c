#include <xc.h>

// Define the clock frequency for delay calculation
#define _XTAL_FREQ 20000000  // 20 MHz for the PIC18F458

// Configure PIC18F458 for PWM output on CCP1 (RC2)
void PWM_Init() {
    // Set CCP1 as output pin (RC2)
    TRISCbits.TRISC2 = 0;

    // Configure PWM period: 50Hz (20ms period)
    // The PWM period is calculated by the formula: 
    // T = (PR2 + 1) * 4 * TOSC * (TMR2 prescaler)
    // For 50Hz PWM, PR2 = 249
    PR2 = 249;  // Set period register (for 50Hz frequency)

    // Configure TMR2 prescaler
    T2CKPS0 = 1;  // Set prescaler to 16 (prescaler options: 1, 4, 16, 64)
    T2CKPS1 = 1;

    // Start Timer2
    TMR2 = 0;  // Clear Timer2
    TMR2ON = 1;  // Enable Timer2
    
    // Configure CCP1 for PWM mode
    CCP1M3 = 1;  // PWM mode
    CCP1M2 = 1;
    CCP1M1 = 0;
    CCP1M0 = 0;

    // Set PWM duty cycle (example: 5% duty cycle for 1ms pulse)
    PWM_SetDutyCycle(10);  // 10% duty cycle (1ms pulse)
}

// Set the PWM duty cycle (Pulse Width)
void PWM_SetDutyCycle(unsigned char dutyCycle) {
    // The duty cycle is calculated using the formula:
    // Duty Cycle (%) = (CCPR1L:CCP1CON) / (PR2 + 1) * 100
    // dutyCycle value ranges from 0 to 100 (0% to 100%)

    unsigned int pwmValue = (dutyCycle * (PR2 + 1)) / 100;
    
    // Set the PWM duty cycle by writing to CCPR1L (8-bit) and CCP1CON (2-bit)
    CCPR1L = pwmValue;  // Set the high byte (CCP1L)
    CCP1CONbits.DC1B = pwmValue & 0x03;  // Set the low 2 bits (CCP1CON)
}

// Main function
void main(void) {
    // Initialize PWM
    PWM_Init();

    // Run the PWM signal to control the servo motor
    while(1) {
        // Change the PWM duty cycle to rotate the servo
        // Example: Rotate the servo from 0 to 180 degrees

        for (unsigned char i = 10; i <= 20; i++) {
            PWM_SetDutyCycle(i);  // Set duty cycle (1ms to 2ms pulse width)
            __delay_ms(200);      // Wait for 200ms for the servo to move
        }

        for (unsigned char i = 20; i >= 10; i--) {
            PWM_SetDutyCycle(i);  // Set duty cycle (1ms to 2ms pulse width)
            __delay_ms(200);      // Wait for 200ms for the servo to move
        }
    }
}