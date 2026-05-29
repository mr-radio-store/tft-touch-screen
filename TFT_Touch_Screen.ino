/*
2.4" Inch Touch Screen Shield & Mega 2560 

***
Press, then color change
***

Wire Connection
TFT Pin Label	Connects to Arduino Uno
LCD_D0–D7	D8–D0 (in reverse)
LCD_CS	A3
LCD_RS	A2
LCD_WR	A1
LCD_RD	A0
LCD_RST	RESET or D9
XP	D6
XM	A2
YP	A1
YM	D7
VCC	5V
GND	GND

*/

#include <MCUFRIEND_kbv.h>
#include <Adafruit_GFX.h>
#include <TouchScreen.h>

// Color definitions
#define BLACK   0x0000
#define WHITE   0xFFFF

// Touchscreen pins — adjust if needed
#define YP A1   // must be an analog pin
#define XM A2   // must be an analog pin
#define YM 7    // digital pin
#define XP 6    // digital pin

// Calibration values — these may need to be changed for your screen
#define TS_MINX 100
#define TS_MAXX 920
#define TS_MINY 70
#define TS_MAXY 900

// TouchScreen object
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

// TFT screen object
MCUFRIEND_kbv tft;

bool isWhite = true;  // Toggle flag

void setup() {
  Serial.begin(9600);
  uint16_t ID = tft.readID();
  tft.begin(ID);
  tft.setRotation(1);
  tft.fillScreen(WHITE);
  tft.setTextSize(2);
  tft.setTextColor(BLACK);
  tft.setCursor(10, 10);
  tft.println("Touch to change color");
}

void loop() {
  TSPoint p = ts.getPoint();

  // Restore pin modes after reading
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);

  if (p.z > 200) {  // simple pressure threshold
    int x = map(p.y, TS_MINY, TS_MAXY, 0, tft.width());
    int y = map(p.x, TS_MINX, TS_MAXX, 0, tft.height());

    // Debounce touch
    delay(200);

    // Toggle screen color
    isWhite = !isWhite;
    if (isWhite) {
      tft.fillScreen(WHITE);
      tft.setTextColor(BLACK);
    } else {
      tft.fillScreen(BLACK);
      tft.setTextColor(WHITE);
    }
    
    tft.setCursor(10, 10);
    tft.println("Touch to change color");
  }
}
