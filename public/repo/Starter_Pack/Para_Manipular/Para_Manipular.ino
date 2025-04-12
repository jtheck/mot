/************************************
  Mot.moe's 'Para Manipular Ejemplar' Starter Pack Example.

  Featuring: Single Servos, PCA9685 Controller, Potentiometer Controls, Button Inputs
  Considerations: Motor calibration, Power consumption.
************************************/
//MM PROJECT Manipular
//MM BOARDS [UNO, ESP32, ESP8266]
//MM FEATURES [SINGLES, PCA9685, POTENTIOMETERS, BUTTONS]
//MM
//MM UNO []
//MM ESP32 [SINGLES, PCA9685, POTENTIOMETERS, BUTTONS]
//MM ESP8266 [SINGLES, PCA9685, POTENTIOMETERS, BUTTONS]
//MM
// #define MM_IS_ESP32
// #define MM_IS_ESP8266
//MM
// #define MM_HAS_SINGLES
// #define MM_HAS_PCA9685
//MM
#ifdef MM_IS_ESP32
////////////////////////////////////
// ESP32 Pin Out
// Serial Clock (SCL) - D22- GPIO22
// Serial Data (SDA) - D21 - GPIO21
////////////////////////////////////
#ifdef MM_HAS_SINGLES
#include <ESP32Servo.h> 
#endif // MM_HAS_SINGLES
#ifdef MM_HAS_PCA9685
#include <Wire.h> // I2C serial bus
#include <Adafruit_PWMServoDriver.h> // Servos 
#endif // MM_HAS_PCA9685
#endif // MM_IS_ESP32
//MM
#ifdef MM_IS_ESP8266
////////////////////////////////////
// ESP8266 Pin-Out
// Serial Clock (SCL) - D1 - GPIO5
// Serial Data (SDA) - D2 - GPIO4
////////////////////////////////////
#endif // MM_IS_ESP8266


// SERVOS
#define SERVOMIN 150
#define SERVOMAX 600
Adafruit_PWMServoDriver servoMotors = Adafruit_PWMServoDriver();
uint8_t numberOfServos = 16;
int servoPos = 222;

// POT
struct Pot {
  int min;
  int max;
  int prev;
  int actual;
  float norm;
};

struct Pot p1 = {1024, 0, 0, 100, 100.0};





void setup() {
  // put your setup code here, to run once:


  Serial.begin(115200);
  

    // SERVOS
  servoMotors.begin();
  servoMotors.setPWMFreq(60);
  // KNOB
  pinMode(A0, INPUT); 
  pinMode(LED_BUILTIN, OUTPUT);
p1.prev = analogRead(A0);
p1.actual = analogRead(A0);

    Serial.print("ready");

}


void loop() {
  // put your main code here, to run repeatedly:





  //int potencia = analogRead(A0);
  if (abs(p1.actual - p1.prev) > 4){
    p1.actual = analogRead(A0);
    if (p1.min > p1.actual)
      p1.min = p1.actual;
    if (p1.max < p1.actual)
      p1.max = p1.actual;
     
    p1.norm = (float) (p1.actual-p1.min) / (p1.max-p1.min);

    servoPos = p1.norm*(SERVOMAX - SERVOMIN) + SERVOMIN;

  }

      p1.actual = 1023 - p1.actual;
  analogWrite(LED_BUILTIN, p1.actual);

  for (int servo = 0; servo < numberOfServos; servo++){
    servoMotors.setPWM(servo, 0, servoPos);
    Serial.println(servoPos);
  }
}
