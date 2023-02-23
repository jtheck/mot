
/*********
 Mot.Moe command center
*********/

#define HAS_DISPLAY false
#define HAS_SERVOS false
#define HAS_IMU false
#define HAS_RADIO false
#define HAS_IR false
#define HAS_WIFI false
#define HAS_BLUETOOTH false
#define HAS_CONTROLS false

// Available Boards:
//#define ARDUINO_MICRO
#define ARDUINO_NANO_33_BLE


/*********
  Pin assignments
*********/

#ifdef ARDUINO_MICRO
  #if HAS_CONTROLS
    const uint8_t POT_0 = A2;
    const uint8_t POT_1 = A3; 
    const uint8_t POT_2 = A4;
    const uint8_t POT_3 = A5;  
    const uint8_t POT_4 = A0;
    const uint8_t POT_5 = A1;
  
    const uint8_t B_0 = 1;
    const uint8_t B_1 = 0;
    const uint8_t B_2 = 13;
  #endif
#endif


/*********
 Include library files
 Initialize components 
*********/

#if HAS_DISPLAY
  #include <Adafruit_SSD1306.h>
  #define SCREEN_WIDTH 128
  #define SCREEN_HEIGHT 64
  #define SCREEN_ADDRESS 0x3C
  Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
  uint8_t displayFPS = 1000 / 18; // 1000 / fps
  unsigned long displayTimeout = 1000 * 30; // 1000 * seconds
#endif
#define PAGE_BOOT 0
#define PAGE_DIAG 1
#define PAGE_IDLE 2
#define PAGE_MAIN 3
#define PAGE_CALIBRATE 4
#define PAGE_TRAIN 5
#define PAGE_PLAY 6
uint8_t activePage = 0;
uint8_t cursorPos = 0;



#if HAS_SERVOS
  #include <Adafruit_PWMServoDriver.h>
  #define PWM_FREQ 50 // PWM Frequency (hz)
  #define PWM_MIN 750 // minimum pulse width (ms)
  #define PWM_MAX 2250 // maximum pulse width (ms)
  Adafruit_PWMServoDriver servos = Adafruit_PWMServoDriver();
#endif


#if HAS_IMU
  #include <Adafruit_MPU6050.h>
  #include <Adafruit_Sensor.h>
  Adafruit_MPU6050 mpu;
#endif


#if HAS_RADIO
  #include <RH_ASK.h>
#endif


#if HAS_IR
  #include <IRremote.h>
#endif





/*********
 Initialize components
*********/


// SERVOS
#if HAS_SERVOS

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
  int button, buttonPrev;
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

// SENSE STATE (aspects)
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

// TIMING
struct Timing {
  unsigned long started;
  unsigned long current;
  unsigned long frameStart;
  unsigned long framePrev;
  unsigned long frameDuration;
  unsigned long displayClock;
  unsigned long idleClock;
};
struct Timing timer =
  {0, 0, 0, 0, 0, 0, 0};

 


/*********
 Setup
*********/

void setup()
{
  Serial.begin(115200);
//sendData("AT+CIOBAUD=9600\r\n", 2000, TRUE);
//  Serial.begin(9600);
//  if (!driver.init())
    Serial.println("init !");

  
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
    servos.setPWMFreq(60); // ~60hz update
  #endif

  #if HAS_CONTROLS
    pinMode(B_0, INPUT_PULLUP);
    pinMode(B_1, INPUT_PULLUP);
    pinMode(B_2, INPUT_PULLUP);
  #endif

  // IR Remote
  #if HAS_IR
    lcd.setCursor(0,0);
    lcd.print("Receiving");
    receiver.enableIRIn();
  #endif

  // Gyro
  #if HAS_IMU
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
  delay(33);
  activePage = PAGE_MAIN;
  renderPage(activePage);  

  timer.started = millis();
}




/*********
 Main
*********/

