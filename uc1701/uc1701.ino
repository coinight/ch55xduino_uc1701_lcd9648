#include "uc1701.h"
unsigned char DataHigh, DataLow;
const uint8_t arr[] = {1,2,3,2,1,9,1,2,3,4,5,6};
// char buff[20];
// sprintf(buff, "1:%d",oled_ReadData());
// USBSerial_println(buff);
void setup() {
  oled_setup();
  oled_pixelat(0,0,1);
  oled_pixelat(1,1,1);
  // oled_pageat(5, 1, 0xff);
  //oled_characterat(0, 0, 1);
  oled_charactersat(0, 4, arr,12);
  oled_charactersat(0, 2, arr,12);
  oled_charactersat(0, 0, arr,12);
}

void loop() {

}
