// Steps for PWM Generation for Servo Motor
// PWM Signal Basics:
// The frequency of the PWM signal is typically 50 Hz (20ms period).
// The pulse width is controlled by the duty cycle of the PWM signal (1ms = 5%, 2ms = 10%).
// PIC18F458 PWM Setup:
// We'll use CCP1 (Capture/Compare/PWM) module in PWM mode for generating the PWM signal.
// We will set up the appropriate timer (usually Timer2) for the PWM period.

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


// Explanation of the Code
// PWM Initialization:
// PWM_Init(): Configures the CCP1 module in PWM mode, sets the PWM period for 50Hz (20ms), and enables Timer2 for generating the PWM signal.
// PR2 is set to 249 to achieve a 20ms period, as PR2 = (PWM Period - 1).
// T2CKPS is set to 16 (prescaler for Timer2).

// PWM Duty Cycle:
// PWM_SetDutyCycle(): This function sets the duty cycle for the PWM signal. The duty cycle determines the pulse width and thus controls the position of the servo. For example:
// 1ms pulse (5% duty cycle) corresponds to 0 degrees.
// 2ms pulse (10% duty cycle) corresponds to 180 degrees.
// The duty cycle is calculated based on the desired pulse width in the PWM period.

// Main Loop:
// The main loop continuously rotates the servo from 0 to 180 degrees and back. The duty cycle is varied from 10 (1ms) to 20 (2ms) and back.
// This causes the servo motor to move in a full range of motion.
// Delay:
// __delay_ms(200) is used to give the servo time to reach each position.
// Proteus Simulation Setup
// Place PIC18F458 in the Proteus workspace.
// Place a 16x2 LCD and Servo Motor:
// Connect CCP1 (RC2) to the servo motor's PWM input.
// The servo motor is typically powered by 5V, so make sure to connect VDD and VSS accordingly.
// Connect the control wire of the servo to RC2 (or the pin configured for PWM output).
// Connect Power:
// VDD to 5V and VSS to Ground for both PIC and the servo.
// Run the Simulation:
// Start the simulation and observe the servo motor moving from 0 to 180 degrees and back, based on the PWM signal.
// Conclusion
// The provided code generates a PWM signal on RC2 pin of the PIC18F458 to control a servo motor.
// The duty cycle is adjusted to control the servo position, with values from 1ms (0 degrees) to 2ms (180 degrees).
// The Proteus simulation allows you to test the PWM output and the servo motor's movement.