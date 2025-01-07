/************************************
 Mot.moe 'Hello World' example.
  Ft. Onboard LED, Piezo BUZZER,
   Serial MONITOR, SSD1306 OLED SCREEN,
   WIFI Presence 
************************************/
//MM PROJECT Hello World
//MM BOARDS [UNO, ESP8266, ESP01]
//MM FEATURES [LED, MONITOR, SCREEN, BUZZER]
//MM UNO [LED, MONITOR, SCREEN, BUZZER]
//MM ESP8266 [LED, MONITOR, SCREEN, BUZZER, WIFI]
//MM ESP01 [LED, SCREEN]
#define MM_IS_UNO
// #define MM_IS_ESP8266
// #define MM_IS_ESP01
// #define MM_HAS_LED
// #define MM_HAS_MONITOR
#define MM_HAS_SCREEN
// #define MM_HAS_BUZZER
// #define MM_HAS_WIFI

#ifdef MM_IS_UNO
// SCL A5, SDA A4
#define ON HIGH
#define OFF LOW
#ifdef MM_HAS_LED
#define BOARD_LED 13
#endif // MM_HAS_LED
#ifdef MM_HAS_BUZZER
#define BUZZER_PIN 12
#endif // MM_HAS_BUZZER
#endif // MM_IS_UNO
//MM
#ifdef MM_IS_ESP8266
// SCL D1, SDA D2
#define ON LOW
#define OFF HIGH
#ifdef MM_HAS_LED
#define BOARD_LED 2
#endif // MM_HAS_LED
#ifdef MM_HAS_BUZZER
#define BUZZER_PIN 12
#endif // MM_HAS_BUZZER
#ifdef MM_HAS_WIFI
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#endif // MM_HAS_WIFI
#endif // MM_IS_ESP8266
//MM
#ifdef MM_IS_ESP01
#define ON LOW
#define OFF HIGH
#ifdef MM_HAS_LED
#define BOARD_LED 1
#endif // MM_HAS_LED
#endif // MM_IS_ESP01
//MM
#ifdef MM_HAS_SCREEN
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#define OLED_ADDR   0x3C
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
#endif // MM_HAS_SCREEN


struct Keyframe {
  int time;
  bool state;
};

const int frameCt = 7;
struct Animation {
  unsigned long startTime;
  int currentFrame;
  struct Keyframe keyframes[frameCt];
};

#ifdef MM_HAS_LED
struct Animation LEDAnimation = {
  .startTime = 0,
  .currentFrame = 0,
  .keyframes = {
    {40, ON},
    {150, OFF},
    {250, ON},
    {420, OFF},
    {650, ON},
    {940, OFF},
    {3000, OFF}
  }
};
#endif // MM_HAS_LED
#ifdef MM_HAS_BUZZER
struct Animation buzzerAnimation = {
  .startTime = 0,
  .currentFrame = 0,
  .keyframes = {
    {40, ON},
    {150, OFF},
    {250, ON},
    {420, OFF},
    {650, ON},
    {940, OFF},
    {3000, OFF}
  }
};
#endif // MM_HAS_BUZZER

struct Timing {
  unsigned long startTime;
  unsigned long frameStart;
  unsigned long framePrev;
};
struct Timing timer = {0, 0, 0};


void setup() {
#ifdef MM_HAS_LED
  pinMode(BOARD_LED, OUTPUT);
#endif // MM_HAS_LED
#ifdef MM_HAS_MONITOR
  Serial.begin(9600);
  Serial.println("Hello World!");
#endif // MM_HAS_MONITOR
#ifdef MM_HAS_BUZZER
  pinMode(BUZZER_PIN, OUTPUT);
#endif // MM_HAS_BUZZER
#ifdef MM_HAS_SCREEN
 // initialize and clear display
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.clearDisplay();
  display.display();

  // display a pixel in each corner of the screen
  display.drawPixel(0, 0, WHITE);
  display.drawPixel(127, 0, WHITE);
  display.drawPixel(0, 63, WHITE);
  display.drawPixel(127, 63, WHITE);

  // display a line of text
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(27,30);
  display.print("Hello, world!");

  // update display with all of the above graphics
  display.display();
#endif // MM_HAS_SCREEN
}


void loop() {
  // Timing
  timer.frameStart = millis();
  timer.framePrev = timer.frameStart;

#ifdef MM_HAS_LED
  // Step "Hello World" LED animation
  int LEDElapsed = timer.frameStart - LEDAnimation.startTime;
  if (LEDElapsed > LEDAnimation.keyframes[LEDAnimation.currentFrame].time){
    digitalWrite(BOARD_LED, LEDAnimation.keyframes[LEDAnimation.currentFrame].state);
    if (LEDAnimation.currentFrame < frameCt){
      LEDAnimation.currentFrame++;
    } else {
      LEDAnimation.currentFrame = 0;
      LEDAnimation.startTime = timer.frameStart;
    }
  }
#endif // MM_HAS_LED
#ifdef MM_HAS_MONITOR
#endif // MM_HAS_MONITOR
#ifdef MM_HAS_BUZZER
  // Step "Hello World" BUZZER expression
  int buzzerElapsed = timer.frameStart - buzzerAnimation.startTime;
  if (buzzerElapsed > buzzerAnimation.keyframes[buzzerAnimation.currentFrame].time){
    digitalWrite(BUZZER_PIN, buzzerAnimation.keyframes[buzzerAnimation.currentFrame].state);
    if (buzzerAnimation.currentFrame < frameCt){
      buzzerAnimation.currentFrame++;
    } else {
      buzzerAnimation.currentFrame = 0;
      buzzerAnimation.startTime = timer.frameStart;
    }
  }
#endif // MM_HAS_BUZZER
}
