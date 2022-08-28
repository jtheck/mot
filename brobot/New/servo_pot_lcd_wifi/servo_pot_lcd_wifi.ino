/*********
 momo reboot
*********/


#include <Wire.h> // I2C serial bus
#include <Adafruit_PWMServoDriver.h> // Servos 
#include <Adafruit_SSD1306.h> // OLED Screen
#include <ESP8266WiFi.h>  // WiFi
#include <ESP8266WebServer.h> // WiFi web server
#include <ArduinoJson.h>  // JSON Parsing


// SERVOS
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

// WIFI
const char* ssid     = "Dark Throw";
const char* password = "hellomotmoe";
ESP8266WebServer server(80);


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
  // SERIAL MONITOR
  Serial.begin(115200);
  Wire.begin();
  
  Serial.println(" ");
  Serial.print("begin");

  // WIFI
  WiFi.begin(ssid, password);
  Serial.print("connecting");
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
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
//  delay(10);

  // SCREEN
  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
  display.clearDisplay();
  //Display Text
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("hello MoMo");
  display.display(); 

  // KNOB
  pinMode(A0, INPUT); 
  pinMode(LED_BUILTIN, OUTPUT);
p1.prev = analogRead(A0);
p1.actual = analogRead(A0);

//p1.norm = 200;
  
  Serial.print("setup complete");
}

void loop() {

  // WIFI
  server.handleClient();


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
    
//  Serial.println(" ");
//  Serial.println(p1.actual);
//  Serial.println(p1.norm);
  
  display.clearDisplay();
  display.setCursor(40, 10);
  display.println(p1.actual);
  display.setCursor(40, 30);
  display.println(p1.norm);
  display.display(); 
  
  p1.actual = 1023 - p1.actual;
  analogWrite(LED_BUILTIN, p1.actual);


  for (int servo = 0; servo < numberOfServos; servo++){
    myServo.setPWM(servo, 0, servoPos);
  }
}





void h_index(){
  server.send(200, "text/plain", "HELLO MOMO");
  Serial.println("served /");
}
void h_boop(){
  server.enableCORS(true);
  server.send(200, "application/json", "{\"a\":\"bc\"}");
  Serial.println("served /boop");

  StaticJsonDocument<200> doc;
  deserializeJson(doc, server.arg("plain"));
  JsonObject obj = doc.as<JsonObject>();
  const char* boop = doc["x"];
  Serial.println(boop);
  
}
