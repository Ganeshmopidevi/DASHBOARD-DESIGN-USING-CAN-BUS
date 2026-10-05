//INDICATOR.c

#include<LPC21XX.h>   // LPC21xx register definitions
#include"delay.h"     // Delay functions
#include"types.h"     // Custom data types

#define LED_START 0                 // Starting pin position (P0.0)
#define INDICATOR 0xFF << LED_START // Mask for 8 LEDs (P0.0 to P0.7)

static s32 position = 0;  // Tracks current LED position (0–7)

s32 i;  // (Unused variable - can be removed)


// -------- LEFT INDICATOR (Running LED Left Direction) --------
void led_left_step(void)
{
        IODIR0 |= 0xFF << LED_START;   // Configure P0.0–P0.7 as output

        IOSET0 = INDICATOR;            // Turn OFF all LEDs (assuming active LOW)

        // Turn ON current LED (active LOW → clear bit)
        IOCLR0 = 1 << (LED_START + position);

        position++;                   // Move to next LED (left direction)

        if(position >= 8)             // Wrap around after last LED
            position = 0;

        delay_ms(100);                // Delay for visible movement
}


// -------- RIGHT INDICATOR (Running LED Right Direction) --------
void led_right_step(void)
{
        IODIR0 |= 0xFF << LED_START;   // Configure P0.0–P0.7 as output

        IOSET0 = INDICATOR;            // Turn OFF all LEDs

        // Turn ON current LED
        IOCLR0 = 1 << (LED_START + position);

        position--;                   // Move in reverse direction

        if(position < 0)              // Wrap around to last LED
            position = 7;

        delay_ms(100);                // Delay for animation
}


// -------- TURN OFF ALL INDICATORS --------
void led_off(void)
{
    IOSET0 = INDICATOR;   // Set all bits → turn OFF all LEDs
}