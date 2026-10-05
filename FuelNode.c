//FuelNode.c

#include<LPC21XX.h>        // LPC21xx register definitions
#include"delay.h"          // Delay functions
#include"can.h"            // CAN communication functions
#include"can_defines.h"    // CAN-related macros
#include"types.h"          // Custom data types
#include"fuel.h"           // ADC (fuel sensing) functions

#define TX_LED 0           // LED connected to P0.0 for transmission indication

u32  dVal;                 // Stores raw ADC digital value (0–1023)
f32  eAr;                  // Stores equivalent analog voltage
int percentage;            // Stores fuel level in percentage


int main()
{
        CANF txF;          // CAN frame structure

        IODIR0 |= 1 << TX_LED;   // Configure LED pin as output

        can1_init();       // Initialize CAN module
        adc_init();        // Initialize ADC

        // Configure CAN frame
        txF.ID = 2;        // CAN message ID (Fuel node ID)
        txF.bfv.RTR = 0;   // Data frame (not remote)
        // txF.DATA1 = 0;  // (Optional) Not used here
        // txF.DATA2 = 0;  // (Optional) Initial value
        txF.bfv.DLC = 8;   // Data Length Code (max 8 bytes)

        while(1)
        {
                // Read ADC value from channel 1 (fuel sensor)
                read_adc_value(1, &dVal, &eAr);

                // Convert ADC value to percentage (0–100%)
                percentage = (dVal * 100) / 1023;

                // Store percentage in CAN data field
                txF.DATA2 = percentage;

                // Transmit fuel data over CAN bus
                can1_tx(txF);

                // Toggle LED to indicate transmission
                IOPIN0 ^= 1 << TX_LED;

                delay_ms(100);   // Delay between transmissions
        }
}