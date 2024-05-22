/************************************
 Mot.moe 'Hello Wifi' example.
  Ft. Dynamic WiFi, Static WiFi
************************************/
//MM PROJECT Hello Wifi
//MM BOARDS [ESP8266, ESP01, ESP32]
//MM FEATURES [DYNAMICWIFI, STATICWIFI]
//MM ESP8266 [DYNAMICWIFI, STATICWIFI]
//MM ESP01 [STATICWIFI]
//MM ESP32 [DYNAMICWIFI, STATICWIFI]
// #define MM_IS_ESP01
#define MM_IS_ESP32
// #define MM_IS_ESP8266
#define MM_HAS_STATICWIFI
// #define MM_HAS_DYNAMICWIFI


#ifdef MM_IS_ESP32
#ifdef MM_HAS_STATICWIFI
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
// WiFiServer server(80);
AsyncWebServer server(80);
#endif
#ifdef MM_HAS_DYNAMICWIFI

#endif
#endif
//MM
#ifdef MM_IS_ESP8266
#ifdef MM_HAS_STATICWIFI
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
ESP8266WebServer server(80);
#endif // MM_HAS_STATICWIFI
#endif

#ifdef MM_HAS_STATICWIFI
// WARNING: Protect your credentials!
const char *hostName = "Hello Wifi";
const char *ssid     = "ROBO WiFi";
const char *password = "hellomotmoe";
#endif

#ifdef MM_HAS_DYNAMICWIFI
#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager
#endif // MM_HAS_DYNAMICWIFI
//MM

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);

#ifdef MM_HAS_DYNAMICWIFI

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
#endif // MM_HAS_DYNAMICWIFI

#ifdef MM_HAS_STATICWIFI
  // WIFI
  // WiFi.hostname(hostName);
  WiFi.begin(ssid, password);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.print(".");
  }
  Serial.println(" ");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());


#ifdef MM_IS_ESP32
  server.on("/", [](AsyncWebServerRequest *request){
    request->send(200, "text/plain", "HIHIHIHHOHOHO");
  });
#endif

#ifdef MM_IS_ESP8266
  server.on("/", []()
            { server.send(200, "text/plain", "HIHIHOHO");
            Serial.println("GAH"); });
  server.on("/boop", h_boop);
  server.on("/poll", h_poll);
  server.on("/marco", h_marco);
  server.on("/log", h_log);
  server.enableCORS(true);
#endif
  server.begin();

  Serial.println("listening");
#endif // MM_HAS_STATICWIFI
}

void loop()
{
  // up and at them
#ifdef MM_HAS_STATICWIFI
// server.handleClient();
#endif // MM_HAS_STATICWIFI

#ifdef MM_HAS_DYNAMICWIFI
  // get put
  if (0)
   true;
#endif // MM_HAS_DYNAMICWIFI

}


// void h_poll(){
//   server.send(200, "text/plain", String(millis()));

//   // server.send(200, "application/json", {millis());
//   Serial.println("served /poll");

// }

// void h_log(){
//   server.send(200, "application/json", "{\"recent\":[\"bc\"]}");
//   Serial.println("served /log");

// }

// // void h_index()
// // {
// //   server.send(200, "text/plain", "HELLO MOMO");
// //   Serial.println("served /");
// // }
// void h_boop()
// {
//   // server.enableCORS(true);
//   server.send(200, "application/json", "{\"a\":\"bc\"}");
//   Serial.println("served /boop");

//   // StaticJsonDocument<200> doc;
//   // deserializeJson(doc, server.arg("plain"));
//   // JsonObject obj = doc.as<JsonObject>();
//   const char *boop = "IT IS WHAT IT IS"; // doc["x"];
//   Serial.println(boop);
// }
// void h_marco()
// {
//   // server.send(200, "application/json", "{\"a\":\"bc\"}");
//   Serial.println("served /marco");

//   // server.send(200, "text/plain", "HELLO MOMO");
//   // Serial.println("served /");

//  server.send(200, "text/plain", hostName); 
// }

// void log(){
//   Serial.println("serve");

//  server.send(200, "text/plain", "USA"); 

// }