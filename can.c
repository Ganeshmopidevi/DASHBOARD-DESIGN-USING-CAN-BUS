//can.c

#include<LPC21XX.h>     // Header file for LPC21xx microcontroller registers
#include"types.h"       // Custom typedefs (u8, u32, etc.)
#include"delay.h"       // Delay functions
#include"can_defines.h" // CAN-related macros and bit definitions
#include"can.h"         // CAN function declarations

// Function to initialize CAN1 module
void can1_init(void)
{
        PINSEL1 |= (RD1_PIN_0_25);   // Configure pins P0.25 and P0.26 for CAN1 RX and TX

        C1MOD |= 1 << RM_BIT;        // Set Reset Mode (enter initialization mode)

        AFMR &= ~(1 << ACCOFF_BIT);  // Enable acceptance filter (clear ACCOFF bit)
        AFMR |= 1 << ACCBP_BIT;      // Bypass acceptance filter (accept all messages)

        C1BTR = BTR_LVAL;            // Set baud rate timing register

        C1MOD &= ~(1 << RM_BIT);     // Exit Reset Mode (enter normal operation mode)
}

// Function to transmit CAN frame
void can1_tx(CANF txF)
{
        u32 timeout = 50000;         // Timeout counter

        // Wait until transmit buffer 1 is free
        while(((C1GSR >> TBS1_BIT) & 1) == 0)
        {
                if(timeout-- == 0)   // Break if timeout occurs
                        break;
        }

        C1TID1 = txF.ID;             // Load identifier into transmit ID register

        // Load Frame Information: RTR bit and DLC (Data Length Code)
        C1TFI1 = ((txF.bfv.RTR << RTR_BIT) | (txF.bfv.DLC << DLC_BIT));

        // If it's not a Remote Frame, load data
        if(txF.bfv.RTR != 1)
        {
                C1TDA1 = txF.DATA1;  // Load first 4 bytes of data
                C1TDB1 = txF.DATA2;  // Load next 4 bytes of data
        }

        // Select transmit buffer and request transmission
        C1CMR |= ((1 << STB1_BIT) | (1 << TR_BIT));

        timeout = 50000;             // Reset timeout counter

        // Wait until transmission is complete
        while(((C1GSR >> TCS1_BIT) & 1) == 0)
        {
                if(timeout-- == 0)   // Break if timeout occurs
                        break;
        }
}

// Function to receive CAN frame
u8 can1_rx(CANF *rxF)
{
        // Check if Receive Buffer has data
        if(((C1GSR >> RBS_BIT) & 1) == 0)
        {
                return 0;            // No data received
        }

        rxF->ID = C1RID;             // Read received ID

        rxF->bfv.RTR = ((C1RFS >> RTR_BIT) & 1);   // Extract RTR bit

        rxF->bfv.DLC = ((C1RFS >> DLC_BIT) & 15);  // Extract Data Length Code

        // If it's a Data Frame, read data
        if(rxF->bfv.RTR == 0)
        {
                rxF->DATA1 = C1RDA;  // Read first 4 bytes
                rxF->DATA2 = C1RDB;  // Read next 4 bytes
        }

        C1CMR |= (1 << RRB_BIT);     // Release Receive Buffer

        return 1;                    // Data received successfully
}