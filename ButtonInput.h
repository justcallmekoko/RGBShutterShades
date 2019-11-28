#ifndef ButtonInput_h
#define ButtonInput_h

#define BUTTON D0

class ButtonInput
{
  private:
    bool current_button_state = false;
  public:
    void checkPatternChange();
    void initButtonInput();
};

#endif
