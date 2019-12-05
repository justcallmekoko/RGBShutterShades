#include "ButtonInput.h"
#include "Patterns.h"

extern Patterns patternObj;

void ButtonInput::checkPatternChange()
{
  if (digitalRead(BUTTON) == 1)
  {
    if (!this->current_button_state)
    {
      this->current_button_state = true;
      patternObj.currentPattern++;
      if (patternObj.currentPattern >= NUM_PATTERN)
        patternObj.currentPattern = 0;
      Serial.print("Changing pattern: ");
      Serial.println(patternObj.currentPattern);
      patternObj.resetWheel();
    }
  }
  else
    this->current_button_state = false;
}

void ButtonInput::initButtonInput()
{
  pinMode(BUTTON, INPUT);
}
