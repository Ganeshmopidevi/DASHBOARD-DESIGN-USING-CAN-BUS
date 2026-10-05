//lcd.c

#include<LPC21xx.h>        // LPC21xx register definitions
#include"delay.h"          // Delay functions
#include"types.h"          // Custom data types
#include"defines.h"        // General macros
#include"lcd.h"            // LCD function declarations
#include"lcd_defines.h"    // LCD pin definitions


// -------- LCD INITIALIZATION --------
void lcd_init(void)
{
  IODIR0 |= (0xff << LCD_DATA) | (1<<RS) | (1<<RW) | (1<<EN);
  // Configure LCD data pins (8-bit) + control pins as output

  delay_ms(20);            // Wait for LCD power stabilization

  // Initialization sequence (mandatory for 8-bit mode)
  lcd_cmd(0x30);
  delay_ms(8);
  lcd_cmd(0x30);
  delay_ms(1);
  lcd_cmd(0x30);
  delay_ms(1);

  lcd_cmd(0x38);           // Function set: 8-bit, 2 lines, 5x7 font
  lcd_cmd(0x10);           // Cursor move (shift settings)
  lcd_cmd(0x01);           // Clear display
  lcd_cmd(0x06);           // Entry mode: auto increment cursor
  lcd_cmd(0x0C);           // Display ON, cursor OFF
  lcd_cmd(GOTO_LINE_1_POS_0); // Set cursor to line 1, position 0
}


// -------- LOW-LEVEL DISPLAY FUNCTION --------
void lcd_disp(u8 val)
{
  IOCLR0 = 1 << RW;                        // RW = 0 → Write operation

  WRITEBYTE(IOPIN0, LCD_DATA, val);        // Put data/command on data bus

  IOSET0 = 1 << EN;                        // Enable HIGH (latch data)
  delay_us(2);
  IOCLR0 = 1 << EN;                        // Enable LOW

  delay_ms(2);                             // Wait for execution
}


// -------- SEND COMMAND --------
void lcd_cmd(u8 cmd)
{
  IOCLR0 = 1 << RS;    // RS = 0 → Command register
  lcd_disp(cmd);       // Send command
}


// -------- SEND SINGLE CHARACTER --------
void lcd_char(s8 dat)
{
  IOSET0 = 1 << RS;    // RS = 1 → Data register
  lcd_disp(dat);       // Send character
}


// -------- DISPLAY STRING --------
void lcd_str(s8 *ptr)
{
  while(*ptr)          // Loop until NULL character
  {
    lcd_char(*ptr++);  // Print each character
  }
}


// -------- DISPLAY INTEGER --------
void lcd_int(s32 num)
{
  s8 a[10], i = 0;

  if(num == 0)
    lcd_char('0');     // Directly print '0'
  else
  {
    if(num < 0)        // Handle negative numbers
    {
      lcd_char('-');
      num = -num;
    }

    // Convert integer to ASCII digits
    while(num)
    {
      a[i++] = num % 10 + '0';
      num /= 10;
    }

    // Print digits in correct order
    for(i = i-1; i >= 0; i--)
      lcd_char(a[i]);
  }
}


// -------- DISPLAY FLOAT --------
void lcd_f32(f32 num, u32 nDP)
{
  s32 n, i;

  if(num < 0)          // Handle negative float
  {
    lcd_char('-');
    num = -num;
  }

  n = num;
  lcd_int(n);          // Print integer part
  lcd_char('.');       // Print decimal point

  // Print fractional part
  for(i = 0; i <= nDP; i++)
  {
    num = (num - n) * 10;
    n = num;
    lcd_char(n + '0');
  }
}


// -------- CUSTOM CHARACTER CREATION (CGRAM) --------
void WriteToCGRAM(void)
{
  s8 i;

  /* Custom patterns:
     Used for arrows (indicator) and fuel bar graphics
  */
  s8 a[] = {0x10,0x1C,0x1E,0x1F,0x1E,0x1C,0x10,0x00};
  s8 b[] = {0x01,0x07,0x0F,0x1F,0x0F,0x07,0x01,0x00};
  s8 c[] = {0x00,0x04,0x0E,0x1F,0x0E,0x04,0x00,0x00};
  s8 d[] = {0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0x00};
  s8 e[] = {0x00,0x00,0x00,0x00,0x1F,0x1F,0x1F,0x00};
  s8 f[] = {0x00,0x00,0x1F,0x1F,0x1F,0x1F,0x1F,0x00};
  s8 g[] = {0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x00};
  s8 h[] = {0x1F,0x11,0x11,0x11,0x11,0x11,0x1F,0x00};

  lcd_cmd(0x40);       // Set CGRAM address

  // Load patterns into CGRAM
  for(i=0;i<8;i++) lcd_char(a[i]);
  for(i=0;i<8;i++) lcd_char(b[i]);
  for(i=0;i<8;i++) lcd_char(c[i]);
  for(i=0;i<8;i++) lcd_char(d[i]);
  for(i=0;i<8;i++) lcd_char(e[i]);
  for(i=0;i<8;i++) lcd_char(f[i]);
  for(i=0;i<8;i++) lcd_char(g[i]);
  for(i=0;i<8;i++) lcd_char(h[i]);
}


// -------- DISPLAY HEX BYTE --------
void lcd_hex(u8 data)
{
  u8 up, low;

  up  = (data >> 4) & 0x0F;   // Upper nibble
  low = data & 0x0F;          // Lower nibble

  // Display upper nibble
  if(up < 10)
    lcd_disp(up + '0');
  else
    lcd_disp(up - 10 + 'A');

  // Display lower nibble
  if(low < 10)
    lcd_disp(low + '0');
  else
    lcd_disp(low - 10 + 'A');
}


// -------- DISPLAY 32-BIT HEX VALUE --------
void lcd_hex_data(u32 value)
{
  lcd_str("0x");   // Prefix

  lcd_hex((value >> 24) & 0xFF); // MSB
  lcd_hex((value >> 16) & 0xFF);
  lcd_hex((value >> 8) & 0xFF);
  lcd_hex(value & 0xFF);         // LSB
}