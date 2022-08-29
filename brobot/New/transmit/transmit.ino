// TX
#include <RH_ASK.h>


RH_ASK driver(2000, 14, 12, 0);

const int switch_on = 9, switch_off = 10;
int dat[3];

void setup()
{
  Serial.begin(115200);
  if (!driver.init())
    Serial.println("init failed");

  pinMode(switch_on, INPUT);
  pinMode(switch_off, INPUT);
}

void loop()
{
  
  dat[0] = analogRead(A0);
  dat[1]=0;
  dat[2]=0;
  if (digitalRead(switch_on) == HIGH){
    dat[1] = 1;
  }
  if (digitalRead(switch_off) == HIGH){
    dat[2] = 1;
  }
  driver.send((uint8_t *)&dat, sizeof(dat));
  driver.waitPacketSent();
}
