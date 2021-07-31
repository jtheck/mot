
/*
 * 
 * Mot.Moe brobot
 * 
 */
 
#include <Wire.h> // I2C serial bus
#include <LiquidCrystal_SR.h> // LCD
#include <MPU6050_light.h> // Gyro
#include <Adafruit_PWMServoDriver.h> // Servos
#include <IRremote.h> // Infrared remote
#include <EEPROM.h> // Storage



// LCD
// 5v
// Pin 3 - SCK
// Pin 5 - Clock/SCL
// Pin 6 - Data Enable/ SER
LiquidCrystal_SR lcd(6, 5, 3);

// Gyro
// 3v/5v
// SCL/SDA
MPU6050 mpu(Wire);

// Servos
// 3v/5v + 5-12v
// SCL/SDA
#define PWM_FREQ 50 // PWM Frequency (hz)
#define PWM_MIN 650 // minimum pulse width (1ms?)
#define PWM_MAX 2350 // maximum pulse width (2ms?)
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
int controlA = A0; // manual servo knob
int motorA = 15;
int controlB = 300;
int motorB = 7;

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
  
  // LCD
  lcd.begin(16,2);
  lcd.setCursor(13,0);
  lcd.print(age);
  lcd.setCursor(1,2);
  lcd.print("hello mot.moe");

  // Gyro
  byte gyro = mpu.begin();
  while(gyro!=0){ } // Wait for successful connection (0)
  mpu.calcOffsets();

  // Servo
  pwm.begin();
  pwm.setOscillatorFrequency(27000000); // 27MHz
  pwm.setPWMFreq(PWM_FREQ); // 

  // Remote
  receiver.enableIRIn();

  // Ready
  delay(333);
  lcd.clear();
  
}



void loop() {

  // Remote
  if (receiver.decode()){
    mapButton();
    if (button == "FUNC/STOP") resetFunc(); // reset arduino
    if (button == "POWER") EEPROM.write(agePt, 0); // clear EEPROM (age)
    if (button != "repeat") {
      buttonPrev = button;
//      lcd.setCursor(0,1);
//      lcd.print("                ");
//      lcd.setCursor(1,1);
//      lcd.print(button);
      Serial.println(button);
    } else {
      button = buttonPrev;
    }

    if (button == "UP") controlB += 25;
    if (button == "DOWN") controlB -= 25;
    if (button == "EQ") controlB = 300;
    
    receiver.resume();
  }
  

  // Gyro
  mpu.update();

  if((millis()-timer)>100){ // print data every Nms
  
    // LCD
    lcd.clear();
    //lcd.setCursor(0,0);
    //lcd.print("                ");
    lcd.setCursor(0,0);
    lcd.print(int(mpu.getAngleX()));
    lcd.print("x");
    lcd.setCursor(5,0);
    lcd.print(int(mpu.getAngleY()));
    lcd.print("y");
    lcd.setCursor(10,0);
    lcd.print(int(mpu.getAngleZ()));
    lcd.print("z");


    
    
  // Servo
//  pwm.setPWM(motorA, 0, 1000);
  int potVal, pwid, wid;
  // Read values from potentiometer
  potVal = analogRead(controlA);
  pwid = map(potVal, 0, 1023, PWM_MIN, PWM_MAX);
  wid = int(float(pwid) / 1000000 * PWM_FREQ * 4096);
  pwm.setPWM(motorA, 0, wid);
  lcd.setCursor(10,1);
  lcd.print(wid);

  lcd.setCursor(1,1);
  lcd.print(controlB);
  
    
    timer = millis();  
  }

  pwm.setPWM(motorB, 0, controlB);
  
  
  
//  delay(100);

}




void moveMotor(int controlIn, int motorOut)
{
  int pulse_wide, pulse_width, potVal;
  
  // Read values from potentiometer
  potVal = analogRead(controlIn);

  lcd.setCursor(10,1);
  lcd.print(potVal);
  
  // Convert to pulse width
  pulse_wide = map(potVal, 0, 1023, PWM_MIN, PWM_MAX);
  pulse_width = int(float(pulse_wide) / 1000000 * PWM_FREQ * 4096);
  
  //Control Motor
  pwm.setPWM(motorOut, 0, pulse_width);

}



String mapButton(){
  switch (receiver.decodedIRData.decodedRawData) {
    case 0xBA45FF00:
      button = "POWER";
      break;
    case 0xB946FF00:
      button = "VOL+";
      break;
    case 0xB847FF00:
      button = "FUNC/STOP";
      break;
    case 0xBB44FF00:
      button = "|<<";
      break;
    case 0xBF40FF00:
      button = ">||";
      break ;
    case 0xBC43FF00:
      button = ">>|";
      break ;
    case 0xF807FF00:
      button = "DOWN";
      break ;
    case 0xEA15FF00:
      button = "VOL-";
      break ;
    case 0xF609FF00:
      button = "UP";
      break ;
    case 0xE916FF00:
      button = "0";
      break ;
    case 0xE619FF00:
      button = "EQ";
      break ;
    case 0xF20DFF00:
      button = "ST/REPT";
      break ;
    case 0xF30CFF00:
      button = "1";
      break ;
    case 0xE718FF00:
      button = "2";
      break ;
    case 0xA15EFF00:
      button = "3";
      break ;
    case 0xF708FF00:
      button = "4";
      break ;
    case 0xE31CFF00:
      button = "5";
      break ;
    case 0xA55AFF00:
      button = "6";
      break ;
    case 0xBD42FF00:
      button = "7";
      break ;
    case 0xAD52FF00:
      button = "8";
      break ;
    case 0xB54AFF00:
      button = "9";
      break ;
    default:
      button = "repeat";
      break;
  }
  
  return button;
}
