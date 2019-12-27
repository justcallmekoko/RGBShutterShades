// Adapted from https://github.com/macetech/RGBShades/blob/master/XYmap.h

// Pixel layout
//
//      0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15
//   +------------------------------------------------
// 0 |  .  0  1  2  3  4  5  6  7  8  9 10 11 12 13  .
// 1 | 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14
// 2 | 30 31 32 33 34 35 36  .  . 37 38 39 40 41 42 43
// 3 | 57 56 55 54 53 52 51  .  . 50 49 48 47 46 45 44
// 4 |  . 58 59 60 61 62  .  .  .  . 63 64 65 66 67  .
#ifndef XYmap_h
#define XYmap_h

#include <stdint.h>
#include <avr/pgmspace.h>

#define matrix_x 16
#define matrix_y 5

#define VIRTUAL_NUM_LEDS (matrix_x * matrix_y)
#define STS 80
#define LAST_VISIBLE_LED 67

class XYmap
{
  private:
    //CRGB leds[ VIRTUAL_NUM_LEDS ];
  
  
  // This function will return the right 'led index number' for 
  // a given set of X and Y coordinates on your RGB Shades. 
  // This code, plus the supporting 80-byte table is much smaller 
  // and much faster than trying to calculate the pixel ID with code.
  public:
    const uint8_t ShadesTable[80] = {
       68,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 69,
       29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14,
       30, 31, 32, 33, 34, 35, 36, 70, 71, 37, 38, 39, 40, 41, 42, 43,
       57, 56, 55, 54, 53, 52, 51, 72, 73, 50, 49, 48, 47, 46, 45, 44,
       74, 58, 59, 60, 61, 62, 75, 76, 77, 78, 63, 64, 65, 66, 67, 79
    };

    uint8_t XYtable[5][16] = {
       {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
       {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
       {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
       {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
       {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };
  
    uint8_t XY(uint8_t x, uint8_t y);
};
#endif
