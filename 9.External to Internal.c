//EEPROM -> RAM

#include <xc.h>
#include "i2c.h"  // Include I2C library (you must provide it)

#define EEPROM_ADDRESS  0x50  // 7-bit address of the EEPROM device

// Empty array to receive data from EEPROM
unsigned char received_data[5];

void main(void) {
    unsigned char i;

    // Step 1: Initialize I2C communication
    I2C_Master_Init(100000);  // Set I2C clock to 100 kHz

    // Step 2: Transfer data from EEPROM back into internal array
    for(i = 0; i < 5; i++) {
        I2C_Master_Start();                           // Start communication
        I2C_Master_Write((EEPROM_ADDRESS << 1) | 0);   // Send device address + Write (to set address)
        I2C_Master_Write(i);                           // Send memory location address to read from
        I2C_Master_RepeatedStart();                   // Repeat start (switch to Read mode)
        I2C_Master_Write((EEPROM_ADDRESS << 1) | 1);   // Send device address + Read command
        received_data[i] = I2C_Master_Read(0);         // Read the data byte (NACK after last byte)
        I2C_Master_Stop();                             // Stop communication
        __delay_ms(5);  // Small delay
    }
    
    while(1);  // Stay in infinite loop after reading is done
}
