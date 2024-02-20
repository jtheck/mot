
// listen for input state updates

void observeInput(){
  
}






// what to do with state anomaly

void walkCursor(int max){
  if (cursorPos < max){
    cursorPos ++;  
  } else {
    cursorPos = 0;
  }

}


void walkCursorReverse(int max){
  if (cursorPos > 0){
    cursorPos --;  
  } else {
    cursorPos = max;
  }

}
