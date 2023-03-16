
/*********
 Mot.Moe command center
 OLED Display
*********/

#if HAS_DISPLAY
  const uint8_t IDLE_EXTENT_X = SCREEN_WIDTH - 16;
  const uint8_t IDLE_EXTENT_Y = SCREEN_HEIGHT - 16;
  uint8_t idleX = random(IDLE_EXTENT_X);
  uint8_t idleY = random(IDLE_EXTENT_Y);
  uint8_t idleXV = 1;
  uint8_t idleYV = 1;

  const uint8_t iconX = SCREEN_WIDTH - 16;
  const uint8_t iconY = 0;
 
  
  const unsigned char icon [] PROGMEM = {
    0x00, 0x00, 0x70, 0x06, 0xf7, 0xef, 0xf8, 0x1f, 0x60, 0x07, 0x20, 0x02, 0x4e, 0x61, 0x8e, 0x71, 
    0x8c, 0x71, 0x8c, 0x61, 0x83, 0x82, 0x41, 0x02, 0x27, 0xc4, 0x13, 0xc8, 0x0c, 0x30, 0x03, 0xc0
  };
#endif

void renderPage(int page){
  #if HAS_DISPLAY
    display.clearDisplay();

    if (page == PAGE_MAIN){
      display.setCursor(0,0);
      display.print(timer.current - timer.started);

//      display.setCursor(0,10);
//      display.print(timer.frameDuration);

      display.setCursor(0,20);
      display.print(timer.idleClock);
      
      display.drawBitmap(iconX, iconY, icon, 16, 16, 1);

      display.setCursor(0, 53);
      display.print("Play Train Calib Diag");

      display.setCursor(cursorPos * 33 + 7, 61);
      display.print("^");
    }

    if (page == PAGE_CALIBRATE){
      display.setCursor(0,0);
      display.print("Calibrate");
      
      display.setCursor(0, 53);
      display.print("0   1   2   3   4   X");

      display.setCursor(cursorPos * 24, 61);
      display.print("^");
    }

    if (page == PAGE_TRAIN){
      display.setCursor(0,0);
      display.print("Train");
      
      display.setCursor(0, 53);
      display.print("0   1   2   3   4   X");

      display.setCursor(cursorPos * 24, 61);
      display.print("^");
    }

    if (page == PAGE_PLAY){
      display.setCursor(0,0);
      display.print("Play");
      
      display.drawBitmap(iconX, iconY, icon, 16, 16, 1);
    }

    
    if (page == PAGE_BOOT){
      display.setCursor(0,0);
      display.print("Hello Mot.Moe!");
      
    }

    
    if (page == PAGE_DIAG){
      // POTENTIOMETERS
      display.setCursor(0, 0);
      display.print("p0:");
      display.setCursor(18, 0);
      display.print(ctrl.p0.actual);
  
      display.setCursor(0, 8);
      display.print("p1:");
      display.setCursor(18, 8);
      display.print(ctrl.p1);
  
      display.setCursor(0, 16);
      display.print("p2:");
      display.setCursor(18, 16);
      display.print(ctrl.p2);
  
      display.setCursor(0, 24);
      display.print("p3:");
      display.setCursor(18, 24);
      display.print(ctrl.p3);
  
      display.setCursor(0, 32);
      display.print("p4:");
      display.setCursor(18, 32);
      display.print(ctrl.p4);
  
      display.setCursor(0, 40);
      display.print("p5:");
      display.setCursor(18, 40);
      display.print(ctrl.p5);
  
      // BUTTONS
      display.setCursor(50, 0);
      display.print("b0:");
      display.setCursor(70, 0);
      display.print(ctrl.b0);
  
      display.setCursor(50, 8);
      display.print("b1:");
      display.setCursor(70, 8);
      display.print(ctrl.b1);
  
      display.setCursor(50, 16);
      display.print("b2:");
      display.setCursor(70, 16);
      display.print(ctrl.b2);
  
//      // GYROMETER
//      display.setCursor(84,0);
//      display.print("x:");
//      display.setCursor(96,0);
//      display.print(state.gx);
//  
//      display.setCursor(84,8);
//      display.print("y:");
//      display.setCursor(96,8);
//      display.print(state.gy);
//  
//      display.setCursor(84,16);
//      display.print("z:");
//      display.setCursor(96,16);
//      display.print(state.gz);
//
//      // ACCELEROMETER
//      display.setCursor(84,24);
//      display.print("x:");
//      display.setCursor(96,24);
//      display.print(state.ax);
//  
//      display.setCursor(84,32);
//      display.print("y:");
//      display.setCursor(96,32);
//      display.print(state.ay);
//  
//      display.setCursor(84,40);
//      display.print("z:");
//      display.setCursor(96,40);
//      display.print(state.az);
//
//      // TEMPERATURE
//      display.setCursor(84,48);
//      display.print("c:");
//      display.setCursor(96,48);
//      display.print(state.t);    
    }

    
    if (page == PAGE_IDLE){
      if (idleX > IDLE_EXTENT_X || idleX < 1){
        idleXV *= -1;
      }
      if (idleY > IDLE_EXTENT_Y || idleY < 1){
        idleYV *= -1;
      }
      idleX += idleXV;
      idleY += idleYV;
      display.drawBitmap(idleX, idleY, icon, 16, 16, 1);
    }

    display.display();
  #endif
}
