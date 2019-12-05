#include "Patterns.h"
#include "XYmap.h"
#include "ButtonInput.h"

Adafruit_NeoPixel strip = Adafruit_NeoPixel(Pixels, PIN, NEO_GRB + NEO_KHZ800);

Patterns patternObj;
XYmap mapObj;
ButtonInput buttonObj;

void setup() {
  Serial.begin(115200);

  buttonObj.initButtonInput();
  
  strip.begin();
  strip.setBrightness(50);
  strip.show();

  // Test XY function
  strip.setPixelColor(mapObj.XY(1, 0), strip.Color(255, 255, 255));
  strip.setPixelColor(mapObj.XY(1, 1), strip.Color(255, 255, 255));
  strip.setPixelColor(mapObj.XY(0, 1), strip.Color(255, 255, 255));
  strip.show();
  delay(2000);
}

void loop()
{
  buttonObj.checkPatternChange();
  patternObj.initPattern(patternObj.currentPattern);
}
