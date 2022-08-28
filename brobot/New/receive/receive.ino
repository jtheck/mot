// RX
#include <RH_ASK.h>
//#include <SPI.h>

RH_ASK driver(2000,14,12,0);
const int out = 9;
char receive[32];

void setup()
{
    Serial.begin(115200);

  driver.init();
  pinMode(out, OUTPUT);
  Serial.println("rdy!");
}

void loop()
{
  uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
  uint8_t buflen = sizeof(buf);

  if (driver.recv(buf, &buflen))
  {
    memset(receive, 0, sizeof(receive));
    for (int i = 0; i < buflen; i++) {
      receive[i] = buf[i];
    }
    if (strcmp(receive, "Switch_ON") == 0) {
      digitalWrite(out, HIGH);
      Serial.println(receive);
    } else if (strcmp(receive, "Switch_OFF") == 0) {
      digitalWrite(out, LOW);
    Serial.println(receive);
    }
    
  }
}
