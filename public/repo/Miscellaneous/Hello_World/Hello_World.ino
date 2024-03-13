/************************************
 Mot.moe 'Hello World' example.
  Ft. Onboard LED, Piezo Buzzer,
   Serial Monitor, SSD1306 OLED Screen 
************************************/
//MM PROJECT Hello World
//MM BOARDS [UNO, ESP8266, ESP01]
//MM FEATURES [LED, MONITOR, SCREEN, BUZZER]
//MM UNO [LED, MONITOR, SCREEN, BUZZER]
//MM ESP8266 [LED, MONITOR, SCREEN, BUZZER]
//MM ESP01 [LED, SCREEN]
// #define MM_IS_UNO
// #define MM_IS_ESP8266
// #define MM_IS_ESP01
// #define MM_HAS_LED
// #define MM_HAS_MONITOR
// #define MM_HAS_SCREEN
// #define MM_HAS_BUZZER

#ifdef MM_IS_UNO
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
#define ON LOW
#define OFF HIGH
#ifdef MM_HAS_LED
#define BOARD_LED 1
#endif // MM_HAS_LED
#endif // MM_IS_ESP01

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
  // Step "Hello World" BUZZER animation
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
