#include "XYmap.h"

uint8_t XYmap::XY( uint8_t x, uint8_t y)
{
  // any out of bounds address maps to the first hidden pixel
  if( (x >= matrix_x) || (y >= matrix_y) ) {
    return (LAST_VISIBLE_LED + 1);
  }

  uint8_t i = (y * matrix_x) + x;
  uint8_t j = this->ShadesTable[i];
  return j;
}

uint8_t ReverseXYmap(uint8_t index)
{
  
}
