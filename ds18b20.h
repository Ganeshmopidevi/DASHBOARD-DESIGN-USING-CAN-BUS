///ds18b20.h

#ifndef _DS18B20_H_   // Check if header is already included
#define _DS18B20_H_   // Define macro to prevent multiple inclusion

// -------- DS18B20 FUNCTION DECLARATIONS --------

// Reset the DS18B20 sensor and check presence
unsigned char ResetDS1820(void);  
// Returns 0 → device present, 1 → no device

// Read a single bit from DS18B20 (1-Wire protocol)
unsigned char ReadBit(void);

// Write a single bit to DS18B20
void WriteBit(unsigned char);

// Read a full byte (8 bits) from DS18B20
unsigned char ReadByte(void);

// Write a full byte (8 bits) to DS18B20
void WriteByte(unsigned char);

// Read temperature value from DS18B20
int ReadTemp(void);   // Returns temperature in °C (after conversion)

#endif   // End of header guard