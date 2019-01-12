#ifndef ChartDownloader_h
#define ChartDownloader_h

#include <Arduino.h>
#include <LFlash.h>
#include <LSD.h>
#include <LStorage.h>
#include <LWiFi.h>
#include <LWiFiClient.h>
#include "ChartConfig.h"

class ChartDownloader
{
  public:
    ChartDownloader(char * api_host);
    void setup(char * ap_ssid, char * ap_password);
    void downloadHourlyChart();
    void downloadDailyChart();
  private:
    char * _api_host;
    LWiFiClient wifiClient;
    String getSoundUrl(ChartType type);
    void downloadSound(String url, char * download_filename);
};

#endif
