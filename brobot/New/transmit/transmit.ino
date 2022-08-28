// TX
#include <RH_ASK.h>



RH_ASK driver(2000, 14, 12, 0);

const int switch_on = 9, switch_off = 10;
int state = 0;
char *msg;


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
  if (digitalRead(switch_on) == HIGH){
    msg = "Switch_ON";
    state = 1;
  }
  else if (digitalRead(switch_off) == HIGH){
    msg = "Switch_OFF";
    state = 1;
  }
  else if (state == 1){
    driver.send((uint8_t *)msg, strlen(msg));
    driver.waitPacketSent();
    Serial.println("SENT ");
//    Serial.println((uint8_t *)msg);
//    delay(200);
    
    state = 0;
  }
//  char msg = "hello mot.moe! "+String(iter);
//  Serial.println(msg);
//    driver.send((uint8_t *)msg, strlen(msg));
//  driver.waitPacketSent();
//  delay(500);
}
