#define cs   10
#define dc   8
#define rst  0  // you can also connect this to the Arduino reset

#define BUTTON_NONE 0
#define BUTTON_DOWN 1
#define BUTTON_RIGHT 2
#define BUTTON_SELECT 3
#define BUTTON_UP 4
#define BUTTON_LEFT 5

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <SPI.h>

#if defined(__SAM3X8E__)
    #undef __FlashStringHelper::F(string_literal)
    #define F(string_literal) string_literal
#endif

Adafruit_ST7735 tft = Adafruit_ST7735(cs, dc, rst);
int av=90;
int ah=90;
int r = BUTTON_DOWN;

#define BAUDRATE 9600

void setup(void) {
  Serial.begin(BAUDRATE);
  Serial1.begin(BAUDRATE);
  tft.initR(INITR_BLACKTAB);   // initialize a ST7735S chip, black tab
  tft.setTextWrap(true); // Allow text to run off right edge
  tft.fillScreen(ST7735_BLACK);

  Serial.println("This is a test of the rotation capabilities of the TFT library!");
  Serial.println("Press <SEND> (or type a character) to advance");
 tft.setRotation(3);
  tft.setCursor(0, 0);
    tft.setTextSize(2);
    tft.setTextColor(ST7735_WHITE);
}

#define INCR_MIN 1
#define INCR_ACC 1

int previousBtn = 0;
int incr = INCR_MIN;

void loop(void) 
{
  if (r != previousBtn || r != BUTTON_NONE) {
    previousBtn = r;
    tft.fillRect(80, 40, 50, 14, ST7735_BLACK);
    tft.setCursor(80,40);
    tft.print(readButton());
    tft.setCursor(0,0);
    tft.fillRect(0, 0, 80, 30, ST7735_BLACK);
    tft.print("v="); tft.println(av);
    tft.print("h="); tft.println(ah);
  }
  
  r=readButton();
  
  if (r==BUTTON_LEFT) av += incr;
  if (r==BUTTON_RIGHT) av -= incr;
  
  if (r==BUTTON_UP) ah += incr;
  if (r==BUTTON_DOWN) ah -= incr;
  
  // clamp
  av = av>180 ? 180 : (av<1 ? 1: av);
  ah = ah>180 ? 180 : (ah<1 ? 1: ah);
  
  if (r==BUTTON_SELECT) {
    Serial.print("F");
    Serial.print((char)254);
    Serial1.print("F");
    Serial1.print((char)254);
  }
  
  if (r!=BUTTON_SELECT && r!=BUTTON_NONE) {
    Serial.print("A");
    Serial.print((char)ah);
    Serial.print((char)av);
    Serial.print((char)254);
    
    Serial1.print("A");
    Serial1.print((char)ah);
    Serial1.print((char)av);
    Serial1.print((char)254);
    
    delay(30);
    
    incr += INCR_ACC;
  } else {
    incr = INCR_MIN;
  }
}

int readButton(void) {
  float a = analogRead(3);
  
  a *= 5.0;
  a /= 1024.0;
  
  if (a < 0.2) return BUTTON_DOWN;
  if (a < 1.0) return BUTTON_RIGHT;
  if (a < 1.5) return BUTTON_SELECT;
  if (a < 2.0) return BUTTON_UP;
  if (a < 3.2) return BUTTON_LEFT;
  else return BUTTON_NONE;
}

//
//
//
//void rotateText() {
//  for (uint8_t i=0; i<4; i++) {
//    tft.fillScreen(ST7735_BLACK);
//    Serial.println(tft.getRotation(), DEC);
//
//    tft.setCursor(0, 30);
//    tft.setTextColor(ST7735_RED);
//    tft.setTextSize(1);
//    tft.println("Hello World!");
//    tft.setTextColor(ST7735_YELLOW);
//    tft.setTextSize(2);
//    tft.println("Hello World!");
//    tft.setTextColor(ST7735_GREEN);
//    tft.setTextSize(3);
//    tft.println("Hello World!");
//    tft.setTextColor(ST7735_BLUE);
//    tft.setTextSize(4);
//    tft.print(1234.567);
//    while (!Serial.available());
//    Serial.read();  Serial.read();  Serial.read();
//  
//    tft.setRotation(tft.getRotation()+1);
//  }
//}
//

