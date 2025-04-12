/************************************
  Mot.moe's 'Hello World' Starter Pack Example.

  Featuring: Onboard LED, Buzzer Chirp, Serial Monitoring, SSD1306 I2C OLED
  Considerations: Feature selection, pin identification and placement. Fault correction.
************************************/
//MM PROJECT Hello World
//MM BOARDS [UNO, ESP32, ESP8266, ESP01]
//MM FEATURES [LED, SERIAL_MONITOR, SCREEN, BUZZER]
//MM
//MM UNO [LED, SERIAL_MONITOR, SCREEN, BUZZER]
//MM ESP32 [SERIAL_MONITOR, SCREEN]
//MM ESP8266 [LED, SERIAL_MONITOR, SCREEN, BUZZER]
//MM ESP01 [LED, SCREEN, SERIAL_MONITOR]
//MM
// #define MM_IS_UNO
// #define MM_IS_ESP32
// #define MM_IS_ESP8266
// #define MM_IS_ESP01
//MM
// #define MM_HAS_LED
// #define MM_HAS_SERIAL_MONITOR
// #define MM_HAS_SCREEN
// #define MM_HAS_BUZZER
//MM
#ifdef MM_IS_UNO
////////////////////////////////////
// Arduino UNO Pin Out
// Serial Clock (SCL) - A5
// Serial Data (SDA) - A4
// Buzzer Pin+ - 12 - D12
////////////////////////////////////
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
#ifdef MM_IS_ESP32
////////////////////////////////////
// ESP32 Pin-Out
// Serial Clock (SCL) - D22- GPIO22
// Serial Data (SDA) - D21 - GPIO21
////////////////////////////////////
#endif // MM_IS_ESP32
//MM
#ifdef MM_IS_ESP8266
////////////////////////////////////
// ESP8266 Pin-Out
// Serial Clock (SCL) - D1 - GPIO5
// Serial Data (SDA) - D2 - GPIO4
// Buzzer Pin+ - SD3 - 12 - GPIO10
////////////////////////////////////
#define ON LOW
#define OFF HIGH
#ifdef MM_HAS_LED
#define BOARD_LED 2
#endif // MM_HAS_LED
#ifdef MM_HAS_BUZZER
#define BUZZER_PIN 12
#endif // MM_HAS_BUZZER
#endif // MM_IS_ESP8266
//MM
#ifdef MM_IS_ESP01
////////////////////////////////////
// ESP01 Pin-Out
// Serial Clock (SCL) - GPIO0
// Serial Data (SDA) - GPIO2
// Chip Enable/Chip Power Down (EN) - 3.3V+ 
////////////////////////////////////
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
//MM

// Animations
struct Keyframe {
  int time;
  bool state;
};
const int framesCount = 7;
struct Animation {
  unsigned long startTime;
  int currentFrame;
  struct Keyframe keyframes[framesCount];
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
struct Animation buzzerExpression = {
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
// Timer
struct Timing {
  unsigned long startTime;
  unsigned long frameStart;
  unsigned long framePrev;
};
struct Timing timer = {0, 0, 0};


void setup() {
  // put your setup code here, to run once:


#ifdef MM_HAS_LED
  pinMode(BOARD_LED, OUTPUT);
#endif // MM_HAS_LED
//MM
#ifdef MM_HAS_BUZZER
  pinMode(BUZZER_PIN, OUTPUT);
#endif // MM_HAS_BUZZER
//MM
#ifdef MM_HAS_SERIAL_MONITOR
  Serial.begin(115200);
  Serial.println("Hello World!");
#endif // MM_HAS_SERIAL_MONITOR
//MM
#ifdef MM_HAS_SCREEN

  // OLED Screen
#ifdef MM_IS_ESP01
  Wire.begin(2,0);
#endif // MM_IS_ESP01
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.clearDisplay();
  display.display();
  // Display a pixel in each corner of the screen
  display.drawPixel(0, 0, WHITE);
  display.drawPixel(SCREEN_WIDTH-1, 0, WHITE);
  display.drawPixel(0, SCREEN_HEIGHT-1, WHITE);
  display.drawPixel(SCREEN_WIDTH-1, SCREEN_HEIGHT-1, WHITE);
  // Display a line of text
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(27,30);
  display.print("Hello, world!");
  // Present Display
  display.display();
#endif // MM_HAS_SCREEN
}


void loop() {
  // put your main code here, to run repeatedly:
  

  // Timer
  timer.frameStart = millis();
  timer.framePrev = timer.frameStart;

#ifdef MM_HAS_LED
  // Step LED animation
  int LEDElapsed = timer.frameStart - LEDAnimation.startTime;
  if (LEDElapsed > LEDAnimation.keyframes[LEDAnimation.currentFrame].time){
    digitalWrite(BOARD_LED, LEDAnimation.keyframes[LEDAnimation.currentFrame].state);
    if (LEDAnimation.currentFrame < framesCount){
      LEDAnimation.currentFrame++;
    } else {
      LEDAnimation.currentFrame = 0;
      LEDAnimation.startTime = timer.frameStart;
    }
  }
#endif // MM_HAS_LED
#ifdef MM_HAS_BUZZER
  // Step BUZZER expression
  int buzzerElapsed = timer.frameStart - buzzerExpression.startTime;
  if (buzzerElapsed > buzzerExpression.keyframes[buzzerExpression.currentFrame].time){
    digitalWrite(BUZZER_PIN, buzzerExpression.keyframes[buzzerExpression.currentFrame].state);
    if (buzzerExpression.currentFrame < framesCount){
      buzzerExpression.currentFrame++;
    } else {
      buzzerExpression.currentFrame = 0;
      buzzerExpression.startTime = timer.frameStart;
    }
  }
#endif // MM_HAS_BUZZER
#ifdef MM_HAS_SERIAL_MONITOR
  Serial.println("Hello World!");
#endif // MM_HAS_SERIAL_MONITOR
}
