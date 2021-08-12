




//void 
void motorsCycle(){
  
  for (int i=0; i<MOTOR_COUNT; i++){
    struct Moto &tMoto = motoArr[i];

    tMoto.pos += tMoto.vel;
    
    if (tMoto.pos < tMoto.min){
      tMoto.vel = 0;
      tMoto.pos = tMoto.min;
    }
    if (tMoto.pos > tMoto.max){
      tMoto.vel = 0;
      tMoto.pos = tMoto.max;
    }

    tMoto.vel *= .8;

    int degWidth = map(tMoto.pos, 0, 180, PWM_MIN, PWM_MAX); // degrees to pulse width
    int tick = int(float(degWidth) / 1000000 * PWM_FREQ * 4096); // tick to end pulse

    pwm.setPWM(tMoto.pin, 0, tick);
//    delay(3);
   
  }


}














//void moveMotor(int controlIn, int motorOut)
//{
//  int pulse_wide, pulse_width, potVal;
//  
//  // Read values from potentiometer
//  potVal = analogRead(controlIn);
//
//  lcd.setCursor(10,1);
//  lcd.print(potVal);

//  //  pwid = map(potVal, 0, 1023, PWM_MIN, PWM_MAX);
//  wid = int(float(pwid) / 1000000 * PWM_FREQ * 4096);
  
//  // Convert to pulse width
//  pulse_wide = map(potVal, 0, 180, PWM_MIN, PWM_MAX);
//  pulse_width = int(float(pulse_wide) / 1000000 * PWM_FREQ * 4096);
//  
//  //Control Motor
//  pwm.setPWM(motorOut, 0, pulse_width);
//
//}
