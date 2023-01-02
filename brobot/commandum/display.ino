
/*********
 Mot.Moe command center
 OLED Display
*********/

#if HAS_DISPLAY
  const uint8_t IDLE_EXTENT_X = SCREEN_WIDTH - 85;
  const uint8_t IDLE_EXTENT_Y = SCREEN_HEIGHT - 8;
  uint8_t idleX = random(IDLE_EXTENT_X);
  uint8_t idleY = random(IDLE_EXTENT_Y);
  uint8_t idleXV = 1;
  uint8_t idleYV = 1;
#endif

void renderPage(String page){
  #if HAS_DISPLAY
    
//    Serial.println(page);
    display.clearDisplay();
    if (page == "boot"){
      display.setCursor(0,0);
      display.print(F("Initializing!")); 
  //    display.display();
    }
    
    if (page == "diag"){
      // POTENTIOMETERS
      display.setCursor(0, 0);
      display.print("p0:");
  //display.print("p0:                  p1:                  p2:                  p3:                  p4:                  p5:");
      display.setCursor(20, 0);
      display.print(ctrl.p0);
  
      display.setCursor(0, 10);
      display.print("p1:");
      display.setCursor(20, 10);
      display.print(ctrl.p1);
  
      display.setCursor(0, 20);
      display.print("p2:");
      display.setCursor(20, 20);
      display.print(ctrl.p2);
  
      display.setCursor(0, 30);
      display.print("p3:");
      display.setCursor(20, 30);
      display.print(ctrl.p3);
  
      display.setCursor(0, 40);
      display.print("p4:");
      display.setCursor(20, 40);
      display.print(ctrl.p4);
  
      display.setCursor(0, 50);
      display.print("p5:");
      display.setCursor(20, 50);
      display.print(ctrl.p5);
  
      // BUTTONS
      display.setCursor(50, 0);
      display.print("b0:");
      display.setCursor(70, 0);
      display.print(ctrl.b0);
  
      display.setCursor(50, 10);
      display.print("b1:");
      display.setCursor(70, 10);
      display.print(ctrl.b1);
  
      display.setCursor(50, 20);
      display.print("b2:");
      display.setCursor(70, 20);
      display.print(ctrl.b2);
  
      // GYROMETER
      display.setCursor(84,0);
      display.print("x:");
      display.setCursor(96,0);
      display.print(state.gx);
  
      display.setCursor(84,10);
      display.print("y:");
      display.setCursor(96,10);
      display.print(state.gy);
  
      display.setCursor(84,20);
      display.print("z:");
      display.setCursor(96,20);
      display.print(state.gz);

      // ACCELEROMETER
      display.setCursor(84,40);
      display.print("x:");
      display.setCursor(96,40);
      display.print(state.ax);
  
      display.setCursor(84,50);
      display.print("y:");
      display.setCursor(96,50);
      display.print(state.ay);
  
      display.setCursor(84,60);
      display.print("z:");
      display.setCursor(96,60);
      display.print(state.az);

      // TEMPERATURE
      display.setCursor(84,30);
      display.print("C:");
      display.setCursor(96,30);
      display.print(state.t);    
    }

    
    if (page == "idle"){
      if (idleX > IDLE_EXTENT_X || idleX < 1){
        idleXV *= -1;
      }
      if (idleY > IDLE_EXTENT_Y || idleY < 1){
        idleYV *= -1;
      }
      idleX += idleXV;
      idleY += idleYV;
      display.setCursor(idleX, idleY);
      display.println(F("Hello Mot.Moe!"));
    }

    
    if (page == "run"){
      
    }
    display.display();
  #endif
}
