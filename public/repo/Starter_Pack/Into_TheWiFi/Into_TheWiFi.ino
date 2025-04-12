/************************************
  Mot.moe's 'Into The Wifi' Starter Pack Example.

  Featuring: Standalone Access Point, Portable WiFi Login, Static WiFi Credentials
  Considerations: Network configuration for wireless feedback and monitoring.
************************************/
//MM PROJECT Into the Wifi
//MM BOARDS [ESP32, ESP8266, ESP01]
//MM FEATURES [ACCESS_POINT, STATIC_WIFI, PORTABLE_WIFI, BLUETOOTH]
//MM ESP32 [ACCESS_POINT, STATIC_WIFI, PORTABLE_WIFI, BLUETOOTH]
//MM ESP8266 [ACCESS_POINT, STATIC_WIFI]
//MM ESP01 [STATIC_WIFI]
//MM
// #define MM_IS_ESP32
// #define MM_IS_ESP8266
// #define MM_IS_ESP01
//MM
// #define MM_HAS_ACCESS_POINT
// #define MM_HAS_STATIC_WIFI
// #define MM_HAS_PORTABLE_WIFI
// #define MM_HAS_BLUETOOTH
//MM
#ifdef MM_IS_ESP8266
////////////////////////////////////
// ESP8266 & ESP01
////////////////////////////////////

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#ifdef MM_HAS_ACCESS_POINT
// Access Point Credentials & IP
const char* hostName = "Hello Wifi!";
const char* ssid = "RB-NET-ESP8266-AP"; // Access point SSID
const char* password = "12345678"; // WARN: Eight character minimum!
IPAddress local_ip(192,168,2,1);
IPAddress gateway(192,168,2,1);
IPAddress subnet(255,255,255,0);
ESP8266WebServer server(80);
#endif // MM_HAS_ACCESS_POINT
//MM
#ifdef MM_HAS_STATIC_WIFI
// WiFi Credentials
// WARNING: Protect your credentials!
const char* hostName = "Hello Wifi!";
const char* ssid = "RB-NET-0G";  // Network SSID
const char* password = "12345678";  // Enter Password here!
ESP8266WebServer server(80);
#endif // MM_HAS_STATIC_WIFI
#endif // MM_IS_ESP8266
//MM
#ifdef MM_IS_ESP32
////////////////////////////////////
// ESP32
////////////////////////////////////
#include <WiFi.h>
#include <WebServer.h>
// #include <ESPAsyncWebServer.h>
#ifdef MM_HAS_ACCESS_POINT
// Access Point Credentials & IP
const char* hostName = "Hello Wifi!";
const char* ssid = "RB-NET-ESP32-AP"; // Access point SSID
const char* password = "12345678"; // WARN: Eight character minimum!
IPAddress local_ip(192,168,2,1);
IPAddress gateway(192,168,2,1);
IPAddress subnet(255,255,255,0);
WebServer server(80);
#endif // MM_HAS_ACCESS_POINT
//MM
#ifdef MM_HAS_STATIC_WIFI
// WiFi Credentials
// WARNING: Protect your credentials!
const char* hostName = "Hello Wifi!";
const char* ssid     = "RB-NET-0G";
const char* password = "12345678";
WebServer server(80);
#endif // MM_HAS_STATIC_WIFI
//MM
#ifdef MM_HAS_PORTABLE_WIFI
#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager
#endif // MM_HAS_PORTABLE_WIFI
#endif // MM_IS_ESP32
//MM


