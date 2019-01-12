#ifndef Clock_h
#define Clock_h

#include <Arduino.h>
#include <LDateTime.h>
#include "Display.h"
#include "DisplayConfig.h"

class Clock
{
  public:
    Clock(byte edit_button, byte confirm_button);
    void setup();
    DisplayGroup getFormattedCurrentTime();
    void updateTime();
    void enterSetAlarmMode();
    bool isAlarmTime();
    bool isHourlyUpdateTime();
    bool isDailyUpdateTime();
  private:
    Display _display;
    byte _edit_button;
    byte _confirm_button;
    datetimeInfo _currentTime;
    datetimeInfo _alarmTime;
    datetimeInfo _lastAlarmTime;
    datetimeInfo _lastHourlyUpdateTime;
    datetimeInfo _lastDailyUpdateTime;
    DisplayGroup getFormattedTime(datetimeInfo time);
};

#endif
