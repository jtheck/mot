
/*********
 Mot.Moe command center
*********/

#define HAS_DISPLAY true
#define HAS_SERVOS false
#define HAS_GYRO true
#define HAS_RADIO false
#define HAS_IR false
#define HAS_CONTROLS true



/*********
 Include library files
  +Pin assignments
*********/

//#include <SPI.h>
//#include <Wire.h> // I2C

#if HAS_DISPLAY
  #include <Adafruit_SSD1306.h> // OLED Screen
#endif

#if HAS_SERVOS
  #include <Adafruit_PWMServoDriver.h> // Servos
#endif

#if HAS_GYRO
  #include <Adafruit_MPU6050.h> // Gyro
  #include <Adafruit_Sensor.h>
  #include <Wire.h>
#endif

#if HAS_RADIO
  #include <RH_ASK.h> // Transmit radio
#endif

#if HAS_IR
  #include <IRremote.h> // Infrared remote
#endif

#if HAS_CONTROLS
  const uint8_t POT_0 = A0;
  const uint8_t POT_1 = A1; 
  const uint8_t POT_2 = A2;
  const uint8_t POT_3 = A3; 
  const uint8_t POT_4 = A4;
  const uint8_t POT_5 = A5;
#endif



/*********
 Initialize components
*********/

// DISPLAY
#if HAS_DISPLAY
  bool displayEnabled = true;
  #define SCREEN_WIDTH 128
  #define SCREEN_HEIGHT 64
  #define SCREEN_ADDRESS 0x3C
  Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
#endif
String activePage = "boot";

// SERVOS
#if HAS_SERVOS
  #define PWM_FREQ 50 // PWM Frequency (hz)
  #define PWM_MIN 750 // minimum pulse width (1ms?)
  #define PWM_MAX 2250 // maximum pulse width (2ms?)
  Adafruit_PWMServoDriver servos = Adafruit_PWMServoDriver();
#endif

// GYRO
#if HAS_GYRO
  // 3v/5v
  // SCL/SDA
  Adafruit_MPU6050 mpu;
#endif

// RADIO
#if HAS_RADIO
  // ESP8266MOD
  const int TX_PIN = 12;//d6
  const int RX_PIN = 14;//d5
  RH_ASK driver(2000, RX_PIN, TX_PIN, 0);
#endif

// IR REMOTE
#if HAS_IR
  IRrecv receiver(4);
  String button, buttonPrev;
#endif

// CONTROL (inputs)
struct Control {
  int p0;
  int p1;
  int p2;
  int p3;
  int p4;
  int p5;
  bool b0;
  bool b1;
  bool b2;
};
struct Control ctrl =
  {0,0,0,0,0,0, false, false, false};

// STATE (aspects)
struct State {
  float ax;
  float ay;
  float az;
  float gx;
  float gy;
  float gz;
  int t;
};
struct State state =
  {1,1,1,1,1,1,1};





 
//const int switch_on = 9, switch_off = 10;//sd2, sd3
//int dat[3];

const int jbutton = 13;
const int b1 = 0;
const int b2 = 1;



/*********
 Setup
*********/

void setup()
{
  Serial.begin(115200);
//sendData("AT+CIOBAUD=9600\r\n", 2000, TRUE);
//  Serial.begin(9600);
//  if (!driver.init())
//    Serial.println("init !");

  
  // DISPLAY
  #if HAS_DISPLAY
    display.setRotation(2); // 180deg flip
    display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
    display.setTextSize(1);
    display.setTextColor(WHITE);
    renderPage(activePage);
    delay(1500);
  #endif

  // SERVOS
  #if HAS_SERVOS
    servos.begin();
    servos.setPWMFreq(60);
  #endif
//    display.setCursor(1,2);
//    display.print("hello mot.moe!");
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
  // IR Remote
  #if HAS_IR
    lcd.setCursor(0,0);
    lcd.print("Receiving");
    receiver.enableIRIn();
  #endif

  // Gyro
  #if HAS_GYRO
  
//    byte gyro = mpu.begin();
  if (!mpu.begin()){
    Serial.println("fail");
    while(1){
      delay(10);
      } // Wait for successful connection (0)

  }
  Serial.println("found!");
    

    
    mpu.setAccelerometerRange(MPU6050_RANGE_8_G); // 2 < 4 < 8 < 16 +-G
    mpu.setGyroRange(MPU6050_RANGE_500_DEG); // 250 < 500 < 1000 < 2000 deg/s
    mpu.setFilterBandwidth(MPU6050_BAND_5_HZ); // 5, 10, 21, 44, 94, 184, 260 HZ 
    renderPage(activePage);
  Serial.println(mpu.getAccelerometerRange());
  Serial.println(mpu.getGyroRange());
      Serial.println(mpu.getFilterBandwidth());

  #endif
  

      

//  Serial.println("Setup complete!");
//  delay(333);

}




/*********
 Main
*********/

void loop()
{

  
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
  ctrl.b0 = true;
    activePage = "idle";

} else {
  ctrl.b0 = false;
}

if (digitalRead(b1) == LOW){
  ctrl.b1 = true;
  activePage = "idle";
} else {
  ctrl.b1 = false;
}
if (digitalRead(b2) == LOW){
  ctrl.b2 = true;
  activePage = "diag";
} else {
  ctrl.b2 = false;
}
//delay(600);    

// IR Remote
//  if (receiver.decode()){
////      Serial.println(button);
//      Serial.println(receiver.decodedIRData.decodedRawData);
//  }

  #if HAS_GYRO
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);
    Serial.println(a.acceleration.x);
    
    state.ax = a.acceleration.x;
    state.ay = a.acceleration.y;
    state.az = a.acceleration.z;
    state.gx = g.gyro.x;
    state.gy = g.gyro.y;
    state.gz = g.gyro.z;
    state.t = int(temp.temperature);
  #endif
//
//  digitalWrite(POT_1, HIGH);
//  delay(100);    
//  Serial.print("pot1: ");
//  Serial.println(analogRead(POT_0));
////  digitalWrite(POT_1, LOW);
////  delay(600);    
////  
////  digitalWrite(POT_2, HIGH);
  delay(80);    
  ctrl.p0 = analogRead(POT_0);
  ctrl.p1 = analogRead(POT_1);
  ctrl.p2 = analogRead(POT_2);
  ctrl.p3 = analogRead(POT_3);
  ctrl.p4 = analogRead(POT_4);
  ctrl.p5 = analogRead(POT_5);
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
  #if HAS_DISPLAY
    renderPage(activePage);  
  #endif
}
