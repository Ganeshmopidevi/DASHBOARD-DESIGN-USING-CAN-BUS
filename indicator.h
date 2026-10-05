//indicator.h

#include"types.h"   // Includes custom data types like u32, s32

// -------- External Interrupt Service Routines --------

// ISR for External Interrupt 0 (e.g., left indicator trigger)
void eint0_isr(void) __irq;

// ISR for External Interrupt 2 (e.g., right indicator trigger)
void eint2_isr(void) __irq;


// -------- External Interrupt Initialization --------

// Function to configure and enable external interrupts (EINT0 & EINT2)
void ext_int_init(void);


// -------- LED Indicator Functions --------

// Move LED in left direction (running LED effect)
void led_left_step(void);

// Move LED in right direction (reverse running effect)
void led_right_step(void);

// Turn OFF all LEDs
void led_off(void);