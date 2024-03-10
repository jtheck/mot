/************************************
 Mot.moe 'Hello World' example.
************************************/

//MM PROJECT Hello World
//MM BOARDS [UNO, ESP8266, ESP01]
//MM FEATURES [LED, MONITOR, SCREEN, BUZZER]
//MM LED [UNO, ESP8266, ESP01]
//MM MONITOR [UNO, ESP8266, ESP01]
//MM SCREEN [UNO, ESP8266, ESP01]
//MM BUZZER [UNO, ESP8266, ESP01]

#define IS_UNO
// #define IS_ESP8266
// #define IS_ESP01

#define HAS_LED
#define HAS_MONITOR
// #define HAS_SCREEN
// #define HAS_BUZZER



#ifdef HAS_LED

#ifdef IS_UNO
#define BOARD_LED 13
#endif //IS_UNO
#ifdef IS_ESP8266
#define BOARD_LED 2
#endif //IS_ESP8266
#ifdef IS_ESP01
#define BOARD_LED 1
#endif


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

struct Animation LEDAnimation = {
  .startTime = 0,
  .currentFrame = 0,
  .keyframes = {
    {40, true},
    {150, false},
    {250, true},
    {420, false},
    {650, true},
    {940, false},
    {3200, false}
  }
};

int ledFrame = 0;
unsigned long ledTimer = 0;


#endif //HAS_LED


struct Timing {
  unsigned long startTime;
  unsigned long frameStart;
  unsigned long framePrev;
  unsigned long frameDuration;
};

struct Timing timer =
  {0, 0, 0, 0};

void setup() {
  // put your setup code here, to run once:

  #ifdef HAS_LED

  pinMode(BOARD_LED, OUTPUT);

  #endif


  #ifdef HAS_MONITOR

  Serial.begin(9600);
  Serial.println("Hello World!");

  #endif
}





void loop() {
  // Progress frame timings
  timer.frameStart = millis();
  // timer.frameDuration = timer.frameStart - timer.framePrev;
  timer.framePrev = timer.frameStart;



  #ifdef HAS_LED
  // Step "Hello World" LED animation
  int elapsed = timer.frameStart - LEDAnimation.startTime;
  if (elapsed > LEDAnimation.keyframes[LEDAnimation.currentFrame].time){
    digitalWrite(BOARD_LED, LEDAnimation.keyframes[LEDAnimation.currentFrame].state);
    if (LEDAnimation.currentFrame < frameCt){
      LEDAnimation.currentFrame++;
    } else {
      LEDAnimation.currentFrame = 0;
      LEDAnimation.startTime = timer.frameStart;
    }
  }
  #endif //HAS_LED


  #ifdef HAS_MONITOR

  // Serial.println("bop");

  #endif //HAS_MONITOR

}
