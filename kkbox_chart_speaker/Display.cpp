#include <Arduino.h>
#include "Display.h"
#include "DisplayConfig.h"

#define PIN_0 0
#define PIN_g 1
#define PIN_c 2
#define PIN_d 3
#define PIN_e 4
#define PIN_b 10
#define PIN_1 9
#define PIN_2 8
#define PIN_f 7
#define PIN_a 6
#define PIN_3 5

const byte pos_pins[4] = {PIN_3, PIN_2, PIN_1, PIN_0};
const byte seg_pins[7] = {PIN_a, PIN_b, PIN_c, PIN_d, PIN_e, PIN_0, PIN_g};

const bool rule[11][7] = {
  {1, 1, 1, 1, 1, 1, 0}, // 0
  {0, 1, 1, 0, 0, 0, 0}, // 1
  {1, 1, 0, 1, 1, 0, 1}, // 2
  {1, 1, 1, 1, 0, 0, 1}, // 3
  {0, 1, 1, 0, 0, 1, 1}, // 4
  {1, 0, 1, 1, 0, 1, 1}, // 5
  {1, 0, 1, 1, 1, 1, 1}, // 6
  {1, 1, 1, 0, 0, 0, 0}, // 7
  {1, 1, 1, 1, 1, 1, 1}, // 8
  {1, 1, 1, 1, 0, 1, 1}, // 9
  {0, 0, 0, 0, 0, 0, 0}, // BLANK
};

Display::Display() {}

void Display::setup()
{
  for(int i = 0; i < 4; i++){
    pinMode(pos_pins[i], OUTPUT);
  }
  for(int i = 0; i < 8; i++){
    pinMode(seg_pins[i], OUTPUT);
  }

  DisplayGroup dg;
  dg.letter1 = BLANK;
  dg.letter2 = BLANK;
  dg.letter3 = BLANK;
  dg.letter4 = BLANK;

  show(dg);
}

void Display::show(DisplayGroup word)
{
  byte arr[] = {word.letter1, word.letter2, word.letter3, word.letter4};
  for(int i = 0; i < 4; i++){
    showOne(i, arr[i]);
    delay(5);
  }
}

void Display::showOne(byte position, byte letter)
{
  for(int i = 0; i < 4; i++){
    digitalWrite(pos_pins[i], position == i ? HIGH : LOW);
  }

  for(int i = 0; i < 7; i++){
    digitalWrite(seg_pins[i], rule[letter][i] ? LOW : HIGH);
  }
}
