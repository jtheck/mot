
/*
 * 
 * mot.moe brobot
 * 
 */
 
#include <Wire.h> // I2C serial bus
#include <LiquidCrystal_SR.h> // LCD
#include <MPU6050_light.h> // Gyro
//#include <Adafruit_PWMServoDriver.h> // Servos
#include <IRremote.h> // Infrared remote
#include <EEPROM.h> // Storage





// LCD
// 5v
// Pin 3 - SCK
// Pin 5 - Clock/SCL
// Pin 6 - Data Enable/ SER
LiquidCrystal_SR lcd(6, 5, 3);
String page = "HELLO";


// Gyro
// 3v/5v
// SCL/SDA
MPU6050 mpu(Wire);
struct Vec{
    float x, y, z;
  };
struct Vec torsoPlane{0,0,0};
struct Vec hipPlane{0,0,0};




// Remote
// 3.3v
// Pin 4
IRrecv receiver(4);
String button, buttonPrev;


// Timing
unsigned long timer = 0;


// Memory
int agePt = 0;
int age;


// Misc
void(* resetFunc) (void) = 0; // reset function


// Init
void setup() {

  // Memory
  age = EEPROM.read(agePt);
  age += 1;
  EEPROM.write(agePt, age);
  
  // Log
  Serial.begin(9600);
  Wire.begin();
  Serial.println(" ");
  Serial.print("begin age ");
  Serial.print(age);
  Serial.print("!");
  Serial.println("");  
  Serial.println(motoArr[0].name);
  
  // LCD
  lcd.begin(16,2);
  renderPage();
  page = "DEFAULT";
  
  // Gyro
  lcd.setCursor(0,0);
  lcd.print("Orienting");
  byte gyro = mpu.begin();
  while(gyro!=0){ } // Wait for successful connection (0)
  mpu.calcOffsets();

  // Remote
  lcd.setCursor(0,0);
  lcd.print("Receiving");
  receiver.enableIRIn();

  // Ready
  delay(333);
  lcd.clear();
  
}




// Run
void loop() {

  // Remote
  if (receiver.decode()){
    mapButton();
    if (button == "FUNC/STOP") resetFunc(); // reset arduino
    if (button == "POWER") EEPROM.write(agePt, 0); // clear EEPROM (age)
    if (button != "REPEAT") {
      buttonPrev = button;
      Serial.println(button);
    } else {
      button = buttonPrev;
    }


    if (button == "0") lcd.begin(16,2); // reset lcd
    if (button == "1") page = "HELLO";
    if (button == "2") page = "DEFAULT";
    if (button == "3") page = "CONTROL";

    if (button == "5"){
      motoActive += 1;
      if (motoActive >= MOTO_CT) motoActive = 0;
    }

    int imp = 5;
    if (button == ">>|"){
      motoArr[2].vel -=imp;
      motoArr[0].vel -=imp;
    }
    if (button == "|<<"){
      motoArr[2].vel +=imp;
      motoArr[0].vel +=imp;
    }
    if (button == "VOL+"){
      motoArr[0].vel -=imp;
      motoArr[2].vel +=imp;
    }
    if (button == "VOL-"){
      motoArr[0].vel +=imp;
      motoArr[2].vel -=imp;
    }

    if (button == "UP") motoArr[motoActive].vel += 10;
    if (button == "DOWN") motoArr[motoActive].vel -= 10;
    if (button == "EQ"){
      
      for (int i=0; i<MOTO_CT; i++){
        motoArr[i].pos = motoArr[i].zero;
      }
    }        
    
    receiver.resume();
  }
  


  //if((millis()-timer)>10){ // print data every Nms
    // Gyro
    mpu.update();
  
  //}

  if((millis()-timer)>100){ // print data every Nms

   
    // LCD
    renderPage();
    
    timer = millis();  
  }

  
//  delay(100);

}







//#include <Stepper.h> // Steppers
//// Stepper
//// 5v
//// Pin 8 - In1
//// Pin 9 - In2
//// Pin 10 - In3
//// Pin 11 - In4
//const float SPR = 32; // Steps per revolution
//const float SPRG = SPR * 64; // steps per geared output rotation (gear ratio 64)
////Stepper stepper(SPR, 8, 10, 9, 11);
//Stepper stepper(SPR, 9, 11, 10, 8);
//int steps = 0;
//// Stepper
//stepper.setSpeed(750);
//// Stepper
////    stepper.step(steps);
//if (button == "8"){
//  digitalWrite(8,LOW);
//  digitalWrite(9,LOW);
//  digitalWrite(10,LOW);
//  digitalWrite(11,LOW); 
//}
//if (button == "9") stepper.step(SPRG*.125);// cw 1/8
//if (button == "7") stepper.step(-SPRG*.125);// ccw 1/8
