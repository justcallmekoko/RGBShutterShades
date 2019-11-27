#include "Patterns.h"

// Fill the dots one after the other with a color


void Patterns::colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

void Patterns::Twinkle()
{
  if (this->show_led)
  {
    this->current_itter++;
    if (this->current_itter >= this->ring_speed)
    {
      this->current_itter = 0;
  
      if (random(this->max_interval) == 1) {
        uint16_t i = random(Pixels);
        if (this->redStates[i] < 1 && this->greenStates[i] < 1 && this->blueStates[i] < 1) {
          this->redStates[i] = random(256);
          this->greenStates[i] = random(256);
          this->blueStates[i] = random(256);
        }
      }
    }
  
    if (this->current_fade_itter > this->fade_delay)
    {
      this->current_fade_itter = 1;
      for(uint16_t l = 0; l < Pixels; l++) {
        if (this->redStates[l] > 1 || this->greenStates[l] > 1 || this->blueStates[l] > 1) {
          strip.setPixelColor(l, this->redStates[l], this->greenStates[l], this->blueStates[l]);
          
          if (this->redStates[l] > 1) {
            this->redStates[l] = this->redStates[l] * this->fadeRate;
          } else {
            this->redStates[l] = 0;
          }
          
          if (this->greenStates[l] > 1) {
            this->greenStates[l] = this->greenStates[l] * this->fadeRate;
          } else {
            this->greenStates[l] = 0;
          }
          
          if (this->blueStates[l] > 1) {
            this->blueStates[l] = this->blueStates[l] * this->fadeRate;
          } else {
            this->blueStates[l] = 0;
          }
          
        } else {
          strip.setPixelColor(l, 0, 0, 0);
        }
      }
    }
    this->current_fade_itter++;
    strip.show();
  }
}
