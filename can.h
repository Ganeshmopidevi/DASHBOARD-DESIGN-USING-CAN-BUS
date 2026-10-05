//can.h

#include"types.h"   // Includes custom data types like u8, u32

// Structure representing a CAN frame
typedef struct can_frame
{
        u32 ID;     // CAN Identifier (Standard or Extended ID)

        // Bitfield structure for control bits
        struct bitfield
        {
                u32 RTR : 1;  // Remote Transmission Request bit (1 = remote frame, 0 = data frame)
                u32 DLC : 4;  // Data Length Code (number of bytes: 0–8)
                u32 FF  : 1;  // Frame Format (0 = standard frame, 1 = extended frame)
        }bfv;  // Instance name for bitfield values

        u32 DATA1,DATA2;  // Data bytes (total 8 bytes split into two 32-bit registers)

}CANF;  // Typedef name for CAN frame structure

// Function declarations

void can1_init(void);          // Initialize CAN1 module
void can1_tx(CANF txF);        // Transmit a CAN frame
u8 can1_rx(CANF *rxF);         // Receive a CAN frame (returns 1 if data received, else 0)
void left(void);               // Function for left indicator (user-defined)
void right(void);              // Function for right indicator (user-defined)