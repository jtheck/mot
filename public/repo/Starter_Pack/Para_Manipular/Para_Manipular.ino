/************************************
  Mot.moe's 'Para Manipular Ejemplar' Starter Pack Example.

  Featuring: Motor Control, Sensory Feedback
  Considerations: Motor calibration, Power consumption.
************************************/
//MM PROJECT Manipular
//MM BOARDS [UNO, ESP8266]
//MM FEATURES [moto]
//MM UNO [moto]
//MM
// #define MM_IS_UNO
// #define MM_IS_ESP8266
//MM
// #define MM_HAS_MOTO
//MM

#include <Wire.h> // I2C serial bus
#include <Adafruit_PWMServoDriver.h> // Servos 
// #include <Adafruit_SSD1306.h> // OLED Screen
#include <ESP8266WiFi.h>  // WiFi
#include <ESP8266WebServer.h> // WiFi web server
// #include <ArduinoJson.h>  // JSON Parsing

// WARNING: Protect your credentials!
const char* hostName = "momo";
const char* ssid = "RB-NET-0G";  // Network SSID
const char* password = "12345678";  // Enter Password here!
ESP8266WebServer server(80);



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
  //connect to your local wi-fi network
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  WiFi.hostname(hostName);
  Serial.print("Got IP: ");  Serial.println(WiFi.localIP());
  server.onNotFound(handle_404);
  server.on("/", handle_connect);
  server.on("/marco", handle_marco);
  server.begin();
  

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

      p1.actual = 1023 - p1.actual;
  analogWrite(LED_BUILTIN, p1.actual);

  for (int servo = 0; servo < numberOfServos; servo++){
    servoMotors.setPWM(servo, 0, servoPos);
    Serial.println(servoPos);
  }
}











void handle_404(){
  server.send(404, "text/plain", "Not found");
}

void handle_connect(){
//  server.send(200, "text/plain", hostName); 
  server.send(200, "text/html", SendHTML(true,true)); 
  Serial.println("Served /");
}
void handle_marco()
{
  server.sendHeader("Access-Control-Allow-Origin", "*"); // Allow CORS
  // server.send(200, "text/html", SendHTML(true,true)); 
  // server.send(200, "application/json", "{\"a\":\"bc\"}");
  server.send(200, "text/plain", hostName); 
  Serial.println("served /marco");
}
void h_poll(){
  server.send(200, "text/plain", String(millis()));
  // server.send(200, "application/json", {millis());
  Serial.println("served /poll");
}





String SendHTML(uint8_t led1stat,uint8_t led2stat){
String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<title>WiFi Control</title>\n";
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<h1>ESP8266 Web Server</h1>\n";
  ptr +="<h3>Using Access Point(AP) Mode</h3>\n";

  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;


}