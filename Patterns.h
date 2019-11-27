#ifndef Patterns_h
#define Patterns_h

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN D1

#define Pixels 68

extern Adafruit_NeoPixel strip;

class Patterns
{
  private:
    // Ring Settings
    int ring_speed = 6; // (ms * fade_delay)
    int fade_delay = 20; // ms
    int max_interval = 2; // TIME BETWEEN PIXELS FIRING ((0 - x) * 10ms)
    
    int current_itter = ring_speed;
    int current_pixel = 0;
    int current_fade_itter = 1;
    bool increasing = true;
    bool show_led = true;
    float redStates[Pixels];
    float blueStates[Pixels];
    float greenStates[Pixels];
    float fadeRate = 0.80;

  public:
    void colorWipe(uint32_t c, uint8_t wait);
    void Twinkle();
};

#endif
