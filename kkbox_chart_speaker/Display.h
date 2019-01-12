#ifndef Display_h
#define Display_h

#include <Arduino.h>
#include "DisplayConfig.h"

class Display
{
  public:
    Display();
    void setup();
    void show(DisplayGroup word);
  private:
    void showOne(byte position, byte letter);
};

#endif
