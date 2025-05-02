//RAM -> EEPROM

#include <xc.h>
#include "i2c.h"  // Include I2C library (you must provide it)

#define EEPROM_ADDRESS  0x50  // 7-bit address of the EEPROM device

// Array stored in internal RAM (inside the microcontroller)
unsigned char internal_data[5] = {10, 20, 30, 40, 50};

void main(void) {
    unsigned char i;

    // Step 1: Initialize I2C communication
    I2C_Master_Init(100000);  // Set I2C clock to 100 kHz

    // Step 2: Transfer data from internal array to EEPROM
    for(i = 0; i < 5; i++) {
        I2C_Master_Start();                           // Start communication with EEPROM
        I2C_Master_Write((EEPROM_ADDRESS << 1) | 0);   // Send device address + Write command
        I2C_Master_Write(i);                           // Send memory location address (0,1,2,...)
        I2C_Master_Write(internal_data[i]);            // Send the data byte
        I2C_Master_Stop();                             // Stop communication
        __delay_ms(10);  // Wait for EEPROM to finish writing (important!)
    }
    
    while(1);  // Stay in infinite loop after transfer is done
}