/*********
 momo remote
*********/
#include <SPI.h>
#include <Wire.h>
#include <RH_ASK.h> // Transmit radio
#include <Adafruit_SSD1306.h> // OLED Screen


// TX/RX
// ESP8266MOD
const int TX_PIN = 12;//d6
const int RX_PIN = 14;//d5
RH_ASK driver(2000, RX_PIN, TX_PIN, 0);



// POTENTIOMETER
//const uint8_t POT_1 = 13;//d7
//const uint8_t POT_2 = 15;//d8


const uint8_t POT_0 = A0;
const uint8_t POT_1 = A1; 
const uint8_t POT_2 = A2;
const uint8_t POT_3 = A3; 
const uint8_t POT_4 = A4;
const uint8_t POT_5 = A5;
 
const int switch_on = 9, switch_off = 10;//sd2, sd3
int dat[3];

const int jbutton = 13;
const int b1 = 0;
const int b2 = 1;

// SCREEN
bool displayEnabled = true;
#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64
#define SCREEN_ADDRESS 0x3C
//Adafruit_SSD1306 display(-1);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);




void setup()
{
  
//  Wire.begin(2,0);
Serial.begin(115200);
//sendData("AT+CIOBAUD=9600\r\n", 2000, TRUE);
//  Serial.begin(9600);
//  if (!driver.init())
    Serial.print("init !");

//  pinMode(switch_on, INPUT);
//  pinMode(switch_off, INPUT);
pinMode(jbutton, INPUT_PULLUP);
pinMode(b1, INPUT_PULLUP);
pinMode(b2, INPUT_PULLUP);
//digitalWrite(POT_1, LOW);
//digitalWrite(POT_2, LOW);
//pinMode(POT_1, OUTPUT);
//pinMode(POT_2, OUTPUT);
//
////
//
//
  // SCREEN
  if (displayEnabled){
    display.setRotation(2); // 180deg flip
    display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
    display.setTextSize(1);
    display.setTextColor(WHITE);  
  }
      

  Serial.println("Setup complete!");
}

void loop()
{
  if (displayEnabled){
    display.clearDisplay();
    display.setCursor(random(SCREEN_WIDTH - 77),random(SCREEN_HEIGHT - 6));
    display.println("hello MotMoe!");
    display.display();     
  }

  
  
//  dat[0] = analogRead(POT_0);
//  dat[1]=0;
//  dat[2]=0;
//  if (digitalRead(switch_on) == HIGH){
//    dat[1] = 1;
//  }
//  if (digitalRead(switch_off) == HIGH){
//    dat[2] = 1;
//  }
//  driver.send((uint8_t *)&dat, sizeof(dat));
//  driver.waitPacketSent();

if (digitalRead(jbutton) == LOW){
  Serial.println("boop!");
}
if (digitalRead(b1) == LOW){
  Serial.println("b1");
}
if (digitalRead(b2) == LOW){
  Serial.println("b2");
}
//delay(600);    
//
//  digitalWrite(POT_1, HIGH);
//  delay(100);    
//  Serial.print("pot1: ");
//  Serial.println(analogRead(POT_0));
////  digitalWrite(POT_1, LOW);
////  delay(600);    
////  
////  digitalWrite(POT_2, HIGH);
  delay(200);    
//  Serial.print("pot2: ");
//  Serial.println(analogRead(POT_1));
//    Serial.print("pot3: ");
//  Serial.println(analogRead(POT_2));
//    Serial.print("pot4: ");
//  Serial.println(analogRead(POT_3));
//  Serial.print("pot5: ");
//  Serial.println(analogRead(POT_4));
//    Serial.print("pot6: ");
//  Serial.println(analogRead(POT_5));
//  digitalWrite(POT_2, LOW);

}
