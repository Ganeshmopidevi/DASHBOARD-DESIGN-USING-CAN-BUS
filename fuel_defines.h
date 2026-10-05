//fuel_defines.h

// -------- CLOCK CONFIGURATION --------

#define FOSC 12000000        // Crystal oscillator frequency = 12 MHz

#define CCLK (FOSC*5)        // CPU clock = 60 MHz (PLL used: 12 × 5)

#define PCLK (CCLK/4)        // Peripheral clock = 15 MHz


// -------- ADC CLOCK CONFIGURATION --------

#define ADC_CLK 3000000      // ADC clock should be ≤ 4.5 MHz (safe value: 3 MHz)

#define CLK_DIV ((PCLK/ADC_CLK) - 1)
// Clock divider value for ADC
// Formula: ADC_CLK = PCLK / (CLK_DIV + 1)


// -------- ADCR REGISTER CONFIGURATION --------

#define CLK_DIV_BITS 8       // Bits 8–15 → Clock divider field

#define PDN_BIT      21      // Power Down bit (1 = ADC ON, 0 = ADC OFF)

#define CONV_START_BITS 24   // Bits 24–26 → Start conversion control


// -------- ADDR REGISTER CONFIGURATION --------

#define RESULT_BITS 6        // Bits 6–15 → ADC result (10-bit value)

#define DONE_BIT    31       // Bit 31 → Conversion complete flag


// -------- PIN CONFIGURATION (PINSEL1) --------

#define AIN0_0_27 0x00400000   // Configure P0.27 as ADC channel 0 (AIN0)

#define AIN1_0_28 0x01000000   // Configure P0.28 as ADC channel 1 (AIN1)

//#define AIN2_0_29 0x04000000 // (Optional) P0.29 as AIN2
//#define AIN3_0_30 0x10000000 // (Optional) P0.30 as AIN3