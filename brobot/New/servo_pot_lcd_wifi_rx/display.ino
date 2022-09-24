

const int BALLS = 0;
const int COCK = 1;
const int PUSS = 2;


struct LCD {
  int page;
  
};

struct LCD gui = {
  {BALLS}
};


//int page = 0;
void renderPage(int page){
  display.clearDisplay();
  if (page == BALLS){
    display.setCursor(40, 10);
    display.println(p1.actual);
    display.setCursor(40, 30);
    display.println(p1.norm);
  }
  if (page == COCK){
    display.setCursor(0, 0);
    display.println("Hello Mot.Moe!");
  }
  if (gui.page == PUSS){
    
  }
  display.display();
}