void setup()
{
  // put your setup code here, to run once:


  Serial.begin(115200);

#ifdef MM_HAS_ACCESS_POINT
  WiFi.softAPConfig(local_ip, gateway, subnet);
  WiFi.softAP(ssid, password);
  delay(100);

  server.onNotFound(handle_404);
  server.on("/", handle_connect);
  server.on("/marco", handle_marco);
  server.on("/boop", h_boop);
  server.on("/poll", h_poll);
  server.on("/log", h_log);

  server.begin();
  
  Serial.println(WiFi.localIP());
  Serial.println(WiFi.softAPIP());
#endif // MM_HAS_ACCESS_POINT
//MM
#ifdef MM_HAS_PORTABLE_WIFI
  // WiFi.mode(WIFI_STA); // explicitly set mode, esp defaults to STA+AP
  // it is a good practice to make sure your code sets wifi mode how you want it.
  // WiFiManager, Local intialization. Once its business is done, there is no need to keep it around
  WiFiManager wm;
  // reset settings - wipe stored credentials for testing
  // these are stored by the esp library
  // wm.resetSettings();
  // Automatically connect using saved credentials,
  // if connection fails, it starts an access point with the specified name ( "AutoConnectAP"),
  // if empty will auto generate SSID, if password is blank it will be anonymous AP (wm.autoConnect())
  // then goes into a blocking loop awaiting configuration and will return success result
  bool res;
  // res = wm.autoConnect(); // auto generated AP name from chipid
  // res = wm.autoConnect("AutoConnectAP"); // anonymous ap
  res = wm.autoConnect("ROBO Uplink WiFi", "password"); // password protected ap
  if (!res)
  {
    Serial.println("Failed to connect");
    // ESP.restart();
  }
  else
  {
    // if you get here you have connected to the WiFi
    Serial.println("connected...yeey :)");
  }
#endif // MM_HAS_PORTABLE_WIFI
//MM
#ifdef MM_HAS_STATIC_WIFI
#ifdef MM_IS_ESP32

  Serial.println("Connecting to ");
  Serial.println(ssid);
  //connect to your local wi-fi network
  WiFi.begin(ssid, password);
  //check wi-fi is connected to wi-fi network
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  WiFi.hostname(hostName);
  Serial.println("");
  Serial.println("WiFi connected..!");
  Serial.print("Got IP: ");  Serial.println(WiFi.localIP());

  server.onNotFound(handle_404);
  server.on("/", handle_connect);
  server.on("/marco", handle_marco);
  server.on("/boop", h_boop);
  server.on("/poll", h_poll);
  server.on("/log", h_log);

  server.begin();
  Serial.println("listening");


  // server.on("/", [](AsyncWebServerRequest *request){
  //   request->send(200, "text/plain", "HIHIHIHHOHOHO");
  // });

#endif // MM_IS_ESP32
//MM
#ifdef MM_IS_ESP8266
  Serial.println("Connecting to ");
  Serial.println(ssid);
  //connect to your local wi-fi network
  WiFi.begin(ssid, password);
  //check wi-fi is connected to wi-fi network
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  WiFi.hostname(hostName);
  Serial.println("");
  Serial.println("WiFi connected..!");
  Serial.print("Got IP: ");  Serial.println(WiFi.localIP());

  server.onNotFound(handle_404);
  server.on("/", handle_connect);
  server.on("/marco", handle_marco);
  server.on("/boop", h_boop);
  server.on("/poll", h_poll);
  server.on("/log", h_log);

  server.begin();
  Serial.println("listening");

#endif // MM_IS_ESP8266
#endif // MM_HAS_STATIC_WIFI
} // END setup()


void loop()
{
  // put your main code here, to run repeatedly:

server.handleClient();

  // Use WiFiClient class to create TCP connections
  WiFiClientSecure client;
  const int httpPort = 443; // 80 is for HTTP / 443 is for HTTPS!
  
  client.setInsecure(); // this is the magical line that makes everything work
  

  // up and at them
#ifdef MM_HAS_STATIC_WIFI
server.handleClient();
#endif // MM_HAS_STATIC_WIFI
//MM
#ifdef MM_HAS_PORTABLE_WIFI
server.handleClient();
  // get put
  if (0)
   true;

#endif // MM_HAS_PORTABLE_WIFI

} // END loop()










void handle_404(){
  server.send(404, "text/plain", "Not found");
}

void handle_connect(){
  server.send(200, "text/html", SendHTML(true,true)); 
  Serial.println("Served /");
}

void h_poll(){
  server.send(200, "text/plain", String(millis()));
  // server.send(200, "application/json", {millis());
  Serial.println("served /poll");
}

void h_log(){
  server.sendHeader("Access-Control-Allow-Origin", "*"); // Allow CORS
  server.send(200, "application/json", "{\"recent\":[\"bc\"]}");
  Serial.println("served /log");
}

void h_boop()
{
  server.send(200, "application/json", "{\"a\":\"bc\"}");
  Serial.println("served /boop");
  // StaticJsonDocument<200> doc;
  // deserializeJson(doc, server.arg("plain"));
  // JsonObject obj = doc.as<JsonObject>();
  const char *boop = "IT IS WHAT IT IS"; // doc["x"];
  Serial.println(boop);
}

void handle_marco()
{
  server.sendHeader("Access-Control-Allow-Origin", "*"); // Allow CORS
  // server.send(200, "text/html", SendHTML(true,true)); 
  // server.send(200, "application/json", "{\"a\":\"bc\"}");
  server.send(200, "text/plain", hostName); 
  Serial.println("served /marco");
}



String SendHTML(uint8_t led1stat,uint8_t led2stat){
String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<title>WiFi Control</title>\n";
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
  ptr +=".button {display: block;width: 80px;background-color: #1abc9c;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
  ptr +=".button-on {background-color: #1abc9c;}\n";
  ptr +=".button-on:active {background-color: #16a085;}\n";
  ptr +=".button-off {background-color: #34495e;}\n";
  ptr +=".button-off:active {background-color: #2c3e50;}\n";
  ptr +="p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<h1>ESP8266 Web Server</h1>\n";
  ptr +="<h3>Using Access Point(AP) Mode</h3>\n";
  
   if(led1stat)
  {ptr +="<p>LED1 Status: ON</p><a class=\"button button-off\" href=\"/led1off\">OFF</a>\n";}
  else
  {ptr +="<p>LED1 Status: OFF</p><a class=\"button button-on\" href=\"/led1on\">ON</a>\n";}

  if(led2stat)
  {ptr +="<p>LED2 Status: ON</p><a class=\"button button-off\" href=\"/led2off\">OFF</a>\n";}
  else
  {ptr +="<p>LED2 Status: OFF</p><a class=\"button button-on\" href=\"/led2on\">ON</a>\n";}

  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;


}

// void log(){
//   Serial.println("serve");
//  server.send(200, "text/plain", "USA"); 
// }
