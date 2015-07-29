///////////////
// Sketch: Calibrate - Calibrate TFT SPFD5408 Touch
// Author: Joao Lopes F. - joaolopesf@gmail.com
//
// Versions:
//    - 0.9.0  First beta - July 2015
//    - 0.9.1  Rotation for Mega 
// Comments: 
//    Show the calibration parameters to put in your code
//    Please use a small like the eraser on a pencil for best results
//
//    Code for buttons, based on Adafruit arduin_o_phone example
///////////////

// library SPFD5408 

#include <SPFD5408_Adafruit_GFX.h>    // Core graphics library
#include <SPFD5408_Adafruit_TFTLCD.h> // Hardware-specific library
#include <SPFD5408_TouchScreen.h>     // Touch library

// Calibrates value
#define SENSIBILITY 300
#define MINPRESSURE 10
#define MAXPRESSURE 1000

//These are the pins for the shield!
#define YP A1 
#define XM A2 
#define YM 7  
#define XP 6 

/*
//Macros replaced by variables
#define TS_MINX 150
#define TS_MINY 120
#define TS_MAXX 920
#define TS_MAXY 940
*/
short TS_MINX=150;
short TS_MINY=120;
short TS_MAXX=920;
short TS_MAXY=940;

// Init TouchScreen:

TouchScreen ts = TouchScreen(XP, YP, XM, YM, SENSIBILITY);

// LCD Pin

#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
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

// Dimensions

uint16_t width = 0;
uint16_t height = 0;

// Buttons

#define BUTTONS 3
#define BUTTON_CLEAR 0
#define BUTTON_SHOW 1
#define BUTTON_RESET 2

Adafruit_GFX_Button buttons[BUTTONS];

uint16_t buttons_y = 0;

//-- Setup

void setup(void) {

  // Serial por for debug, not works if shield is plugged in arduino
  
//  Serial.begin(9600);

  // Inicialize the controller
  
  tft.reset();
  
  tft.begin(0x9341);

  tft.setRotation(0); // Need for the Mega, please changed for your choice or rotation initial

  width = tft.width() - 1;
  height = tft.height() - 1;

  // Debug
  
//  Serial.println(F("TFT LCD test"));
//  Serial.print("TFT size is "); 
//  Serial.print(tft.width()); 
//  Serial.print("x"); 
//  Serial.println(tft.height());

  // UI

  initializeButtons();
  
  // Border

  drawBorder();
  
  // Initial screen
  
  tft.setCursor (55, 50);
  tft.setTextSize (3);
  tft.setTextColor(RED);
  tft.println("SPFD5408");
  tft.setCursor (65, 85);
  tft.println("Library");
  tft.setCursor (55, 150);
  tft.setTextSize (2);
  tft.setTextColor(BLACK);
  tft.println("Calibration");

  tft.setCursor (80, 250);
  tft.setTextSize (1);
  tft.setTextColor(BLACK);
  tft.println("Touch to proceed");

  // Wait touch

  waitOneTouch();

  // Calibrate it
  
  calibrate_TS();

  // Wait touch

  waitOneTouch();

  // Calibration

  showCalibration();

}

// -- Loop

void loop()
{
  // Test of calibration
  
  TSPoint p;

  // Wait a touch
  
  digitalWrite(13, HIGH);
  
  p = waitOneTouch();
  
  digitalWrite(13, LOW);

  // Map of values
  
//  p.x = map(p.x, TS_MINX, TS_MAXX, 0, tft.width());
//  p.y = map(p.y, TS_MINY, TS_MAXY, 0, tft.height());

  p.x = mapXValue(p);
  p.y = mapYValue(p);
  
  // Draw a point
  
  tft.fillCircle(p.x, p.y, 3, BLUE);
  
  // Show touch screen point (TSPOINT)
  
  showTouched(p);
  
  // Buttons

  // Go thru all the buttons, checking if they were pressed
  
  for (uint8_t b=0; b<BUTTONS; b++) {
    
    if (buttons[b].contains(p.x, p.y)) {

        // Action

        switch  (b) {

          case BUTTON_CLEAR:

              // Clear

              showCalibration();

              break;
              
          case BUTTON_SHOW:

              // Clear

              showResults();

              tft.println();
              tft.println("Touch to proceed");

              waitOneTouch();

              showCalibration();
              
              break;
              
          case BUTTON_RESET:

              // New calibration

              calibrate_TS();

              waitOneTouch();

              showCalibration();

              break;
        }
    }
  }

}

// Calibration of Touch Screen (resistive)

