#include <Arduino.h>
#include <LDateTime.h>
#include "Clock.h"
#include "Display.h"
#include "DisplayConfig.h"

Clock::Clock(byte edit_button, byte confirm_button)
{
  _edit_button = edit_button;
  _confirm_button = confirm_button;
}

void Clock::setup()
{
  datetimeInfo dt;
  LDateTime.getTime(&dt);
  _currentTime = dt;

  // Serial.print("[setup] _currentTime: ");
  // Serial.print(_currentTime.hour);
  // Serial.print(":");
  // Serial.print(_currentTime.min);
  // Serial.println();

  _display.setup();
  _display.show(getFormattedCurrentTime());
}

DisplayGroup Clock::getFormattedCurrentTime()
{
  return getFormattedTime(_currentTime);
}

void Clock::updateTime()
{
  datetimeInfo dt;
  LDateTime.getTime(&dt);

  _currentTime.hour = dt.hour;
  _currentTime.min = dt.min;
  _currentTime.sec = dt.sec;

  // Serial.print("[updated] _currentTime: ");
  // Serial.print(_currentTime.hour);
  // Serial.print(":");
  // Serial.print(_currentTime.min);
  // Serial.println();

  _display.show(getFormattedCurrentTime());
}

void Clock::enterSetAlarmMode()
{
  DisplayGroup formattedTime = getFormattedTime(_alarmTime);
  byte count = 0;

  // Serial.print("[original] _alarmTime: ");
  // Serial.print(_alarmTime.hour);
  // Serial.print(":");
  // Serial.print(_alarmTime.min);
  // Serial.println();

  while (digitalRead(_confirm_button))
  {
    delay(500);
  }

  while (!digitalRead(_confirm_button))
  {
    if (digitalRead(_edit_button))
    {
      _alarmTime.hour = _alarmTime.hour == 23 ? 0 : _alarmTime.hour + 1;
      formattedTime = getFormattedTime(_alarmTime);

      // Serial.print("[updated] _alarmTime: ");
      // Serial.print(_alarmTime.hour);
      // Serial.print(":");
      // Serial.print(_alarmTime.min);
      // Serial.println();

      while (digitalRead(_edit_button))
      {
        delay(500);
      }
    }

    _display.show(formattedTime);

    /* if (5 < count++)
    {
      _display.show(formattedTime);
    }

    if (10 == count++)
    {
      DisplayGroup dg;
      dg.letter1 = BLANK;
      dg.letter2 = BLANK;
      dg.letter3 = formattedTime.letter3;
      dg.letter4 = formattedTime.letter4;
      _display.show(dg);

      count = 0;
    } */
  }

  while (digitalRead(_confirm_button))
  {
    delay(500);
  }

  while (!digitalRead(_confirm_button))
  {
    if (digitalRead(_edit_button))
    {
      _alarmTime.min = _alarmTime.min == 59 ? 0 : _alarmTime.min + 1;
      formattedTime = getFormattedTime(_alarmTime);

      // Serial.print("[updated] _alarmTime: ");
      // Serial.print(_alarmTime.hour);
      // Serial.print(":");
      // Serial.print(_alarmTime.min);
      // Serial.println();
      while (digitalRead(_edit_button))
      {
        delay(500);
      }
    }

    _display.show(formattedTime);

    /* if (5 < count++)
    {
      _display.show(formattedTime);
    }

    if (10 == count++)
    {
      DisplayGroup dg;
      dg.letter1 = formattedTime.letter1;
      dg.letter2 = formattedTime.letter2;
      dg.letter3 = BLANK;
      dg.letter4 = BLANK;
      _display.show(dg);

      count = 0;
    } */
  }

  while (digitalRead(_confirm_button))
  {
    delay(500);
  }

  _lastAlarmTime.hour = 24;
  _lastAlarmTime.min = 60;
}

bool Clock::isAlarmTime()
{
  bool isTime = _alarmTime.min == _currentTime.min &&
    _alarmTime.hour == _currentTime.hour &&
    _lastAlarmTime.min != _currentTime.min &&
    _lastAlarmTime.hour != _currentTime.hour;

  if (isTime)
  {
    _lastAlarmTime.hour = _currentTime.hour;
    _lastAlarmTime.min = _currentTime.min;
  }

  return isTime;
}

bool Clock::isHourlyUpdateTime()
{
  bool isTime = 10 == _currentTime.min &&
    _lastHourlyUpdateTime.hour != _currentTime.hour;

  if (isTime)
  {
    _lastHourlyUpdateTime.hour = _currentTime.hour;
  }

  return isTime;
}

bool Clock::isDailyUpdateTime()
{
  bool isTime = 8 == _currentTime.hour &&
    _lastDailyUpdateTime.day != _currentTime.day;

  if (isTime)
  {
    _lastDailyUpdateTime.day = _currentTime.day;
  }

  return isTime;
}

DisplayGroup Clock::getFormattedTime(datetimeInfo time)
{
  DisplayGroup dg;

  dg.letter1 = time.hour / 10;
  dg.letter2 = time.hour % 10;
  dg.letter3 = time.min / 10;
  dg.letter4 = time.min % 10;

  return dg;
}
