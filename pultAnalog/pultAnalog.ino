#define cs   10
#define dc   8
#define rst  0  // you can also connect this to the Arduino reset

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <SPI.h>

#if defined(__SAM3X8E__)
    #undef __FlashStringHelper::F(string_literal)
    #define F(string_literal) string_literal
#endif

Adafruit_ST7735 tft = Adafruit_ST7735(cs, dc, rst);

#define BAUDRATE 9600

// small joystick
#define PIN_SMALL_JOYSTICK 3
#define BUTTON_NONE 0
#define BUTTON_DOWN 1
#define BUTTON_RIGHT 2
#define BUTTON_SELECT 3
#define BUTTON_UP 4
#define BUTTON_LEFT 5

#define PIN_KEYBOARD 0

#define JOYSTICK_SCALE 20
#define JOYSTICK_1_BTN 14
#define JOYSTICK_2_BTN 15
int joystick_pinout[4] = {1, 2, 4, 5};

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
  
  tft.setCursor(0,0);  tft.print("Small:");
  tft.setCursor(0,20); tft.print("KB:");
  
  tft.drawRect(0, 45, 51, 51, ST7735_WHITE);
  tft.drawRect(55, 45, 51, 51, ST7735_WHITE);
  
  pinMode(JOYSTICK_1_BTN, INPUT);
  //pinMode(JOYSTICK_2_BTN, INPUT);
}

#define C2I (int)(unsigned char)

void loop(void)
{
  
  char x[5];
  for (int i=0; i<4; i++) {
    x[i] = (char)((analogRead(joystick_pinout[i])-512)/JOYSTICK_SCALE+'z');
  }
  x[4] = 0;
  
  Serial1.print('A');
  Serial1.print(x);
  Serial1.print("\xFE");
  Serial.print('A');
  Serial.println(x);
  
  if (!digitalRead(JOYSTICK_1_BTN)) {
    Serial1.print("F1\xFE");
    Serial.println("F1");
  }
  
  switch(readButton()) {
  case BUTTON_DOWN:  Serial1.print("JD\xFE"); Serial.println("JD"); break;
  case BUTTON_UP:    Serial1.print("JU\xFE"); Serial.println("JU"); break;
  case BUTTON_LEFT:  Serial1.print("JL\xFE"); Serial.println("JL"); break;
  case BUTTON_RIGHT: Serial1.print("JR\xFE"); Serial.println("JR"); break;
  }
  
  switch(readKeyboard()) {
  case 1: Serial1.print("S1\xFE"); Serial.println("S1"); break;
  case 2: Serial1.print("S2\xFE"); Serial.println("S2"); break;
  case 3: Serial1.print("S3\xFE"); Serial.println("S3"); break;
  case 4: Serial1.print("S4\xFE"); Serial.println("S4"); break;
  case 5: Serial1.print("S5\xFE"); Serial.println("S5"); break;
  }
 
  tft.fillRect(80, 0, 20, 40, ST7735_BLACK);
  
  tft.setCursor(80,0);  tft.print(readButton());
  tft.setCursor(80,20); tft.print(readKeyboard());
  
  tft.fillRect(1, 46, 49, 49, ST7735_BLACK);
  tft.fillRect(56, 46, 49, 49, ST7735_BLACK);
  
  int z = (int)'z';
  tft.fillRect(24+C2I(x[0])-z, 69+z-C2I(x[1]), 3, 3, ST7735_WHITE);
  tft.fillRect(79+C2I(x[2])-z, 69+z-C2I(x[3]), 3, 3, ST7735_WHITE);
  
  delay(20);
}

int readButton(void) {
  int a = analogRead(PIN_SMALL_JOYSTICK);
  
  if (a < 41) return BUTTON_DOWN;
  if (a < 205) return BUTTON_RIGHT;
  if (a < 308) return BUTTON_SELECT;
  if (a < 410) return BUTTON_UP;
  if (a < 656) return BUTTON_LEFT;
  return BUTTON_NONE;
}

int readKeyboard(void) {
  int a = analogRead(PIN_KEYBOARD);
  
  if (a < 140) return 0;
  if (a < 400) return 5;
  if (a < 610) return 4;
  if (a < 790) return 3;
  if (a < 950) return 2;
  return 1;
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