void calibrate_TS(void) {

  // Based in code posted in https://forum.arduino.cc/index.php?topic=223769.15
  
  TSPoint p1, p2;
  int16_t temp;
  int32_t tempL;
  
  tft.fillScreen(BLACK);
  
  tft.fillCircle(4,4,4,WHITE); //show the first point
  tft.setCursor(5, 30); 
  tft.setTextColor(WHITE); 
  tft.setTextSize(1);
  tft.println("Please touch the dot");

  uint16_t limit = 40;
  
  do {
  
    p1 = waitOneTouch();

  } while (!(mapXValue(p1) < limit && mapYValue(p1) < limit));
  
  tft.fillScreen(BLACK);

  tft.fillCircle(234,314,4,WHITE); //show the 2nd point
  tft.setCursor(50, 280);
  tft.println("Please touch the other dot");
  delay (500); // debunce

  do {
  
    p2 = waitOneTouch();
  
  } while (!(mapXValue(p2) > (width - limit) && mapYValue(p2) > (height - limit)));
  
  tft.fillScreen(BLACK);
  
  delay (300); 
  
  temp=p2.x-p1.x; // Calculate the new coefficients, get X difference
  tempL=((long)temp*1024)/(tft.width()-20);
  TS_MINX=p1.x-( (tempL*10)>>10);// 10 pixels du bord
  TS_MAXX=p1.x+( (tempL*tft.width())>>10);// 220 pixels entre points
  temp=p2.y-p1.y; // ¨get Y difference
  tempL=((long)temp*1024)/(tft.height()-20);
  TS_MINY=p1.y-( (tempL*10)>>10);// 10 pixels du bord
  TS_MAXY=TS_MINY+( (tempL*tft.height())>>10);
  
  // Show results

  showResults();
  
//  p1.x = map(p1.x, TS_MAXX,TS_MINX, tft.width(), 0);
//  p1.y = map(p1.y, TS_MAXY,TS_MINY, tft.height(), 0);
//  p2.x = map(p2.x, TS_MAXX,TS_MINX, tft.width(), 0);
//  p2.y = map(p2.y, TS_MAXY,TS_MINY, tft.height(), 0);

    p1.x = mapXValue(p1);
    p1.y = mapYValue(p1);
    p2.x = mapXValue(p2);
    p2.y = mapYValue(p2);

  tft.println();
  tft.println("Last touched points: ");
  tft.print("Pt 1: ");tft.print(p1.x);tft.print(" : ");tft.println(p1.y);
  tft.print("Pt 2: ");tft.print(p2.x);tft.print(" : ");tft.println(p2.y);

  tft.println();

  // Wait a touch
  
  tft.println("Touch to proceed");

  waitOneTouch();
}
// wait 1 touch to return the point 

TSPoint waitOneTouch() {
  
  TSPoint p;
  
  do {
    p= ts.getPoint(); 
  
    pinMode(XM, OUTPUT); //Pins configures again for TFT control
    pinMode(YP, OUTPUT);
  
  } while((p.z < MINPRESSURE )|| (p.z > MAXPRESSURE));
  
  return p;
}

// Draw a border

void drawBorder () {

  uint16_t width = tft.width() - 1;
  uint16_t height = tft.height() - 1;
  uint8_t border = 10;

  tft.fillScreen(RED);
  tft.fillRect(border, border, (width - border * 2), (height - border * 2), WHITE);
  
}

// Show a screen of calibration

void showCalibration() {
  
  // Clear
  
  tft.fillScreen(BLACK);
  tft.setTextSize (1);

  // Header
  
  tft.fillRect(0, 0, width, 10, RED);

  tft.setCursor (40, 0);
  tft.setTextColor(WHITE);
  tft.println("*** Test of calibration ***");

  // Footer

  TSPoint p; // Only for show initial values
  p.x=0;
  p.y=0;
  p.z=0;
  
  showTouched(p);

  // Buttons

  for (uint8_t i=0; i<3; i++) {
      buttons[i].drawButton();
  }
  
}

// Show the coordinates     

void showTouched(TSPoint p) {

  uint8_t w = 40; // Width
  uint8_t h = 10; // Heigth
  uint8_t x = (width - (w*2)); // X
  uint8_t y = 11; // Y
  
  tft.fillRect(x, y, w*2, h, WHITE); // For cleanup

  tft.drawRect(x, y, w, h, RED); // For X
  tft.drawRect(x+w+2, y, w*2, h, RED); // For Y

  tft.setTextColor(BLACK);
  tft.setCursor(x+2, y + 1);
  tft.print("X: ");
  showValue(p.x);
  
  tft.setCursor(x+2+w+2, y + 1);
  tft.print("Y: ");
  showValue(p.y);

}

// Show a value of TSPoint

void showValue (uint16_t value) {

  if (value < 10)
    tft.print("00");
  if (value < 100)
    tft.print("0");
    
  tft.print(value);
  
}

// Show results of calibration

void showResults() {

  tft.fillScreen(BLACK);
  
  // Header
  
  tft.fillRect(0, 0, width, 10, RED);

  tft.setCursor (40, 0);
  tft.setTextColor(WHITE);
  tft.println("*** Results of calibration ***");

  // Results
  
  tft.setCursor(5, 30);
  tft.setTextSize(2);
  tft.println("After calibration: ");
  tft.print("TS_MINX= ");tft.println(TS_MINX);
  tft.print("TS_MINY= ");tft.println(TS_MINY);
  tft.println();
  tft.print("TS_MAXX= ");tft.println(TS_MAXX);
  tft.print("TS_MAXY= ");tft.println(TS_MAXY);

}

// Initialize buttons

void initializeButtons() {

  uint16_t x = 40;
  uint16_t y = height - 20;
  uint16_t w = 75;
  uint16_t h = 20;
  
  uint8_t spacing_x = 5;
  
  uint8_t textSize = 1;

  char buttonlabels[3][20] = {"Clear", "Show", "Recalib."};
  uint16_t buttoncolors[15] = {RED, BLUE, RED};

  for (uint8_t b=0; b<3; b++) {
    buttons[b].initButton(&tft,                           // TFT object
                  x+b*(w+spacing_x),  y,                  // x, y,
                  w, h, WHITE, buttoncolors[b], WHITE,    // w, h, outline, fill, 
                  buttonlabels[b], textSize);             // text
  }

  // Save the y position to avoid draws
  
  buttons_y = y;
  
}

// Map the coordinate X
  
uint16_t mapXValue(TSPoint p) {

  uint16_t x = map(p.x, TS_MINX, TS_MAXX, 0, tft.width());

  //Correct offset of touch. Manual calibration
  //x+=1;
  
  return x;

}

// Map the coordinate Y

uint16_t mapYValue(TSPoint p) {

  uint16_t y = map(p.y, TS_MINY, TS_MAXY, 0, tft.height());

  //Correct offset of touch. Manual calibration
  //y-=2;

  return y;
}

