//lcd_defines.h

// -------- LCD PIN CONFIGURATION --------

// Starting bit position of LCD data lines (D0–D7 connected to P0.10–P0.17)
#define LCD_DATA 10   // Data lines mapped from P0.10 onwards (8-bit mode)

//#define LCD_DATA_2 27   // (Optional) For 4-bit mode or alternate mapping (not used)


// -------- LCD CONTROL PINS --------

#define RS 18   // Register Select → P0.18
// RS = 0 → Command register
// RS = 1 → Data register

#define RW 20   // Read/Write → P0.20
// RW = 0 → Write
// RW = 1 → Read

#define EN 19   // Enable → P0.19
// Used to latch data (HIGH → LOW pulse)


// -------- LCD COMMAND MACROS --------

#define GOTO_LINE_1_POS_0 0x80   // Cursor to line 1, position 0
#define GOTO_LINE_2_POS_0 0xC0   // Cursor to line 2, position 0

#define LCD_CLR 0x01             // Clear display command