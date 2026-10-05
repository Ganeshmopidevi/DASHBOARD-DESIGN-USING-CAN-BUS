//ds18b20.c

#include<LPC21xx.h>   // LPC21xx register definitions
#include "delay.h"    // Delay functions

#define D 1<<22        // 1-Wire data line connected to P0.22
#define R (IOPIN0&(1<<22))   // Read status of data line (P0.22)


/** RESET FUNCTION FOR DS18B20 **/
unsigned char ResetDS18b20(void)
{
        unsigned int presence;   // Variable to store presence pulse

        IODIR0 |= D;             // Configure pin as output
        IOPIN0 |= D;             // Set line HIGH
        delay_us(1);             // Small delay (1 µs)

        IOPIN0 &= ~(D);          // Pull line LOW (reset pulse)
        delay_us(478);           // Keep LOW for ~480 µs

        IOPIN0 |= D;             // Release line (HIGH)
        delay_us(54);            // Wait before reading presence

        presence = IOPIN0;       // Read line status

        delay_us(423);           // Wait for end of timeslot

        // Check if device responded (presence pulse)
        if(presence & R)
                return 1;        // No device detected
        else
                return 0;        // Device present
}


/** READ A SINGLE BIT FROM DS18B20 **/
unsigned char ReadBit(void)
{
        unsigned int B;

        IOPIN0 &= ~(D);          // Pull line LOW (start read slot)
        delay_us(1);             // Short delay

        IOPIN0 |= D;             // Release line
        IODIR0 &= ~(D);          // Configure as input

        delay_us(10);            // Wait before sampling

        B = IOPIN0;              // Read data line

        IODIR0 |= D;             // Set back to output

        if(B & R)
                return 1;        // Bit = 1
        else
                return 0;        // Bit = 0
}


/** WRITE A SINGLE BIT TO DS18B20 **/
void WriteBit(unsigned char Dbit)
{
        IOPIN0 &= ~(D);          // Pull line LOW (start write slot)
        delay_us(1);             // Short delay

        if(Dbit)
                IOPIN0 |= D;     // Write '1' by releasing line early

        delay_us(58);            // Complete timeslot (~60 µs)

        IOPIN0 |= D;             // Ensure line HIGH
        delay_us(1);
}


/** READ A BYTE (8 bits) FROM DS18B20 **/
unsigned char ReadByte(void)
{
        unsigned char i;
        unsigned char Din = 0;   // Variable to store received byte

        for (i = 0; i < 8; i++)
        {
                // Read each bit and place at correct position
                Din |= ReadBit() ? (0x01 << i) : Din;

                delay_us(45);    // Delay between bit reads
        }

        return Din;              // Return received byte
}


/** WRITE A BYTE (8 bits) TO DS18B20 **/
void WriteByte(unsigned char Dout)
{
        unsigned char i;

        for (i = 0; i < 8; i++)
        {
                WriteBit((Dout & 0x1));  // Write LSB first
                Dout = Dout >> 1;        // Shift next bit
                delay_us(1);
        }

        delay_us(98);            // Delay after byte transmission
}


/** READ TEMPERATURE FROM DS18B20 **/
int ReadTemp(void)
{
        unsigned char n, buff[2];
        int temp;

        ResetDS18b20();   // Send reset pulse
        WriteByte(0xcc);  // Skip ROM (single device)
        WriteByte(0x44);  // Start temperature conversion

        while (ReadByte() == 0); // Wait until conversion complete

        ResetDS18b20();   // Reset again
        WriteByte(0xcc);  // Skip ROM
        WriteByte(0xbe);  // Read scratchpad command

        // Read 2 bytes (LSB + MSB of temperature)
        for (n = 0; n < 2; n++)
        {
            buff[n] = ReadByte();
        }

        // Combine MSB and LSB
        temp = buff[1];   // MSB
        temp = temp << 8;
        temp |= buff[0];  // LSB

        temp = temp / 16; // Convert to Celsius (DS18B20 resolution)

        return temp;      // Return temperature value
}