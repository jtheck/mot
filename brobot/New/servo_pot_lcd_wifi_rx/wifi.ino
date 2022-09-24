
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
