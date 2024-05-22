/**************************************************************************
 Two-screen Hourglass and eyeball example.
  Ft. Onboard Tilt, Dual SSD1306 OLED Screens,
    External IMU MPU6050 Tilt, 2+n Control
 **************************************************************************/
//MM PROJECT Hourglass Eyeballs
//MM BOARDS [NANO33BLE, ESP8266]
//MM FEATURES [SCREENS, IMU, 2NCONTROL]
//MM NANO33BLE [SCREENS, IMU, 2NCONTROL]
//MM ESP8266 [SCREENS, IMU, 2NCONTROL]


#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
Adafruit_MPU6050 mpu;

//#include <ArduinoSound.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels

#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define VIRTUAL_WIDTH 256 // double wide
#define VIRTUAL_HEIGHT 64

// ARDUINO NANO 33 BLE
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
#define SCREEN_ADDRESS2 0x3D ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
Adafruit_SSD1306 display2(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);



#define NUMFLAKES     100 // Number of snowflakes in the animation example

#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16
static const unsigned char PROGMEM logo_bmp[] =
{ 0b00000000, 0b11000000,
  0b00000001, 0b11000000,
  0b00000001, 0b11000000,
  0b00000011, 0b11100000,
  0b11110011, 0b11100000,
  0b11111110, 0b11111000,
  0b01111110, 0b11111111,
  0b00110011, 0b10011111,
  0b00011111, 0b11111100,
  0b00001101, 0b01110000,
  0b00011011, 0b10100000,
  0b00111111, 0b11100000,
  0b00111111, 0b11110000,
  0b01111100, 0b11110000,
  0b01110000, 0b01110000,
  0b00000000, 0b00110000 };

void setup() {
  Serial.begin(9600);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  if(!display2.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS2)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // IMU
  byte gyro = mpu.begin();
  if (!mpu.begin()){
    Serial.println("fail");
    while(1){
      delay(10);
      } // Wait for successful connection (0)
  }
  // Serial.println("found!");
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G); // 2 < 4 < 8 < 16 +-G
  mpu.setGyroRange(MPU6050_RANGE_500_DEG); // 250 < 500 < 1000 < 2000 deg/s
  mpu.setFilterBandwidth(MPU6050_BAND_5_HZ); // 5, 10, 21, 44, 94, 184, 260 HZ 
  // Serial.println(mpu.getAccelerometerRange());
  // Serial.println(mpu.getGyroRange());
  // Serial.println(mpu.getFilterBandwidth());


  // Clear the buffer
  display2.clearDisplay();
  display.clearDisplay();

  testanimate(logo_bmp, LOGO_WIDTH, LOGO_HEIGHT); // Animate bitmaps
}

void loop() {
}


#define XPOS   0 // Indexes into the 'icons' array in function below
#define YPOS   1
#define DELTAY 2

void testanimate(const uint8_t *bitmap, uint8_t w, uint8_t h) {
  int8_t f, icons[NUMFLAKES][3];

  // Initialize 'snowflake' positions
  for(f=0; f< NUMFLAKES; f++) {
    icons[f][XPOS]   = random(1 - LOGO_WIDTH, display.width());
    icons[f][YPOS]   = random(-LOGO_HEIGHT, display.height());
    icons[f][DELTAY] = random(1, 6);
    Serial.print(F("x: "));
    Serial.print(icons[f][XPOS], DEC);
    Serial.print(F(" y: "));
    Serial.print(icons[f][YPOS], DEC);
    Serial.print(F(" dy: "));
    Serial.println(icons[f][DELTAY], DEC);
  }

  for(;;) { // Loop forever...
       sensors_event_t a, g, temp;
       mpu.getEvent(&a, &g, &temp);
       Serial.println(a.acceleration.x);
       Serial.println(a.acceleration.y);
//    
    display.clearDisplay(); // Clear the display buffer
    display2.clearDisplay(); // Clear the display buffer

    // Draw each snowflake:
    for(f=0; f< NUMFLAKES; f++) {
//  display.drawCircle(icons[f][XPOS], icons[f][YPOS], 9, SSD1306_WHITE);

    display.drawPixel(icons[f][XPOS], icons[f][YPOS], SSD1306_WHITE);
display2.drawPixel(icons[f][XPOS], icons[f][YPOS], SSD1306_WHITE);

      // display.drawBitmap(icons[f][XPOS], icons[f][YPOS], bitmap, w, h, SSD1306_WHITE);
//      display2.drawBitmap(icons[f][XPOS], icons[f][YPOS], bitmap, w, h, SSD1306_WHITE);
    }

    display.display(); // Show the display buffer on the screen
    display2.display();
    delay(10);

    // Then update coordinates of each flake...
    for(f=0; f< NUMFLAKES; f++) {
      icons[f][YPOS] -= a.acceleration.x+a.acceleration.x*random(1,2);//cons[f][DELTAY];
      icons[f][XPOS] -= a.acceleration.y+a.acceleration.y*random(1,2);//cons[f][DELTAY];
      
      // If snowflake is off the bottom of the screen...
      if (icons[f][YPOS] >= display.height()) {
        // Reinitialize to a random position, just off the top
        icons[f][XPOS]   = random(1 - LOGO_WIDTH, display.width());
        icons[f][YPOS]   = -LOGO_HEIGHT;
        icons[f][DELTAY] = random(1, 6);
      }
      if (icons[f][YPOS] < -LOGO_HEIGHT) {
        // Reinitialize to a random position, just off the top
        icons[f][XPOS]   = random(1 - LOGO_WIDTH, display.width());
        icons[f][YPOS]   = display.height();
        icons[f][DELTAY] = random(-6, -1);
      }
    }
  }
}
