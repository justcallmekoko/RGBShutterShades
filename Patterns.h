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


#define NUM_PATTERN 7

// Pattern definitions
#define DASH 0
#define FALLING_RAINBOW 1
#define PULSE 2
#define RADIATE_RAINBOW 3
#define TWINKLE 4
#define TRACER 5
#define BIT_RACE 6

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
    int wheel_pos = 255;
    int wheel_speed = 1; // lower = slower
    bool increasing = true;
    bool show_led = true;
    float redStates[Pixels];
    float blueStates[Pixels];
    float greenStates[Pixels];
    float redStates2[SHADES_TABLE_SIZE];
    float blueStates2[SHADES_TABLE_SIZE];
    float greenStates2[SHADES_TABLE_SIZE];
    float fadeRate= 0.80;

    uint32_t Wheel(byte WheelPos);

  public:
    uint8_t currentPattern = 0
    ;
    
    // Color presets
    float scanning[3] = {255, 6, 0};
    float deauthing[3] = {255, 6, 0};
    float serving[3] = {0, 170, 255};
    float clicon[3] = {255, 255, 0};
    float purple[3] = {255, 0, 255};

    void bitRace();
    void colorWipe(uint32_t c, uint8_t wait);
    void Dash(int r, int g, int b);
    void initPattern(uint8_t pattern);
    void Pulse(int r, int g, int b);
    void Rainbow1();
    void Rainbow2();
    void Rainbow3();
    void resetWheel();
    void Twinkle();
    void Tracer(int r, int g, int b);
    void Tracer2(int r, int g, int b);
};

#endif
