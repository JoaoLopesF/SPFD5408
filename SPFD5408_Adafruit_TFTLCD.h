// IMPORTANT: SEE COMMENTS @ LINE 15 REGARDING SHIELD VS BREAKOUT BOARD USAGE.

// Graphics library by ladyada/adafruit with init code from Rossum
// MIT license

// Modified for SPFD5408 by Joao Lopes

#ifndef _ADAFRUIT_TFTLCD_H_
#define _ADAFRUIT_TFTLCD_H_

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

// *** SPFD5408 change -- Begin
#include <SPFD5408_Adafruit_GFX.h>

// Color definitions
#define	TFTLCD_BLACK           0x0000
#define TFTLCD_WHITE           0xFFFF
#define	TFTLCD_BLUE            0x001F
#define	TFTLCD_RED             0xF800
#define	TFTLCD_GREEN           0x07E0
#define TFTLCD_CYAN            0x07FF
#define TFTLCD_MAGENTA         0xF81F
#define TFTLCD_YELLOW          0xFFE0
#define TFTLCD_ORANGE          0xFC80
#define TFTLCD_PURPLE          0x781F
#define TFTLCD_SIENNA          0xF811
#define TFTLCD_NEONYELLOW      0x9FE0
#define TFTLCD_EMERALD         0x05E5
#define TFTLCD_BLUE3           0x03FF
#define TFTLCD_ROYALBLUE       0x3333
#define TFTLCD_BROWN2          0x8888
#define TFTLCD_PINK            0xFADF
#define TFTLCD_DKPINK          0xFCDF
#define TFTLCD_BROWN1          0x7083
#define TFTLCD_OLIVE           0x6BC3

// -- End

// **** IF USING THE LCD BREAKOUT BOARD, COMMENT OUT THIS NEXT LINE. ****
// **** IF USING THE LCD SHIELD, LEAVE THE LINE ENABLED:             ****

// *** SPFD5408 change -- Begin
//#define USE_ADAFRUIT_SHIELD_PINOUT 1
// -- End

class Adafruit_TFTLCD : public Adafruit_GFX {

 public:

  Adafruit_TFTLCD(uint8_t cs, uint8_t cd, uint8_t wr, uint8_t rd, uint8_t rst);
  Adafruit_TFTLCD(void);

  void     begin(uint16_t id = 0x9325);
  void     drawPixel(int16_t x, int16_t y, uint16_t color);
  void     drawFastHLine(int16_t x0, int16_t y0, int16_t w, uint16_t color);
  void     drawFastVLine(int16_t x0, int16_t y0, int16_t h, uint16_t color);
  void     fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t c);
  void     fillScreen(uint16_t color);
  void     reset(void);
  void     setRegisters8(uint8_t *ptr, uint8_t n);
  void     setRegisters16(uint16_t *ptr, uint8_t n);
  void     setRotation(uint8_t x);
       // These methods are public in order for BMP examples to work:
  void     setAddrWindow(int x1, int y1, int x2, int y2);
  void     pushColors(uint16_t *data, uint8_t len, boolean first);

  uint16_t color565(uint8_t r, uint8_t g, uint8_t b),
           readPixel(int16_t x, int16_t y),
           readID(void);
  uint32_t readReg(uint8_t r);

 private:

  void     init(),
           // These items may have previously been defined as macros
           // in pin_magic.h.  If not, function versions are declared:
#ifndef write8
           write8(uint8_t value),
#endif
#ifndef setWriteDir
           setWriteDir(void),
#endif
#ifndef setReadDir
           setReadDir(void),
#endif
#ifndef writeRegister8
           writeRegister8(uint8_t a, uint8_t d),
#endif
#ifndef writeRegister16
           writeRegister16(uint16_t a, uint16_t d),
#endif
    writeRegister24(uint8_t a, uint32_t d),
    writeRegister32(uint8_t a, uint32_t d),
#ifndef writeRegisterPair
           writeRegisterPair(uint8_t aH, uint8_t aL, uint16_t d),
#endif
           setLR(void),
           flood(uint16_t color, uint32_t len);
  uint8_t  driver;

#ifndef read8
  uint8_t  read8fn(void);
  #define  read8isFunctionalized
#endif

#ifndef USE_ADAFRUIT_SHIELD_PINOUT

  #ifdef __AVR__
    volatile uint8_t *csPort    , *cdPort    , *wrPort    , *rdPort;
	uint8_t           csPinSet  ,  cdPinSet  ,  wrPinSet  ,  rdPinSet  ,
					  csPinUnset,  cdPinUnset,  wrPinUnset,  rdPinUnset,
					  _reset;
  #endif
  #if defined(__SAM3X8E__)
    Pio *csPort    , *cdPort    , *wrPort    , *rdPort;
	uint32_t          csPinSet  ,  cdPinSet  ,  wrPinSet  ,  rdPinSet  ,
					  csPinUnset,  cdPinUnset,  wrPinUnset,  rdPinUnset,
					  _reset;
  #endif

#endif
};

// For compatibility with sketches written for older versions of library.
// Color function name was changed to 'color565' for parity with 2.2" LCD
// library.
#define Color565 color565

#endif
