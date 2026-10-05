//MainNode.c

#include<LPC21XX.h>        // LPC21xx register definitions
#include "delay.h"         // Delay functions
#include "can.h"           // CAN communication
#include "can_defines.h"   // CAN macros
#include "types.h"         // Custom data types
#include "lcd.h"           // LCD functions
#include "lcd_defines.h"   // LCD macros
#include "indicator.h"     // Indicator + interrupt functions
#include "ds18b20.h"       // Temperature sensor (1-Wire)

#define TX_LED 0           // Status LED (P0.0)

CANF rxF;                  // CAN receive frame

// External variables updated by interrupt (EXINT.c)
extern volatile u32 blink1 ,blink2,eintflg1,eintflg2;

char fuel, tp, tpd, blocks, i;  // Fuel + display variables
int temp = 0;                   // Temperature value


int main()
{
    IODIR0 |= TX_LED;        // Configure LED pin as output

    can1_init();             // Initialize CAN module
    ext_int_init();          // Initialize external interrupts
    lcd_init();              // Initialize LCD

    WriteToCGRAM();          // Load custom characters (arrows, fuel blocks)

    while(1)
    {
        // -------- DISPLAY HEADER --------
        lcd_cmd(GOTO_LINE_1_POS_0);
        lcd_str(" <<<DASHBOARD>>>");

        // -------- DISPLAY TEMPERATURE --------
        lcd_cmd(GOTO_LINE_2_POS_0);
        lcd_str("TEMP:");
        lcd_int(temp);       // Show temperature value
        lcd_char(0xdf);      // Degree symbol
        lcd_str("C");

        // -------- DISPLAY INDICATOR LABEL --------
        lcd_cmd(0xD4);       // Custom LCD position
        lcd_str("INDICATOR:");

        // -------- DISPLAY FUEL LABEL --------
        lcd_cmd(0x94);       // Line 2 position
        lcd_str("FUEL: ");

        // Read temperature from DS18B20 sensor
        temp = ReadTemp();


        // -------- RECEIVE FUEL DATA FROM CAN --------
        if(can1_rx(&rxF))
        {
            if(rxF.ID == 2)      // Fuel node ID
            {
                fuel = rxF.DATA2;   // Fuel percentage

                if(fuel > 100)      // Limit max value
                {
                    fuel = 100;
                }

                // Calculate number of blocks (each block = 25%)
                blocks = fuel / 25;

                // Display graphical fuel bar
                for(i = 0; i < 4; i++)
                {
                    if(i < blocks)
                    {
                        lcd_char(i + 3);   // Custom block characters
                    }
                    else
                    {
                        lcd_char(' ');     // Empty space
                    }
                }

                // Display numeric fuel percentage
                lcd_int(fuel);
                lcd_char('%');
                lcd_char(' ');
            }
        }

        // -------- LEFT INDICATOR DISPLAY --------
        if(blink1)
        {
            lcd_cmd(0xDE);     // Position for left arrow
            lcd_char(' ');     // Blink OFF

            delay_ms(350);

            lcd_cmd(0xDE);
            lcd_char(1);       // Custom arrow symbol
        }
        else
        {
            lcd_cmd(0xDE);
            lcd_char(1);       // Static arrow
        }

        // Middle symbol (indicator base)
        lcd_cmd(0xE0);
        lcd_char(2);

        // -------- RIGHT INDICATOR DISPLAY --------
        if(blink2)
        {
            lcd_cmd(0xE2);     // Position for right arrow
            lcd_char(' ');     // Blink OFF

            delay_ms(350);

            lcd_cmd(0xE2);
            lcd_char(0);       // Custom arrow symbol
        }
        else
        {
            lcd_cmd(0xE2);
            lcd_char(0);       // Static arrow
        }
    }
}