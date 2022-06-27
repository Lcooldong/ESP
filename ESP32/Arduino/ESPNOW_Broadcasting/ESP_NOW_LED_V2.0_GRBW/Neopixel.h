#ifndef Neopixel_h
#define Neopixel_h

#include <Adafruit_NeoPixel.h>
//#include "stdint.h"

void init_Neopixel(uint8_t brightness);
//void pickOneLED(uint8_t ledNum, uint8_t R, uint8_t G, uint8_t B, uint8_t brightness, uint8_t wait);
void pickOneLED(uint8_t ledNum, uint32_t color, uint8_t brightness, int wait);
void blinkNeopixel(uint32_t color, int times, int delays);
void colorWipe(uint32_t color, int wait);
void theaterChase(uint32_t color, int wait);
void rainbow(int wait);
void theaterChaseRainbow(int wait);


#endif
