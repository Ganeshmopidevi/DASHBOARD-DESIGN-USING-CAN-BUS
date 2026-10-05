//INDICATOR_NODE.c

#include<LPC21XX.h>        // LPC21xx register definitions
#include"delay.h"          // Delay functions
#include"can.h"            // CAN communication functions
#include"can_defines.h"    // CAN macros
#include"types.h"          // Custom data types
#include"indicator.h"      // LED indicator functions


// -------- LED Mode Definition --------
typedef enum
{
    MODE_OFF = 0,   // All LEDs OFF
    MODE_LEFT,      // Left indicator active
    MODE_RIGHT      // Right indicator active
} LED_MODE;

LED_MODE current_mode = MODE_OFF;   // Current state of indicator


#define LED 10   // Status LED connected to P0.10 (for CAN activity indication)

CANF rxF;        // CAN frame structure for receiving data


int main()
{
    IODIR0 |= 1 << LED;   // Configure status LED pin as output

    can1_init();          // Initialize CAN module

    while(1)
    {
        // Check if any CAN message is received
        if(can1_rx(&rxF))
        {
            IOPIN0 ^= 1 << LED;   // Toggle LED to indicate reception

            // Process message only if ID matches
            if(rxF.ID == 1)
            {
                // DATA1 = 1 → Left indicator command
                if(rxF.DATA1 == 1)
                {
                    // Toggle LEFT mode
                    if(current_mode == MODE_LEFT)
                        current_mode = MODE_OFF;
                    else
                        current_mode = MODE_LEFT;
                }

                // DATA1 = 2 → Right indicator command
                else if(rxF.DATA1 == 2)
                {
                    // Toggle RIGHT mode
                    if(current_mode == MODE_RIGHT)
                        current_mode = MODE_OFF;
                    else
                        current_mode = MODE_RIGHT;
                }
            }
        }

        // Execute LED behavior based on current mode
        switch(current_mode)
        {
            case MODE_LEFT:
                led_left_step();   // Run LEDs in left direction
                break;

            case MODE_RIGHT:
                led_right_step();  // Run LEDs in right direction
                break;

            case MODE_OFF:
                led_off();         // Turn OFF all LEDs
                break;
        }
    }
}