//
//void rotateFillcircle(void) {
//  for (uint8_t i=0; i<4; i++) {
//    tft.fillScreen(ST7735_BLACK);
//    Serial.println(tft.getRotation(), DEC);
//
//    tft.fillCircle(10, 30, 10, ST7735_YELLOW);
//
//    while (!Serial.available());
//    Serial.read();  Serial.read();  Serial.read();
//
//    tft.setRotation(tft.getRotation()+1);
//  }
//}
//
//void rotateDrawcircle(void) {
//  for (uint8_t i=0; i<4; i++) {
//    tft.fillScreen(ST7735_BLACK);
//    Serial.println(tft.getRotation(), DEC);
//
//    tft.drawCircle(10, 30, 10, ST7735_YELLOW);
// 
//    while (!Serial.available());
//    Serial.read();  Serial.read();  Serial.read();
//  
//    tft.setRotation(tft.getRotation()+1);
//  }
//}
//
//void rotateFillrect(void) {
//  for (uint8_t i=0; i<4; i++) {
//    tft.fillScreen(ST7735_BLACK);
//    Serial.println(tft.getRotation(), DEC);
//
//    tft.fillRect(10, 20, 10, 20, ST7735_GREEN);
// 
//    while (!Serial.available());
//    Serial.read();  Serial.read();  Serial.read();
//
//    tft.setRotation(tft.getRotation()+1);
//  }
//}
//
//void rotateDrawrect(void) {
//  for (uint8_t i=0; i<4; i++) {
//    tft.fillScreen(ST7735_BLACK);
//    Serial.println(tft.getRotation(), DEC);
//
//    tft.drawRect(10, 20, 10, 20, ST7735_GREEN);
// 
//    while (!Serial.available());
//    Serial.read();  Serial.read();  Serial.read();
//
//    tft.setRotation(tft.getRotation()+1);
//  }
//}
//
//void rotateFastline(void) {
//  for (uint8_t i=0; i<4; i++) {
//    tft.fillScreen(ST7735_BLACK);
//    Serial.println(tft.getRotation(), DEC);
//
//    tft.drawFastHLine(0, 20, tft.width(), ST7735_RED);
//    tft.drawFastVLine(20, 0, tft.height(), ST7735_BLUE);
//
//    while (!Serial.available());
//    Serial.read();  Serial.read();  Serial.read();
//
//    tft.setRotation(tft.getRotation()+1);
//  }
//}
//
//void rotateLine(void) {
//  for (uint8_t i=0; i<4; i++) {
//    tft.fillScreen(ST7735_BLACK);
//    Serial.println(tft.getRotation(), DEC);
//
//    tft.drawLine(tft.width()/2, tft.height()/2, 0, 0, ST7735_RED);
//    while (!Serial.available());
//    Serial.read();  Serial.read();  Serial.read();
//
//    tft.setRotation(tft.getRotation()+1);
//  }
//}
//
//void rotatePixel(void) {
//  for (uint8_t i=0; i<4; i++) {
//    tft.fillScreen(ST7735_BLACK);
//    Serial.println(tft.getRotation(), DEC);
//
//    tft.drawPixel(10,20, ST7735_WHITE);
//    while (!Serial.available());
//    Serial.read();  Serial.read();  Serial.read();
//
//    tft.setRotation(tft.getRotation()+1);
//  }
//}
//
//void rotateTriangle(void) {
//  for (uint8_t i=0; i<4; i++) {
//    tft.fillScreen(ST7735_BLACK);
//    Serial.println(tft.getRotation(), DEC);
//
//    tft.drawTriangle(20, 10, 10, 30, 30, 30, ST7735_GREEN);
//    while (!Serial.available());
//    Serial.read();  Serial.read();  Serial.read();
//
//    tft.setRotation(tft.getRotation()+1);
//  }
//}
//
//void rotateFillTriangle(void) {
//  for (uint8_t i=0; i<4; i++) {
//    tft.fillScreen(ST7735_BLACK);
//    Serial.println(tft.getRotation(), DEC);
//
//    tft.fillTriangle(20, 10, 10, 30, 30, 30, ST7735_RED);
//    while (!Serial.available());
//    Serial.read();  Serial.read();  Serial.read();
//
//    tft.setRotation(tft.getRotation()+1);
//  }
//}
//
//void rotateRoundRect(void) {
//  for (uint8_t i=0; i<4; i++) {
//    tft.fillScreen(ST7735_BLACK);
//    Serial.println(tft.getRotation(), DEC);
//
//    tft.drawRoundRect(20, 10, 25, 15, 5, ST7735_BLUE);
//    while (!Serial.available());
//    Serial.read();  Serial.read();  Serial.read();
//
//    tft.setRotation(tft.getRotation()+1);
//  }
//}
//
//void rotateFillRoundRect(void) {
//  for (uint8_t i=0; i<4; i++) {
//    tft.fillScreen(ST7735_BLACK);
//    Serial.println(tft.getRotation(), DEC);
//
//    tft.fillRoundRect(20, 10, 25, 15, 5, ST7735_CYAN);
//    while (!Serial.available());
//    Serial.read();  Serial.read();  Serial.read();
//
//    tft.setRotation(tft.getRotation()+1);
//  }
//}
//
//void rotateChar(void) {
//  for (uint8_t i=0; i<4; i++) {
//    tft.fillScreen(ST7735_BLACK);
//    Serial.println(tft.getRotation(), DEC);
//
//    tft.drawChar(25, 15, 'A', ST7735_WHITE, ST7735_WHITE, 1);
//    while (!Serial.available());
//    Serial.read();  Serial.read();  Serial.read();
//
//    tft.setRotation(tft.getRotation()+1);
//  }
//}
//
//void rotateString(void) {
//  for (uint8_t i=0; i<4; i++) {
//        Serial.println(tft.getRotation(), DEC);
//
//    
//    
//  }
//}

