/*********

#include <Wire.h> // I2C serial b
 momo reboot
*********/
#include <Adafruit_SSD1306.h> // OLED Screen
#include <ESP8266WiFi.h> // WiFi
#include <ESP8266WebServer.h> // WiFi web server
#include <ArduinoJson.h> // JSON Parsing
#include <RH_ASK.h> // RX
#include <Adafruit_PWMServoDriver.h> // Servos


// SERVOS
// 4.8v: 0.12s/60deg
#define SERVOMIN 150
#define SERVOMAX 600
Adafruit_PWMServoDriver myServo = Adafruit_PWMServoDriver();
uint8_t servonum = 0;
uint8_t numberOfServos = 6;
int servoPos = 222;


// SCREEN
#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
int screenPage = 0;


// WIFI
const char* ssid     = "Dark Throw";
const char* password = "hellomotmoe";
ESP8266WebServer server(80);


// RX
RH_ASK rx(2000,14,12,0);



// POT
struct Pot {
  int min;
  int max;
  int prev;
  int actual;
  float norm;
};
struct Pot p1 = {1024, 0, 0, 100, 100.0};


// BUTTONS
const int b1 = 15;
const int b2 = 13;



// TIMING
unsigned long timer = 0;





/*********
 SETUP
*********/
void setup() {
  // SERIAL MONITOR
  Serial.begin(115200);
  Serial.println(" ");
  Serial.print("begin");



  // BUTTONS
  pinMode(b1, INPUT);
  pinMode(b2, INPUT);


  // I2C
//  Wire.begin();


  // WIFI
  WiFi.begin(ssid, password);
  Serial.print("connecting");
  Serial.print(millis());
  for(int i=0;i<300;i++){
    
  }
  Serial.print(millis());
//  while(WiFi.status() != WL_CONNECTED){
//    delay(500);
//    Serial.print(".");
//  }
  Serial.print(" ");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
  server.on("/", h_index);
  server.on("/boop", h_boop);
  server.begin();
  Serial.println("listening");

  
  // SERVOS
  myServo.begin();
  myServo.setPWMFreq(60);


  // SCREEN
  display.setRotation(2); // 180deg flip
  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 56);
  display.println("Hello Mot.Moe!");
  display.display(); 


  // RX
  rx.init();

  
  // KNOB
  pinMode(A0, INPUT); 
  pinMode(LED_BUILTIN, OUTPUT);
  p1.prev = analogRead(A0);
  p1.actual = analogRead(A0);
  p1.norm = 200;


  
  Serial.println("Setup complete!");
  delay(1000);
}



/*********
 MAIN
*********/
void loop() {

  // WIFI
  server.handleClient();



  // RX
  int dat[3]={0}; // 0-pot 1-b1 2-b2
  uint8_t buflen = sizeof(dat);
  if (rx.recv((uint8_t*)dat, &buflen))
  {
    for (int i=0; i<3; i++){
      Serial.println(dat[i]);
    }
    
    if (dat[0]){
            
 
     p1.actual = dat[0];//analogRead(A0);
    }
    
    //    if (dat[1] == 1 || dat[2] == 1) {
    //      digitalWrite(out, HIGH);
    //    } else {
    //      digitalWrite(out, LOW);
    //    }
  }
  
  p1.actual = analogRead(A0);
  if (abs(p1.actual - p1.prev) > 4){
//          p1.actual = analogRead(A0);
    if (p1.min > p1.actual)
      p1.min = p1.actual;
    if (p1.max < p1.actual)
      p1.max = p1.actual;
       
    p1.norm = (float) (p1.actual-p1.min) / (p1.max-p1.min);
    p1.prev = p1.actual;

    servoPos = p1.norm*(SERVOMAX - SERVOMIN) + SERVOMIN;
  }


  // BUTTONS
  if (digitalRead(b1) == HIGH){
//    Serial.println("B1!");
    screenPage = 0;
  }
  if (digitalRead(b2) == HIGH){
//    Serial.println("B2!");
    screenPage = 1;
  }

  
//  p1.actual = 1023 - p1.actual;
//  p1.prev = p1.actual;
////  analogWrite(LED_BUILTIN, p1.actual);


  for (int servo = 0; servo < numberOfServos; servo++){
    myServo.setPWM(servo, 0, servoPos);
  }


  // TIMING
  if((millis()-timer)>67){ // print data every Nms
    // LCD
    renderPage(screenPage);
    timer = millis();  
  }
}
