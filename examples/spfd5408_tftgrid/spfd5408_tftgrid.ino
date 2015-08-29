///////////////
// Sketch: Grid TFT
// Author: Joao Lopes F. - joaolopesf@gmail.com
// library SPFD5408

/// Grid for help in design of screens 

#include <SPFD5408_Adafruit_GFX.h>    // Core graphics library
#include <SPFD5408_Adafruit_TFTLCD.h> // Hardware-specific library

// LCD Pin

#define LCD_CS A3 // CS
#define LCD_CD A2 // RS
#define LCD_WR A1 // WR
#define LCD_RD A0 // RD
#define LCD_RESET A4 // Optional : otherwise connect to Arduino's reset pin

// Assign human-readable names to some common 16-bit color values:
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

// Init LCD

Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

//-- Setup

void setup(void) {

  // Inicialize the controller

  tft.reset();

  tft.begin(0x9341);

  tft.setRotation(0); // Need for the Mega, please changed for your choice or rotation initial

  // Screen white

  tft.fillScreen(WHITE);
  
 // Grid

  drawGrid();

  // Texts

  tft.setCursor (0, 20);

  tft.setTextColor(RED);
  for (uint8_t size = 1; size <= 5; size++) {
    tft.setTextSize (size);
    tft.setCursor (0, 20 * size * 2);
    tft.print(size);
    tft.print("-");
    tft.println("ABC123");
  }

 }

// -- Loop

void loop()
{
}

// Draw a grid

void drawGrid () {

  for(uint16_t y = 0; y <= 340; y+=5) 
    tft.drawFastHLine(0, y, 240, BLACK);
  for(uint16_t x = 0; x <= 240; x+=5) 
    tft.drawFastVLine(x, 0, 340, BLACK);

  tft.setTextColor(BLACK);
  tft.setTextSize (1);
  
  for(uint16_t y = 0; y <= 340; y+=25) { 
    tft.setCursor (200, y);
    tft.print(y);
  }
}

