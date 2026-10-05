// Macro to READ a single bit at bit position (BP)
#define READBIT(WORD,BP) ((WORD>>(BP))&1)
// Shifts WORD right by BP positions and masks LSB → returns 0 or 1


// Macro to SET a bit (make it 1) at position BP
#define SETBIT(WORD,BP) WORD|=1<<BP
// OR operation sets only that bit, others remain unchanged


// Macro to SET ONLY one bit (all others become 0)
#define SSETBIT(WORD,BP) WORD=1<<BP
// Clears entire WORD and sets only bit BP


// Alias for SSETBIT (same functionality)
#define SCLRBIT SSETBIT
// (Note: Name is misleading — it doesn't clear, it sets only one bit)


// Macro to CLEAR a bit (make it 0) at position BP
#define CLRBIT(WORD,BP) WORD&=~(1<<BP)
// AND with inverted mask clears that specific bit


// Macro to TOGGLE (complement) a bit
#define CPLBIT(WORD,BP) WORD^=(1<<BP)
// XOR flips the bit (0→1, 1→0)


// Macro to WRITE a specific bit value (0 or 1)
#define WRITEBIT(WORD,BP,BIT) WORD=((WORD&~(1<<BP))|(BIT<<BP))
// Clears target bit first, then writes new BIT value


// Macro to WRITE a 4-bit nibble
#define WRITENIBBLE(WORD,SBP,NIBBLE) WORD=((WORD&~(0xf<<SBP))|(NIBBLE<<SBP))
// Clears 4 bits starting from SBP and writes NIBBLE


// Macro to WRITE a byte (8 bits)
#define WRITEBYTE(WORD,SBP,BYTE) WORD=((WORD&~(0xff<<SBP))|(BYTE<<SBP))
// Clears 8 bits and writes BYTE value


// Macro to WRITE a half-word (16 bits)
#define WRITEHWORD(WORD,SBP,HWORD) WORD=((WORD&~(0xffff<<SBP))|(HWORD<<SBP))
// Clears 16 bits and writes HWORD value