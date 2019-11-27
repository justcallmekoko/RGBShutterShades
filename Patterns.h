#ifndef Patterns_h
#define Patterns_h

#include <Adafruit_NeoPixel.h>
#include "XYmap.h"

#ifdef __AVR__
  #include <avr/power.h>
#endif

#define matrix_x 16
#define matrix_y 5
#define PIN D2
#define Pixels 68
#define VIRTUAL_NUM_LEDS (matrix_x * matrix_y)

// Pattern definitions
#define COLOR_WIPE 0
#define DASH 1
#define PULSE 2
#define TWINKLE 3
#define TRACER 4

extern Adafruit_NeoPixel strip;
extern XYmap mapObj;

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
    int current_x = -1;
    int current_y = 0;
    bool increasing = true;
    bool show_led = true;
    float redStates[Pixels];
    float blueStates[Pixels];
    float greenStates[Pixels];
    float redStates2[SHADES_TABLE_SIZE];
    float blueStates2[SHADES_TABLE_SIZE];
    float greenStates2[SHADES_TABLE_SIZE];
    float fadeRate= 0.80;

  public:
    uint8_t currentPattern= 0;
    
    // Color presets
    float scanning[3] = {255, 6, 0};
    float deauthing[3] = {255, 6, 0};
    float serving[3] = {0, 170, 255};
    float clicon[3] = {255, 255, 0};
    float purple[3] = {255, 0, 255};

    void colorWipe(uint32_t c, uint8_t wait);
    void Dash(int r, int g, int b);
    void initPattern(uint8_t pattern);
    void Pulse(int r, int g, int b);
    void resetWheel();
    void Twinkle();
    void Tracer(int r, int g, int b);
    void Tracer2(int r, int g, int b);
};

#endif
