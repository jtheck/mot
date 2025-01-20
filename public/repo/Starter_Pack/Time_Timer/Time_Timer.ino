/************************************
  Mot.moe's 'Excellent Timing Timer' Starter Pack Example.

  Featuring: Buzzer Tone, ssd1306 lcd
  Considerations: Extensibility and time management.
************************************/
//MM PROJECT Timer
//MM BOARDS [UNO, ESP32, ESP8266]
//MM FEATURES [BUZZER, SCREEN]
//MM UNO [BUZZER, SCREEN]
//MM ESP32 [BUZZER, SCREEN]
//MM ESP8266 [BUZZER, SCREEN]
//MM
// #define MM_IS_UNO
// #define MM_IS_ESP32
// #define MM_IS_ESP8266
//MM
// #define MM_HAS_SCREEN
// #define MM_HAS_BUZZER
//MM
#ifdef MM_IS_UNO
// Arduino UNO Pin Out
// 123
#define PIN_BUTTON_ACTION 7
#ifdef MM_HAS_BUZZER
#define BUZZER_PIN 12
#define PIN_TILT 2
#endif // MM_HAS_BUZZER
#endif // MM_IS_UNO
//MM
#ifdef MM_IS_ESP32
// ESP32 Pin Out
//

#endif // MM_IS_ESP32
//MM
#ifdef MM_IS_ESP8266
// ESP8266 Pin Out
// 123
#define PIN_BUTTON_ACTION 15
#ifdef MM_HAS_BUZZER
#define BUZZER_PIN 13
#define PIN_TILT 6
#endif // MM_HAS_BUZZER
#endif // MM_IS_ESP8266
//MM
#ifdef MM_HAS_SCREEN
// Ini LCD Display
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#define OLED_ADDR   0x3C
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
#endif // MM_HAS_SCREEN
//MM

// Basic Timing
const unsigned long MINUTE = 60000;
struct Timing {
  unsigned long frameStart;
  unsigned long framePrev;
  unsigned long startTime;
  unsigned long elapsedTime;
  unsigned long timer;
};
struct Timing timer = {0, 0, 0, 0, MINUTE};

// Timing Timer Time Stops !
#define timerStopsCount 7
int timerStops[timerStopsCount] = {1, 2, 5, 10, 15, 30, 52};
int timerStopsIndex = 0;


void setup() {
  // put your setup code here, to run once:


#ifdef MM_HAS_SCREEN
  // initialize and clear display
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.setTextColor(WHITE);
  display.clearDisplay();
#endif // MM_HAS_SCREEN

  timer.startTime = millis();
#ifdef MM_HAS_BUZZER
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(PIN_BUTTON_ACTION, INPUT);
  // pinMode(PIN_TILT, INPUT); NO8266!    // Set tiltPin as input
  // digitalWrite(PIN_TILT, HIGH);  // Enable internal pull-up resistor
#endif // MM_HAS_BUZZER
} // end void setup()


void loop() {
  // put your main code here, to run repeatedly:


  // Update Timing
  timer.frameStart = millis();
  timer.framePrev = timer.frameStart;
  timer.elapsedTime = timer.frameStart - timer.startTime;

  // Cycle Timing Timer Timer Time
  if (digitalRead(PIN_BUTTON_ACTION) == HIGH){
    timer.timer = timerStops[timerStopsIndex]*MINUTE;
    timerStopsIndex++;
    if (timerStopsIndex == timerStopsCount){
      timerStopsIndex = 0;
    }
    delay(165); // temper button input
  }

  // Test Tilt
  if (digitalRead(PIN_TILT)) {
    timer.startTime = millis();
    timer.elapsedTime = 0;
  }
#ifdef MM_HAS_SCREEN

  // Render Display
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0,5);
  display.print(millisecondsToString(timer.timer));
  // display.print(millisecondsToString(timer.timer - timer.elapsedTime));
  display.setTextSize(3);
  display.setCursor(20,20);
  display.print("TiMER!");
  display.setTextSize(2);
  display.setCursor(7,48);
  display.print(millisecondsToString(timer.elapsedTime));
  display.display();
#endif // MM_HAS_SCREEN

  // Check Timer, Make Tone, Reset Timer
  if (timer.elapsedTime > timer.timer){
#ifdef MM_HAS_BUZZER
    tone(BUZZER_PIN, 69); // Generate a x Hz tone
    delay(90);            // Wait for x ms
    noTone(BUZZER_PIN);     // Stop the tone
    delay(120);           
    tone(BUZZER_PIN, 42); 
    delay(120);           
    noTone(BUZZER_PIN);
    delay(120);           
    tone(BUZZER_PIN, 42);
    delay(120);          
    noTone(BUZZER_PIN);  
    delay(31);
    tone(BUZZER_PIN, 1233);
    delay(144);            
    noTone(BUZZER_PIN);    
#endif // MM_HAS_BUZZER

    timer.startTime = millis();
  }
} // end void loop()
  


String millisecondsToString(unsigned long ms){
  int totalSeconds = ms / 1000;
  int hours = totalSeconds / 3600;
  int minutes = (totalSeconds % 3600) / 60;
  int seconds = totalSeconds % 60;
  char timeString[20];
  sprintf(timeString, "%02d:%02d:%02d", hours, minutes, seconds);
  
  return timeString;
}


