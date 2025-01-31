/******

  'Eyeballs, Moderately Expressive'

  Featuring: Single & Dual SSD1306 I2C OLEDs, Onboard Tilt, External IMU MPU6050 Tilt
  Considerations: I2C addressing.

******/
//MM PROJECT Eyeballs





//#define MM_IS_UNO
//#define MM_HAS_1SCREEN
#define MM_HAS_2SCREENS


#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//#include <ArduinoSound.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// #define VIRTUAL_WIDTH 256 // double wide
// #define VIRTUAL_HEIGHT 64

// ARDUINO NANO 33 BLE
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#ifdef MM_HAS_2SCREENS
#define SCREEN2_ADDRESS 0x3D ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display2(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
#endif

struct Timing {
  unsigned long frameStart;
  unsigned long framePrev;
};
struct Timing timer = {0, 0};

struct Keyframe {
  int time;
  int state;
};

const int maxFrameCt = 6;
struct Animation {
  unsigned long startTime;
  int duration; 
  int currentFrame;
  int frameCt;
  struct Keyframe keyframes[maxFrameCt];
  int *target;  
};

struct Gesture {
  unsigned long startTime;
  int duration;
  // int frameCt;
  // int currentFrame;
  struct Animation animations[4];
};



struct Eye {
  int x;
  int y;
  int lidUpper;
  int lidLower;
  int irisRadius;
  int pupilRadius;
  int brow;
  int lines[15];
};



struct Eye eye1 = {
  .x = SCREEN_WIDTH/2,
  .y = SCREEN_HEIGHT/2 +6,
  .lidUpper = 15,
  .lidLower = SCREEN_HEIGHT-1,
  .irisRadius = 24,
  .pupilRadius = 9,
  .brow = 0,//7
  // .lines = {} 
};

struct Animation blinkUpperLidLeft = {
  .startTime = 0,
  .duration = 175,
  .currentFrame = 0,
  .frameCt = 5,
  .keyframes = {
    {2, 13},
    {40, 19},
    {50, 59},
    {60, 19},
    {175, 15}
  },
  .target = &eye1.lidUpper,
};
struct Animation blinkLowerLidLeft = {
  .startTime = 0,
  .duration = 60,
  .currentFrame = 0,
  .frameCt = 3,
  .keyframes = {
    {2, 63},
    {50, 60},
    {60, SCREEN_HEIGHT-1}
  },
  .target = &eye1.lidLower
};

#ifdef MM_HAS_2SCREENS
struct Eye eye2 = {
  .x = SCREEN_WIDTH/2,
  .y = SCREEN_HEIGHT/2 +6,
  .lidUpper = 15,
  .lidLower = SCREEN_HEIGHT-1,
  .irisRadius = 24,
  .pupilRadius = 9,
  .brow = 0,//-7
  // .lines = {} 
};

struct Animation blinkUpperLidRight = {
  .startTime = 0,
  .duration = 175,
  .currentFrame = 0,
  .frameCt = 5,
  .keyframes = {
    {2, 13},
    {40, 19},
    {50, 59},
    {60, 19},
    {175, 15}
  },
  .target = &eye2.lidUpper,
};
struct Animation blinkLowerLidRight = {
  .startTime = 0,
  .duration = 60,
  .currentFrame = 0,
  .frameCt = 3,
  .keyframes = {
    {2, 63},
    {50, 60},
    {60, SCREEN_HEIGHT-1}
  },
  .target = &eye2.lidLower
};
#endif




struct Gesture blink = {
  .startTime = 0,
  .duration = 1255,
  .animations = {
    {blinkUpperLidLeft},
    {blinkLowerLidLeft},
    {blinkUpperLidRight},
    {blinkLowerLidRight}
  }
};

int gestureQueueLength = 1;
struct Gesture gestureQueue[4];





void setup() {
  Serial.begin(115200);
  // while(!Serial);
  
  randomSeed(analogRead(0));

  gestureQueue[0] = blink;

  
 
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    // Serial.println(F("SSD1306 allocation failed"));
    // for(;;); // Don't proceed, loop forever
  }
  // display.invertDisplay(true);
  display.clearDisplay();
  initEye(&eye1);

  
  #ifdef MM_HAS_2SCREENS
  if(!display2.begin(SSD1306_SWITCHCAPVCC, SCREEN2_ADDRESS)) {
    // Serial.println(F("SSD1306 allocation failed"));
    // for(;;); // Don't proceed, loop forever
  }
  display2.clearDisplay();
  initEye(&eye2);
  #endif

  if (Serial) Serial.println("Begin!");
}

