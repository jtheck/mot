/************************************
  Mot.moe's 'Para Manipular Ejemplar' Starter Pack Example.

  Featuring: Motor Control, Sensory Feedback
  Considerations: Motor calibration, power requirements.
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

void setup() {
  // put your setup code here, to run once:


  Serial.begin(115200);
  //connect to your local wi-fi network
  WiFi.begin(ssid, password);
  //check wi-fi is connected to wi-fi network
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  WiFi.hostname(hostName);
    server.on("/", handle_connect);
  server.on("/marco", handle_marco);
}


void loop() {
  // put your main code here, to run repeatedly:


  server.handleClient();

}









void handle_connect(){
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