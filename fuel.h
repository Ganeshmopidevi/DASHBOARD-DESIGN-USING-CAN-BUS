//fuel.h

#include"types.h"   // Includes custom data types like u32 (unsigned 32-bit), f32 (float)

// -------- Function Declarations --------

// Initialize ADC module (configure pins, clock, enable ADC)
void adc_init(void);

// Read ADC value from given channel
// ch_no → ADC channel number (e.g., 0, 1)
// dVal  → pointer to store digital value (0–1023)
// eAr   → pointer to store equivalent analog voltage
void read_adc_value(u32 ch_no, u32 *dVal, f32 *eAr);