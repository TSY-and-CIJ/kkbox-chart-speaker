#ifndef Speaker_h
#define Speaker_h

#include <LAudio.h>
#include <LSD.h>
#include "ChartConfig.h"
#include "DisplayConfig.h"

class Speaker
{
  public:
    Speaker();
    void setup();
    void playHourlyChart();
    void playDailyChart();
    void playNowTime(DisplayGroup word);
  private:
    void playChart(ChartType type);
    void playSound(char * file);
};

#endif