void loop()
{
  timer.frameStart = timer.current = millis();
  timer.frameDuration = timer.frameStart - timer.framePrev;
  timer.displayClock += timer.frameDuration;
  timer.idleClock += timer.frameDuration;
  timer.framePrev = timer.frameStart;
  
//  dat[0] = analogRead(POT_0);
//  driver.send((uint8_t *)&dat, sizeof(dat));
//  driver.waitPacketSent();

  #if HAS_CONTROLS
    ctrl.p0 = analogRead(POT_0);
    ctrl.p1 = analogRead(POT_1);
    ctrl.p2 = analogRead(POT_2);
    ctrl.p3 = analogRead(POT_3);
    ctrl.p4 = analogRead(POT_4);
    ctrl.p5 = analogRead(POT_5);
    
    if (digitalRead(B_0) == LOW){
      ctrl.b0 = true;
      if (activePage == PAGE_MAIN){
        if (cursorPos == 0){
          activePage = PAGE_PLAY;
          cursorPos = 0;
        }
        if (cursorPos == 1){
          activePage = PAGE_TRAIN;
          cursorPos = 0;
        }
        if (cursorPos == 2){
          activePage = PAGE_CALIBRATE;
          cursorPos = 0;
        }
        if (cursorPos == 3){
          activePage = PAGE_DIAG;
        }        
      }
      if (activePage == PAGE_CALIBRATE){
        if (cursorPos == 5){
          activePage = PAGE_MAIN;
          cursorPos = 0;
        }
      }
      if (activePage == PAGE_TRAIN){
        if (cursorPos == 5){
          activePage = PAGE_MAIN;
          cursorPos = 0;
        } 
      }
      if (activePage == PAGE_IDLE){
        activePage = PAGE_MAIN;
        cursorPos = 0;
      }

      timer.idleClock = 0;
    } else {
      ctrl.b0 = false;
    }

    
    if (digitalRead(B_1) == LOW){
      if (activePage == PAGE_MAIN){
        if (ctrl.b1 == false) {
          if (cursorPos < 3){
            cursorPos ++;  
          } else {
            cursorPos = 0;
          }
        }      
      }
      
      if (activePage == PAGE_TRAIN){
        if (ctrl.b1 == false) {
          if (cursorPos < 5){
            cursorPos ++;  
          } else {
            cursorPos = 0;
          }
        }      
      }
      
      if (activePage == PAGE_CALIBRATE){
        if (ctrl.b1 == false) {
          if (cursorPos < 5){
            cursorPos ++;  
          } else {
            cursorPos = 0;
          }
        }      
      }

      if (activePage == PAGE_PLAY){
        activePage = PAGE_MAIN;
      }

      if (activePage == PAGE_DIAG){
        activePage = PAGE_MAIN;
      }

      if (activePage == PAGE_IDLE){
        activePage = PAGE_MAIN;
        cursorPos = 0;
      }
      ctrl.b1 = true;
      timer.idleClock = 0;
    } else {
      ctrl.b1 = false;
    }

    
    if (digitalRead(B_2) == LOW){
      ctrl.b2 = true;

      activePage = PAGE_MAIN;
      timer.idleClock = 0;
    } else {
      ctrl.b2 = false;
    }
  #endif  


  #ifdef HAS_IMU
    //  if (receiver.decode()){
    ////      Serial.println(button);
    //      Serial.println(receiver.decodedIRData.decodedRawData);
    //  }
    //    sensors_event_t a, g, temp;
    //    mpu.getEvent(&a, &g, &temp);
    //    Serial.println(a.acceleration.x);
    //    
    //    state.ax = a.acceleration.x;
    //    state.ay = a.acceleration.y;
    //    state.az = a.acceleration.z;
    //    state.gx = g.gyro.x;
    //    state.gy = g.gyro.y;
    //    state.gz = g.gyro.z;
    //    state.t = int(temp.temperature);
  #endif

  
  
  

  #if HAS_DISPLAY
    if (timer.displayClock > displayFPS){
      renderPage(activePage);
      timer.displayClock = 0;
    }

    if (timer.idleClock > displayTimeout){
      activePage = PAGE_IDLE;
      timer.idleClock = 0;
    }
  #endif
}
