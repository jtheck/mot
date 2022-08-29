// RX
#include <RH_ASK.h>

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
  int dat[3]={0};
  
  uint8_t buflen = sizeof(dat);

  if (driver.recv((uint8_t*)dat, &buflen))
  {
    for (int i=0; i<3; i++){
      Serial.println(dat[i]);
    }
    
    if (dat[1] == 1 || dat[2] == 1) {
      digitalWrite(out, HIGH);
    } else {
      digitalWrite(out, LOW);
    }
    
  }
}
