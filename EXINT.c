///EXINT.c

#include<LPC21XX.h>        // LPC21xx register definitions
#include"delay.h"          // Delay functions
#include"can.h"            // CAN functions
#include"can_defines.h"    // CAN-related macros
#include"types.h"          // Custom data types
#include"lcd.h"            // LCD functions
#include"lcd_defines.h"    // LCD macros
#include"indicator.h"      // Indicator control functions

#define TX_LED 0           // LED connected to P0.0 (used as transmit indication)

CANF txF;                  // CAN frame structure for transmission

// Global variables (volatile because used in ISR)
volatile u32 blink1 = 0, blink2 = 0;   // Blink status flags
volatile u32 eintflg1 = 0 , eintflg2 = 0; // Interrupt flags (currently unused)


// -------- External Interrupt 0 ISR --------
void eint0_isr(void) __irq
{
        //eintflg1 = 1;   // (Optional) Set interrupt flag

        //ind_stat=2;     // (Optional) indicator status

        IODIR0 |= 1 << TX_LED;   // Configure LED pin as output

        // Prepare CAN frame (for left indicator or event 1)
        txF.ID = 1;              // CAN ID
        txF.bfv.RTR = 0;         // Data frame (not remote)
        txF.DATA1 = 1;           // Data value = 1
        txF.bfv.DLC = 1;         // Data length = 1 byte

        can1_tx(txF);            // Transmit CAN message

        IOPIN0 ^= 1 << TX_LED;   // Toggle LED (indicates transmission)

        blink1 = !blink1;        // Toggle blink1 flag
        blink2 = 0;              // Reset blink2

        EXTINT = 1 << 0;         // Clear EINT0 interrupt flag

        VICVectAddr = 0;         // Acknowledge interrupt to VIC
}


// -------- External Interrupt 2 ISR --------
void eint2_isr(void) __irq
{
        //eintflg2 = 1;   // (Optional) Set interrupt flag

        //ind_stat=2;     // (Optional) indicator status

        IODIR0 |= 1 << TX_LED;   // Configure LED pin as output

        // Prepare CAN frame (for right indicator or event 2)
        txF.ID = 1;              // CAN ID
        txF.bfv.RTR = 0;         // Data frame
        txF.DATA1 = 2;           // Data value = 2
        txF.bfv.DLC = 1;         // Data length = 1 byte

        can1_tx(txF);            // Transmit CAN message

        IOPIN0 ^= 1 << TX_LED;   // Toggle LED

        blink2 = !blink2;        // Toggle blink2 flag
        blink1 = 0;              // Reset blink1

        EXTINT = 1 << 2;         // Clear EINT2 interrupt flag

        VICVectAddr = 0;         // Acknowledge interrupt
}


// -------- External Interrupt Initialization --------
void ext_int_init(void)
{
        // Configure pins as external interrupt pins
        PINSEL0 |= EINT0_0_1 |    // P0.1 → EINT0
                   EINT2_0_7;     // P0.7 → EINT2

        // Enable interrupts in VIC
        VICIntEnable = (1 << EINT0_VIC_CHNO) |
                       (1 << EINT2_VIC_CHNO);

        // Configure ISR for EINT0
        VICVectCntl0 = (1 << 5) | EINT0_VIC_CHNO; // Enable slot + channel number
        VICVectAddr0 = (s32)eint0_isr;            // Assign ISR address

        // Configure ISR for EINT2
        VICVectCntl1 = (1 << 5) | EINT2_VIC_CHNO;
        VICVectAddr1 = (s32)eint2_isr;

        // Configure interrupt mode (edge-triggered)
        EXTMODE = (1 << 0) |   // EINT0 edge sensitive
                  (1 << 2);    // EINT2 edge sensitive
}