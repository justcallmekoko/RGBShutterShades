#ifndef ButtonInput_h
#define ButtonInput_h

#define BUTTON 2

class ButtonInput
{
  private:
    bool current_button_state = false;
  public:
    void checkPatternChange();
    void initButtonInput();
};

#endif
