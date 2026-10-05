//delay.c

#include"types.h"   // Includes custom data types like u32

// Function to generate delay in microseconds
void delay_us(u32 tdly)
{
        tdly *= 12;        // Adjust count for 1 µs delay (based on CPU clock ~12 MHz)
        while(tdly--);     // Busy-wait loop until count becomes zero
}

// Function to generate delay in milliseconds
void delay_ms(u32 tdly)
{
        tdly *= 12000;     // Adjust count for 1 ms delay (1000 × 12)
        while(tdly--);     // Busy-wait loop
}

// Function to generate delay in seconds
void delay_s(u32 tdly)
{
         tdly *= 12000000; // Adjust count for 1 second delay (1,000,000 × 12)
         while(tdly--);    // Busy-wait loop
}