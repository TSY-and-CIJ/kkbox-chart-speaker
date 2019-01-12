#include <LAudio.h>
#include <LSD.h>
#include "Speaker.h"
#include "ChartConfig.h"
#include "DisplayConfig.h"

#define VOL 4

#define FILE_0 "0.wav"
#define FILE_1 "1.wav"
#define FILE_2 "2.wav"
#define FILE_3 "3.wav"
#define FILE_4 "4.wav"
#define FILE_5 "5.wav"
#define FILE_6 "6.wav"
#define FILE_7 "7.wav"
#define FILE_8 "8.wav"
#define FILE_9 "9.wav"
#define FILE_10 "10.wav"
#define FILE_NOW_TIME "now_time.wav"
#define FILE_HOUR "hour.wav"
#define FILE_MIN "minute.wav"

char * number_files[10] = {FILE_0, FILE_1, FILE_2, FILE_3, FILE_4, FILE_5, FILE_6, FILE_7, FILE_8, FILE_9};

Speaker::Speaker() {}

void Speaker::setup()
{
  LSD.begin();
  LAudio.begin();
  LAudio.setVolume(VOL);
}

void Speaker::playHourlyChart()
{
  playChart(HOURLY);
}

void Speaker::playDailyChart()
{
  playChart(DAILY);
}

void Speaker::playNowTime(DisplayGroup group)
{
  playSound(FILE_NOW_TIME);

  byte word[] = {group.letter1, group.letter2, group.letter3, group.letter4};

  for(int i = 0; i < 4; i++)
  {
    // 0 不發聲
    if (word[i] == 0)
    {
      if (i != 1 || word[0] != 0) {
        continue;
      }
    }

    if ((i != 0 || i != 2) || word[i] != 1)
    {
      playSound(number_files[word[i]]);
    }

    if (i == 0 || i == 2)
    {
      playSound(FILE_10);
    }

    if (i == 1)
    {
      playSound(FILE_HOUR);
    }

    if (i == 3)
    {
      playSound(FILE_MIN);
    }
  }
}

void Speaker::playChart(ChartType type)
{
  char * file = type == HOURLY ? (char *)FILE_NAME_HOURLY : (char *)FILE_NAME_DAILY;
  playSound(file);
}

void Speaker::playSound(char * file)
{
  LAudio.playFile(storageSD, file);

  AudioStatus status;
  do
  {
    status = LAudio.getStatus();
    delay(500);
  } while (status != AudioEndOfFile);
}
