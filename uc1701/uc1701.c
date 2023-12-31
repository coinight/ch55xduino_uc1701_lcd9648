#include "SPI.h"
#include "stdio.h"
#include <stdint.h>
#include "uc1701.h"

const uint8_t oled_characters[18][16]=
{   
	/*--  文字:  0  --*/
	{0x00,0xE0,0x10,0x08,0x08,0x10,0xE0,0x00,0x00,0x0F,0x10,0x20,0x20,0x10,0x0F,0x00,},
	/*--  文字:  1  --*/
	{0x00,0x00,0x10,0x10,0xF8,0x00,0x00,0x00,0x00,0x00,0x20,0x20,0x3F,0x20,0x20,0x00,},
	/*--  文字:  2  --*/
	{0x00,0x70,0x08,0x08,0x08,0x08,0xF0,0x00,0x00,0x30,0x28,0x24,0x22,0x21,0x30,0x00,},
	/*--  文字:  3  --*/
	{0x00,0x30,0x08,0x08,0x08,0x88,0x70,0x00,0x00,0x18,0x20,0x21,0x21,0x22,0x1C,0x00,},
	/*--  文字:  4  --*/
	{0x00,0x00,0x80,0x40,0x30,0xF8,0x00,0x00,0x00,0x06,0x05,0x24,0x24,0x3F,0x24,0x24,},
	/*--  文字:  5  --*/
	{0x00,0xF8,0x88,0x88,0x88,0x08,0x08,0x00,0x00,0x19,0x20,0x20,0x20,0x11,0x0E,0x00,},
	/*--  文字:  6  --*/
	{0x00,0xE0,0x10,0x88,0x88,0x90,0x00,0x00,0x00,0x0F,0x11,0x20,0x20,0x20,0x1F,0x00,},
	/*--  文字:  7  --*/
	{0x00,0x18,0x08,0x08,0x88,0x68,0x18,0x00,0x00,0x00,0x00,0x3E,0x01,0x00,0x00,0x00,},
	/*--  文字:  8  --*/
	{0x00,0x70,0x88,0x08,0x08,0x88,0x70,0x00,0x00,0x1C,0x22,0x21,0x21,0x22,0x1C,0x00,},
	/*--  文字:  9  --*/
	{0x00,0xF0,0x08,0x08,0x08,0x10,0xE0,0x00,0x00,0x01,0x12,0x22,0x22,0x11,0x0F,0x00,},
	/*--  文字:  :  --*/
	{0x00,0x00,0x00,0xC0,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x30,0x00,0x00,0x00,},
	/*--  文字:  -  --*/
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x01,0x01,0x01,0x00,},
	/*--  文字:  .  --*/
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x30,0x00,0x00,0x00,0x00,0x00,},
	/*--  文字:  T  --*/
	{0x18,0x08,0x08,0xF8,0x08,0x08,0x18,0x00,0x00,0x00,0x20,0x3F,0x20,0x00,0x00,0x00,},
	/*--  文字:  A  --*/
	{0x00,0x00,0xC0,0x38,0xE0,0x00,0x00,0x00,0x20,0x3C,0x23,0x02,0x02,0x27,0x38,0x20,},
	/*--  文字:  °C  F--*/
	{0xC6,0x36,0x08,0x08,0x08,0x08,0x38,0x00,0x07,0x18,0x20,0x20,0x20,0x10,0x08,0x00,},
	/*--  文字:  U  --*/
	{0x08,0xF8,0x08,0x00,0x00,0x08,0xF8,0x08,0x00,0x1F,0x20,0x20,0x20,0x20,0x1F,0x00,}
 
};

void oled_setup(){
  digitalWrite(PIN_RST, HIGH);
  digitalWrite(PIN_RS, HIGH);
  digitalWrite(PIN_CS, HIGH);
  pinMode(PIN_RST, OUTPUT);
  pinMode(PIN_RS, OUTPUT);
  pinMode(PIN_CS, OUTPUT);
  SPI_begin();
  SPI_beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE3));
  oled_init();
  oled_Clear();
}
void oled_setxy(uint8_t x,uint8_t page){
  oled_WriteComm(0xb0 + page);
  oled_WriteComm(0x00 + (x & 0x0f));      //列地址
  oled_WriteComm(0x10+ ((x>>4) & 0x0f)) ;      //列地址
}

void oled_init(){
  oled_WriteComm(0xe2);
  oled_WriteComm(0xc8);
  oled_WriteComm(0xa0);
  oled_WriteComm(0x2f);
  oled_WriteComm(0x26);
  oled_WriteComm(0x81);
  oled_WriteComm(0x10);
  oled_WriteComm(0xaf);
}
void oled_phyreset(){
  digitalWrite(PIN_RST, HIGH);
  delay(10);
  digitalWrite(PIN_RST, LOW);
  delay(10);
  digitalWrite(PIN_RST, HIGH);
}
//On CH552: SCK->P1.7, MISO->P1.6 MOSI->P1.5
void oled_WriteComm(unsigned char comm) {
  digitalWrite(PIN_CS, 0);
  digitalWrite(PIN_RS, 0);
  SPI_transfer(comm);
  digitalWrite(PIN_CS, 1);
}
void oled_WriteData(unsigned char data) {
  digitalWrite(PIN_CS, 0);
  digitalWrite(PIN_RS, 1);
  SPI_transfer(data);
  digitalWrite(PIN_CS, 1);
}
void oled_Clear(void) {
  uint8_t i, j;
  oled_WriteComm(0x40);
  for (i = 0; i < 9; i++)  //一共九页 fixbug must 9
  {
    oled_WriteComm(0xb0 + i);  //页地址
    oled_WriteComm(0x10);      //列地址
    oled_WriteComm(0x00);      //列地址
    for (j = 0; j < 96; j++) {
      oled_WriteData(0x00);
    }
  }
}

void oled_pixelat(uint8_t x,uint8_t y,bool color){
  uint8_t bias = y & 0x07; // 2,2,1
  oled_setxy(x,y>>3);
  oled_WriteData(color<<bias);
  
}
void oled_pageat(uint8_t x,uint8_t page,uint8_t data){
  oled_setxy(x, page);
  oled_WriteData(data);
}

void oled_characterat(uint8_t x,uint8_t page,uint8_t type){
  int i;
  //characters[18][16]
  oled_setxy(x, page);
  for (i=0; i<8; i++) {
    oled_WriteData(oled_characters[type][i]);
  }
  oled_setxy(x, page+1);
  for (i=0; i<8; i++) {
    oled_WriteData(oled_characters[type][i+8]);
  }
}
///！max size at a line = 12
void oled_charactersat(uint8_t x,uint8_t page,uint8_t types[],uint8_t length){
  int i;
  for (i = 0; i < length; i++) {
  oled_characterat(x+i*8,page,types[i]);
  }
}