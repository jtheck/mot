/************************************
  Mot.moe 'Excellent Timing Timer' example.
  Featuring: Buzzer Tone, ssd1306 lcd
  Considerations: Extensibility, time management!
************************************/
//MM PROJECT Timer
//MM BOARDS [UNO, 8266]
//MM FEATURES [INCLUDED]
//MM ESP32 [IBUS, WIFI, BT, TX]
// #define MM_IS_ESP32

#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#define OLED_ADDR   0x3C
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

#define BUZZER_PIN 13

// #define BUZZER_PIN 12

#define PIN_BUTTON1 7

#define PIN_TILT 6

// #define PIN_TILT 2

const unsigned long MIN = 60000;
struct Timing {
  unsigned long frameStart;
  unsigned long framePrev;
  unsigned long startTime;
  unsigned long elapsedTime;
  unsigned long timer;
  
};
struct Timing timer = {0, 0, 0, 0, MIN};



void setup() {
  // put your setup code here, to run once:
// initialize and clear display
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  
  display.clearDisplay();
  display.display();

  // display a line of text
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(17,15);
  display.print("TiMER!");

  // update display with all of the above graphics
  display.display();

  timer.startTime = millis();

  pinMode(BUZZER_PIN, OUTPUT);

// pinMode(PIN_BUTTON1, INPUT);

//   pinMode(PIN_TILT, INPUT);     // Set tiltPin as input
//   digitalWrite(PIN_TILT, HIGH);  // Enable internal pull-up resistor
}
void loop() {
  // put your main code here, to run repeatedly:
  // Timing
  timer.frameStart = millis();
  timer.framePrev = timer.frameStart;

  timer.elapsedTime = timer.frameStart - timer.startTime;


if (digitalRead(PIN_BUTTON1) == HIGH){
if (timer.timer == 30*MIN){
  timer.timer = MIN;
}
if (timer.timer == 15*MIN){
  timer.timer = 30*MIN;
}
if (timer.timer == 10*MIN){
  timer.timer = 15*MIN;
}
if (timer.timer == 5*MIN){
  timer.timer = 10*MIN;
}
if (timer.timer == 2*MIN){
  timer.timer = 5*MIN;
}
if (timer.timer == MIN){
  timer.timer = 2*MIN;
}

delay(165);
}
if (digitalRead(PIN_TILT)) {  // Check if tilt switch is HIGH
  timer.startTime = millis();
  timer.elapsedTime = 0;
}

  display.clearDisplay(); // Clear the display buffer
  display.setCursor(27,5);
  display.print(msToString(timer.timer));
  // display.print(msToString(timer.timer - timer.elapsedTime));
  display.setCursor(17,25);
  display.print("TiMER!");

  // display.setCursor(125,25);
  // display.print("-"+msToString(timer.timer - timer.elapsedTime));

  display.setCursor(27,50);
  display.print(msToString(timer.elapsedTime));
  // update display with all of the above graphics
  display.display();

delay(33);
  if (timer.elapsedTime > timer.timer){


  tone(BUZZER_PIN, 69); // Generate a 4000 Hz tone
  delay(90);            // Wait for 1 second
  noTone(BUZZER_PIN);     // Stop the tone
    
  tone(BUZZER_PIN, 42); // Generate a 4000 Hz tone
delay(120);            // Wait for 1 second
  noTone(BUZZER_PIN);

  tone(BUZZER_PIN, 42); // Generate a 4000 Hz tone
  delay(120);            // Wait for 1 second
  noTone(BUZZER_PIN);     // Stop the tone

delay(31);
  tone(BUZZER_PIN, 1233); // Generate a 4000 Hz tone
  delay(144);            // Wait for 1 second
  noTone(BUZZER_PIN);     // Stop the tone

// 
  // delay(1000);  

    timer.startTime = millis();
  
  }
  
}


String msToString(unsigned long ms){
  int totalSeconds = ms / 1000;
  int hours = totalSeconds / 3600;
  int minutes = (totalSeconds % 3600) / 60;
  int seconds = totalSeconds % 60;
  
  char timeString[20];
  sprintf(timeString, "%02d:%02d:%02d", hours, minutes, seconds);
  
  return timeString;
}


