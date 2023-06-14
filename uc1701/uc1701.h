#include <stdint.h>
#include <SPI.h>
#define PIN_RST 11
#define PIN_RS 34
#define PIN_CS 33

void oled_characterat(uint8_t x,uint8_t page,uint8_t type);
void oled_setup();
//On CH552: SCK->P1.7, MISO->P1.6 MOSI->P1.5
void oled_WriteComm(uint8_t comm);
void oled_WriteData(uint8_t data);
void oled_Clear(void);
void oled_init();
void oled_phyreset();
void oled_pixelat(uint8_t x,uint8_t y,bool color);
void oled_pageat(uint8_t x,uint8_t page,uint8_t data);
void oled_charactersat(uint8_t x,uint8_t page,uint8_t types[],uint8_t length);