void loop() {
  // Timing
  timer.frameStart = millis();
  timer.framePrev = timer.frameStart;


  if (random(1000) < 13){
    int x = random(SCREEN_WIDTH);
    eye1.x = x;
    #ifdef MM_HAS_2SCREENS
    eye2.x = x;
    #endif
  }
  if (random(1000) < 13){
    gestureQueueLength = 1;
    gestureQueue[0] = blink;
  }



  for (int i=0; i<gestureQueueLength; i++){
    struct Gesture *tGesture = &gestureQueue[i];
    if (tGesture->startTime == 0) tGesture->startTime = timer.frameStart; 
    // bool advancedFrame = false;
    int gElapsed = timer.frameStart - tGesture->startTime;

    for (int j=0; j<4; j++){
      struct Animation *tAnim = &tGesture->animations[j];

      int elapsed = timer.frameStart - tAnim->startTime;
      if (elapsed > tAnim->keyframes[tAnim->currentFrame].time){
        *tAnim->target = tAnim->keyframes[tAnim->currentFrame].state;
        // Serial.println((String)tAnim->currentFrame+ " v "+(frameCt-1));
      
        if (tAnim->currentFrame < tAnim->frameCt-1){
          tAnim->currentFrame++;
        }
      }
            
    }

    if (gElapsed > tGesture->duration){
      // gestureQueue[i] = null;
      gestureQueueLength = 0;

      tGesture->startTime = 0;
      for (int j=0; j<4; j++){
        struct Animation *tAnim = &tGesture->animations[j];
        tAnim->currentFrame = 0;
        tAnim->startTime = timer.frameStart; 
      }

    }
  }


  // Serial.print((String)elapsed+" v "+testAnim.keyframes[testAnim.currentFrame].time+" frame "+testAnim.currentFrame);





  display.clearDisplay(); // Clear the display buffer
  #ifdef MM_HAS_2SCREENS
  display2.clearDisplay();
  #endif
    

  drawEye(eye1, &display);
  #ifdef MM_HAS_2SCREENS
  drawEye(eye2, &display2);
  #endif 


  display.display(); // Show the display buffer on the screen
  #ifdef MM_HAS_2SCREENS
  display2.display();
  #endif
}





void initEye(struct Eye* eye){
  for (int i=0; i<15; i++){
    eye->lines[i] = random(360);
  }
}


void drawEye(struct Eye eye, Adafruit_SSD1306 *disp){
  // disp->fillRect(0, eye.lidUpper, SCREEN_WIDTH, eye.lidLower, 1);
  // disp->fillCircle(eye.x, eye.y, eye.irisRadius+1, 0); 
  disp->drawCircle(eye.x, eye.y, eye.irisRadius, 1); 
  disp->drawCircle(eye.x, eye.y, eye.irisRadius+1, 1);
  disp->fillCircle(eye.x, eye.y, eye.pupilRadius, 1);
  // disp->drawCircle(eye.x-1.6*eye.pupilRadius, eye.y+1.6*eye.pupilRadius, eye.pupilRadius*1.4, 1);


  for (int i=0; i<15; i++){
    disp->drawLine(eye.x, eye.y, eye.x+cos(eye.lines[i])*eye.irisRadius, eye.y+sin(eye.lines[i])*eye.irisRadius, 1);
  }

  for (int i=0; i<eye.lidUpper; i++){
    disp->drawFastHLine(0, i, SCREEN_WIDTH, 0);
  }
  disp->drawFastHLine(0, eye.lidUpper, SCREEN_WIDTH, 1);
  
  for (int i=eye.lidLower; i<SCREEN_HEIGHT; i++){
    disp->drawFastHLine(0, i, SCREEN_WIDTH, 0); 
  }
  disp->drawFastHLine(0, eye.lidLower, SCREEN_WIDTH, 1);

  disp->drawLine(0, 5+eye.brow, SCREEN_WIDTH, 5-eye.brow, 1);
}