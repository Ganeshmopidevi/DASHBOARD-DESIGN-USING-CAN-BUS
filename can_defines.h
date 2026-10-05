//can_defines.h

#include"types.h"   // Includes custom data types like u32, u8

//#define TD1_PIN           // (Commented) Transmit pin definition (not used)
//#define PIN_FUN2 1        // (Commented) Alternate function select

#define RD1_PIN_0_25 0x15440000   // Configure P0.25 (RD1) and P0.26 (TD1) pins for CAN1

#define PCLK 15000000             // Peripheral clock frequency (15 MHz)

#define BIT_RATE 125000           // Desired CAN baud rate (125 kbps)

#define QUANTA 15                 // Number of time quanta per bit

// Baud Rate Prescaler calculation
#define BRP (PCLK/(BIT_RATE * QUANTA))

#define SAMPLE_POINT (0.7 * QUANTA)   // Sample point at 70% of bit time

#define TSEG1 ((u32)SAMPLE_POINT -1)  // Time Segment 1

#define TSEG2 (QUANTA - (1 + TSEG1))  // Time Segment 2

// Synchronization Jump Width (SJW)
#define SJW ((TSEG2 >= 5)?4:(TSEG2-1))

#define SAM_BIT 0                     // Sampling mode (0 = single sample)

// CAN Bit Timing Register value
#define BTR_LVAL ((SAM_BIT << 23)|((TSEG2 - 1) << 20)|((TSEG1 - 1)<< 16)|((SJW-1) << 14)|(BRP-1))

// ---------------- C1MOD REGISTER ----------------
#define RM_BIT 0       // Reset Mode bit (1 = reset mode, 0 = normal mode)

// ---------------- C1CMR REGISTER ----------------
#define TR_BIT   0     // Transmission Request bit
#define RRB_BIT  2     // Release Receive Buffer bit
#define STB1_BIT 5     // Select Transmit Buffer 1

// ---------------- C1GSR REGISTER ----------------
#define RBS_BIT   0    // Receive Buffer Status (1 = data available)
#define TBS1_BIT  2    // Transmit Buffer 1 Status (1 = free)
#define TCS1_BIT  3    // Transmit Complete Status for buffer 1

// ---------------- C1RFS REGISTER ----------------
#define FF_BIT  31     // Frame Format bit (0 = standard, 1 = extended)
#define RTR_BIT 30     // Remote Transmission Request bit
#define DLC_BIT 16     // Data Length Code position

// ---------------- AFMR REGISTER ----------------
#define ACCOFF_BIT 0   // Acceptance Filter OFF bit
#define ACCBP_BIT  1   // Acceptance Filter Bypass bit (accept all messages)

// ---------------- External Interrupt (EINT) ----------------
#define EINT0_0_1 0x0000000c   // Configure P0.1 as EINT0
#define EINT0_VIC_CHNO 14      // VIC channel number for EINT0
//#define EINT0_STATUS_LED 16   // (Commented) LED pin for status

#define EINT2_0_7 0x0000c000   // Configure P0.7 as EINT2
#define EINT2_VIC_CHNO 16      // VIC channel number for EINT2
///#define EINT1_STATUS_LED 17 // (Commented) Another status LED

// ---------------- LED Definitions ----------------
#define L_LED 0   // Left indicator LED pin (e.g., P0.0)
#define R_LED 2   // Right indicator LED pin (e.g., P0.2)