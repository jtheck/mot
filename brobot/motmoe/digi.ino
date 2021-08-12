



// Render active page to lcd
void renderPage(){
  lcd.clear();
  if (page == "HELLO"){
    lcd.setCursor(0,0);
    lcd.print(timer);
    lcd.setCursor(13,0);
    lcd.print(age);
    lcd.setCursor(1,2);
    lcd.print("hello mot.moe!");
  }
  if (page == "DEFAULT"){
    lcd.setCursor(0,0);
    lcd.print(int(mpu.getAngleX()));
    lcd.print("x");
    lcd.setCursor(5,0);
    lcd.print(int(mpu.getAngleY()));
    lcd.print("y");
    lcd.setCursor(10,0);
    lcd.print(int(mpu.getAngleZ()));
    lcd.print("z");
    lcd.setCursor(13,1);
    lcd.print(int(mpu.getTemp()));
    lcd.print("C");
    lcd.setCursor(1,1);
    lcd.print(controlB);
  }
  if (page == "CONTROL"){
    lcd.setCursor(0,0);
    lcd.print("M:");
    lcd.setCursor(3,0);
    lcd.print(motoArr[motoActive].name);
    lcd.setCursor(0,2);
    lcd.print(motoArr[motoActive].pin);
    lcd.setCursor(13,1);
    lcd.print(motoArr[motoActive].pos);
    lcd.setCursor(9,1);
    lcd.print(motoArr[motoActive].vel);
    lcd.setCursor(0,1);
    lcd.print(motoArr[motoActive].min);
    lcd.setCursor(4,1);
    lcd.print(motoArr[motoActive].max);
    
  }
}



// return readable name for IR Remote buttons
String mapButton(){
  switch (receiver.decodedIRData.decodedRawData) {
    case 0xBA45FF00:
      button = "POWER";
      break;
    case 0xB946FF00:
      button = "VOL+";
      break;
    case 0xB847FF00:
      button = "FUNC/STOP";
      break;
    case 0xBB44FF00:
      button = "|<<";
      break;
    case 0xBF40FF00:
      button = ">||";
      break ;
    case 0xBC43FF00:
      button = ">>|";
      break ;
    case 0xF807FF00:
      button = "DOWN";
      break ;
    case 0xEA15FF00:
      button = "VOL-";
      break ;
    case 0xF609FF00:
      button = "UP";
      break ;
    case 0xE916FF00:
      button = "0";
      break ;
    case 0xE619FF00:
      button = "EQ";
      break ;
    case 0xF20DFF00:
      button = "ST/REPT";
      break ;
    case 0xF30CFF00:
      button = "1";
      break ;
    case 0xE718FF00:
      button = "2";
      break ;
    case 0xA15EFF00:
      button = "3";
      break ;
    case 0xF708FF00:
      button = "4";
      break ;
    case 0xE31CFF00:
      button = "5";
      break ;
    case 0xA55AFF00:
      button = "6";
      break ;
    case 0xBD42FF00:
      button = "7";
      break ;
    case 0xAD52FF00:
      button = "8";
      break ;
    case 0xB54AFF00:
      button = "9";
      break ;
    default:
      button = "REPEAT";
      break;
  }
  
  return button;
}
