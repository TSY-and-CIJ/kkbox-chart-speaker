#include <Arduino.h>
#include "Clock.h"
#include "ChartDownloader.h"
#include "Speaker.h"

#define BUTTON1_PIN A0
#define BUTTON2_PIN A1

#define AP_SSID "AP_SSID"
#define AP_PASSWORD "AP_PASSWORD"

#define API_HOST "API_HOST"

Clock clock(BUTTON1_PIN, BUTTON2_PIN);
ChartDownloader chartDownloader(API_HOST);
Speaker speaker;

short count = 0;

void setup()
{
  // Serial.begin(115200);
  // Serial.println("Chart Speaker Start!");

  pinMode(BUTTON1_PIN, INPUT);
  pinMode(BUTTON2_PIN, INPUT);

  clock.setup();
  chartDownloader.setup(AP_SSID, AP_PASSWORD);
  speaker.setup();

  chartDownloader.downloadHourlyChart();
  chartDownloader.downloadDailyChart();
}

void loop()
{
  clock.updateTime();

  if (clock.isAlarmTime())
  {
    speaker.playNowTime(clock.getFormattedCurrentTime());
    speaker.playDailyChart();
  }

  if (clock.isHourlyUpdateTime())
  {
    chartDownloader.downloadHourlyChart();
  }

  if (clock.isDailyUpdateTime())
  {
    chartDownloader.downloadDailyChart();
  }

  if (digitalRead(BUTTON1_PIN))
  {
    speaker.playNowTime(clock.getFormattedCurrentTime());
    speaker.playHourlyChart();
  }

  if (digitalRead(BUTTON2_PIN))
  {
    clock.enterSetAlarmMode();
  }
}
