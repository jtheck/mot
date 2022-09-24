/*********
 esp-01 momo
 -must pull up EN pin
*********/
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h> // OLED Screen


// SCREEN
#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, 1);




void setup()
{
//  Serial.begin(115200);
//  Serial.println("init !");

  // I2C
  Wire.begin(2,0);

  // SCREEN
  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("hello MoMo");
  display.display(); 
}

void loop()
{
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("hello MoMo!");
  display.display(); 
  
//  Serial.println("run !");

  // blink led
//  digitalWrite(LED_BUILTIN, HIGH);
//  digitalWrite(LED, HIGH);
//  delay(1000);
//  digitalWrite(LED_BUILTIN, LOW);
//  digitalWrite(LED, HIGH);
  delay(1000);
}
