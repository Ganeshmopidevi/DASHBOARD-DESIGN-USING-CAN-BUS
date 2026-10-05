///FUEL.c

#include<LPC21xx.h>       // LPC21xx register definitions
#include"typeS.h"         // Custom data types (u32, f32, etc.)
#include"delay.h"         // Delay functions
#include"fuel_defnes.h"   // ADC-related macros and definitions


// -------- ADC Initialization --------
void adc_init(void)
{
        PINSEL1 &= ~(0xff << 22);   // Clear bits for P0.27 & P0.28 (ADC pins)

        // Configure P0.27 → AIN0, P0.28 → AIN1 (ADC inputs)
        PINSEL1 |= (AIN0_0_27) |
                   (AIN1_0_28);

        // Configure ADC:
        // - Set clock divider
        // - Enable ADC (PDN = Power Down bit = 1 → active)
        ADCR |= (CLK_DIV << CLK_DIV_BITS) |
                (1 << PDN_BIT);
}


// -------- Read ADC Value --------
void read_adc_value(u32 ch_no ,u32 *dVal ,f32 *eAr)
{
        ADCR &= 0xffffff00;   // Clear channel selection bits

        // Select ADC channel and start conversion
        ADCR |= (1 << ch_no) |
                (1 << CONV_START_BITS);

        delay_us(3);          // Small delay for conversion start

        // Wait until conversion is complete (DONE bit becomes 1)
        while(((ADDR >> DONE_BIT) & 1) == 0);

        ADCR &= ~(1 << CONV_START_BITS);   // Stop conversion

        // Extract 10-bit ADC result (0–1023)
        *dVal = ((ADDR >> RESULT_BITS) & 1023);

        // Convert digital value to analog voltage
        *eAr = (*dVal * (3.3 / 1023));   // Assuming reference voltage = 3.3V
}