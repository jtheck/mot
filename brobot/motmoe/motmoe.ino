


/*
 * 
 * mot.moe brobot
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


// Servos
// 3v/5v + 5-12v
// SCL/SDA
#define PWM_FREQ 50 // PWM Frequency (hz)
#define PWM_MIN 750 // minimum pulse width (1ms?)
#define PWM_MAX 2250 // maximum pulse width (2ms?)
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
int controlA = 300; // manual servo knob
int controlB = 90;
int controlC, controlD;

const int MOTOR_COUNT = 9;
int motoActive = 0; // ux active motor

struct Moto {
    char name[16];
    int pin;
    int min;
    int zero;
    int max;
    int pos;
    short vel;
    short acc;
    bool ccw;
    bool live;
  };  


struct Moto motoArr[MOTOR_COUNT] = 
  {{"Lateral",6,15,90,165,90,0,0,true,false},
   {"Forward",5,15,90,165,90,0,0,true},
   {"Rotation",4,15,90,165,90,0,0,true},
   
   {"LFoot",15,15,90,165,90,0,0,true},
   {"LKnee",14,15,90,165,90,0,0,true},
   {"LHip",13,15,90,165,90,0,0,true},

   {"RFoot",0,15,90,165,90,0,0,true},
   {"RKnee",1,15,90,165,90,0,0,true},
   {"RHip",2,15,90,165,90,0,0,true}};



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



// Reset Arduino
void(* resetFunc) (void) = 0; // reset function




// Initialize
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
  renderPage();
  page = "DEFAULT";
  
  // Gyro
  lcd.setCursor(0,0);
  lcd.print("Orienting");
  byte gyro = mpu.begin();
  while(gyro!=0){ } // Wait for successful connection (0)
  mpu.calcOffsets();

  // Servo
  lcd.setCursor(0,0);
  lcd.print("Oscillating");
//  Serial.print(MOTO);
  pwm.begin();
//  pwm.setOscillatorFrequency(14000000); // 27MHz
  pwm.setPWMFreq(PWM_FREQ); // 
  
  for (int i=0; i<MOTOR_COUNT; i++){
    struct Moto &tMoto = motoArr[i];
    tMoto.pos = tMoto.zero;
//
Serial.println(tMoto.name);
      
    int degWidth = map(tMoto.pos, 0, 180, PWM_MIN, PWM_MAX); // degrees to pulse width
    int tick = int(float(degWidth) / 1000000 * PWM_FREQ * 4096); // tick to end pulse

    pwm.setPWM(tMoto.pin, 0, tick);
    delay(50);
  }

  

  // Remote
  lcd.setCursor(0,0);
  lcd.print("Receiving");
  receiver.enableIRIn();

  // Ready
  delay(333);
  lcd.clear();
  
}; // end setup()




// Main Loop
void loop() {


  // IR Remote
  if (receiver.decode()){
    mapButton();

    int imp = 9; // impulse (td:global)

    if (button != "REPEAT") {
      buttonPrev = button;
      Serial.println(button);
    } else {
      button = buttonPrev;
    }



    // buttons by row
    // Clear EEPROM (age)
    if (button == "POWER") EEPROM.write(agePt, 0);
    // Move Forward
    if (button == "VOL+"){
      motoArr[6].vel +=imp;
      motoArr[7].vel +=imp;
      motoArr[8].vel +=imp;
    }
    // Reset arduino
    if (button == "FUNC/STOP") resetFunc();


    // Turn left
    if (button == "|<<"){
      motoArr[0].vel +=imp;
      motoArr[1].vel +=imp;
      
    }
    // Stop
    if (button == ">||"){}
    // Turn right
    if (button == ">>|"){
      motoArr[0].vel -=imp;
      motoArr[1].vel -=imp;
    }


    // Crouch
    if (button == "DOWN") motoArr[motoActive].vel -= 10;
    // Move Backward    
    if (button == "VOL-"){

      motoArr[6].vel -=imp;
      motoArr[7].vel -=imp;
      motoArr[8].vel -=imp;
    }
    // Stand
    if (button == "UP") motoArr[motoActive].vel += 10;


    // Reset display
    if (button == "0") lcd.begin(16,2);
    // Sit
    if (button == "EQ"){
      for (int i=0; i<MOTOR_COUNT; i++){
        motoArr[i].pos = motoArr[i].zero;
      }
    }
    // Reward
    if (button == "ST/REPT"){}


    // Select page
    if (button == "1") page = "HELLO";
    if (button == "2") page = "DEFAULT";
    if (button == "3") page = "CONTROL";


    // Move select motor CCW
    if (button == "4") motoArr[motoActive].vel -= 10;
    // Select next motor
    if (button == "5"){
      motoActive += 1;
      if (motoActive >= MOTOR_COUNT) motoActive = 0;
      delay(30);
    }
    // Move select motor CW
    if (button == "6") motoArr[motoActive].vel += 10;


    // Save select motor current position as min
    if (button == "7") motoArr[motoActive].min = motoArr[motoActive].pos;
    // Select previous motor
    if (button == "8"){
      motoActive -= 1;
      if (motoActive < 0) motoActive = MOTOR_COUNT-1;
      delay(30);
    }
    // Save select motor current position as max
    if (button == "9")  motoArr[motoActive].max = motoArr[motoActive].pos;


    receiver.resume();
  }
  



  if((millis()-timer)>10){
    // Gyro
    mpu.update();
    // Servos
    motorsCycle();
  }


  if((millis()-timer)>305){ // print data every Nms
    // LCD
    renderPage();
  timer = millis();  
  }

  
  
} // end loop()
