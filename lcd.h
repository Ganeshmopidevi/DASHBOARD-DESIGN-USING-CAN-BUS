//lcd.h

#include"types.h"   // Includes custom data types like u8, s8, s32, f32


// -------- LCD FUNCTION DECLARATIONS --------

// Initialize LCD (configure pins and send setup commands)
void lcd_init(void);

// Low-level function to send data/command to LCD
void lcd_disp(u8);

// Send command to LCD (RS = 0)
void lcd_cmd(u8);

// Display a string on LCD
void lcd_str(s8*);

// Display a single character
void lcd_char(s8);

// Display integer value
void lcd_int(s32);

// Display floating point number
// num → value to display
// nDP → number of decimal points
void lcd_f32(f32, u32);

// Write custom characters into CGRAM
void WriteToCGRAM(void);

// Display a byte in hexadecimal format (2 digits)
void lcd_hex(u8 data);

// Display 32-bit value in hexadecimal format
void lcd_hex_data(u32 value);