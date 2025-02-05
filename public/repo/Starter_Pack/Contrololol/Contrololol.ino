/************************************
  Mot.moe's 'Radio Control (lolol)' Starter Pack Example.
  
  Featuring: iBus(RC), bluetooth, RF(~400Mhz) Transmit and Receive, IR, IMU
  Considerations: Variety of application.
************************************/
//MM PROJECT Control
//MM BOARDS [ESP32]
//MM FEATURES [IBUS, BT, RF_TX, RF_RX, IR, IMU]
//MM ESP32 [IBUS, BT, RF_TX, RF_RX, IR, IMU]
//MM
// #define MM_IS_ESP32
//MM
// #define MM_HAS_IBUS
// #define MM_HAS_BT
// #define MM_HAS_RF_TX
// #define MM_HAS_RF_RX
// #define MM_HAS_IR
// #define MM_HAS_IMU
//MM


#ifdef MM_HAS_IBUS
// PIN! IBUS data --> RX2
#include <IBusBM.h>
IBusBM ibus;
 
// Read the number of a given channel and convert to the range provided.
// If the channel is off, return the default value
int readChannel(byte channelInput, int minLimit, int maxLimit, int defaultValue) {
  uint16_t ch = ibus.readChannel(channelInput);
  if (ch < 100) return defaultValue;
  return map(ch, 1000, 2000, minLimit, maxLimit);
}
 
// // Read the channel and return a boolean value
// bool readSwitch(byte channelInput, bool defaultValue) {
//   int intDefaultValue = (defaultValue) ? 100 : 0;
//   int ch = readChannel(channelInput, 0, 100, intDefaultValue);
//   return (ch > 50);
// }
#endif // MM_HAS_IBUS



void setup() {
  // put your setup code here, to run once:

  
  // Start serial monitor
  Serial.begin(115200);
  Serial.print("FLYSKY TAKE ONE");
#ifdef MM_HAS_IBUS
  // Attach iBus object to serial port
  ibus.begin(Serial2);
#endif // MM_HAS_IBUS
}


void loop() {
  // put your main code here, to run repeatedly:


  // Cycle through first 5 channels and determine values
  // Print values to serial monitor
  // Note IBusBM library labels channels starting with "0"
 
  for (byte i = 0; i < 10; i++) {
    int value = readChannel(i, -100, 100, 0);
    Serial.print("Ch");
    Serial.print(i + 1);
    Serial.print(": ");
    Serial.print(value);
    Serial.print(" | ");
  }
 
  // Print channel 6 (switch) boolean value
//  Serial.print("Ch7: ");
//  Serial.print(readSwitch(7, false));
  Serial.println();
 
  delay(10);
}