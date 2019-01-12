#include <Arduino.h>
#include <LFlash.h>
#include <LSD.h>
#include <LStorage.h>
#include <LWiFi.h>
#include <LWiFiClient.h>
#include "ChartDownloader.h"
#include "ChartConfig.h"

#define API_URI_HOURLY "/hourly-chart"
#define API_URI_DAILY "/daily-chart"

#define TTS_HOST "tts.itri.org.tw"

#define TEMP_BUF_SIZE 2048

ChartDownloader::ChartDownloader(char * api_host)
{
  _api_host = api_host;
}

void ChartDownloader::setup(char * ap_ssid, char * ap_password)
{
  LSD.begin();
  LWiFi.begin();

  // Serial.println("Connect AP");
  while (0 == LWiFi.connect(ap_ssid, LWiFiLoginInfo(LWIFI_WPA, ap_password)))
  {
    delay(1000);
  }
  // Serial.println("Connected!");
}

void ChartDownloader::downloadHourlyChart()
{
  String fileUrl = getSoundUrl(HOURLY);
  downloadSound(fileUrl, FILE_NAME_HOURLY);
  // Serial.println("Hourly chart is downloaded!");
}

void ChartDownloader::downloadDailyChart()
{
  String fileUrl = getSoundUrl(DAILY);
  downloadSound(fileUrl, FILE_NAME_DAILY);
  // Serial.println("Daily chart is downloaded!");
}

String ChartDownloader::getSoundUrl(ChartType type)
{
  // Serial.println("Connect to API");
  while (0 == wifiClient.connect(_api_host, 80))
  {
    // Serial.println("Reconnect");
    delay(1000);
  }
  // Serial.println("Connected!");

  String type_name = type == HOURLY ? "hourly chart" : "daily chart";
  String api_uri = type == HOURLY ? API_URI_HOURLY : API_URI_DAILY;

  String temp = _api_host;

  // Serial.println("Get " + type_name);
  wifiClient.println("GET " + api_uri + " HTTP/1.1");
  wifiClient.println("Host: " + temp);
  wifiClient.println("Connection: close");
  wifiClient.println();

  // Serial.println("Waiting response...");
  while (!wifiClient.available())
  {
    delay(100);
  }

  String sound_url = "";

  while (wifiClient)
  {
    int v = wifiClient.read();
    if (v != -1)
    {
      char c = (char)v;
      sound_url += c;
      // Serial.print(c);

      if (sound_url.endsWith("http://"))
      {
        sound_url = "http://";
      }

      if (sound_url.endsWith(".wav"))
      {
        wifiClient.stop();
        break;
      }
    }
  }

  return sound_url;
}

void ChartDownloader::downloadSound(String url, char * download_filename)
{
  url.replace("http://tts.itri.org.tw", "");

  // Serial.println("Connect to TTS");
  while (0 == wifiClient.connect(TTS_HOST, 80))
  {
    // Serial.println("Reconnect");
    delay(1000);
  }

  // Serial.println("GET " + url);
  wifiClient.println("GET " + url + " HTTP/1.0");
  wifiClient.println("User-Agent: Wget/1.11.4");
  wifiClient.println("Accept: */*");
  wifiClient.println("Host: " TTS_HOST);
  wifiClient.println("Connection: Close");
  wifiClient.println();

  // Serial.println("Waiting response...");

  int peekByte = -1;
  while (peekByte == -1 && wifiClient.connected())
  {
    peekByte = wifiClient.peek();
    delay(200);
  }

  // Serial.println("Skip header:");

  int lineFeedCount = 0;
  while (lineFeedCount < 2)
  {
    int value = wifiClient.read();
    if (value == -1)
    {
      delay(10);
      continue;
    }

    // Serial.print((char)value);

    if (value == '\r')
    {
      value = -1;
      while (value == -1)
      {
        value = wifiClient.read();
        // Serial.print((char)value);
      }

      if (value == '\n')
      {
        lineFeedCount++;
      }
      else
      {
        lineFeedCount = 0;
      }
    }
    else
    {
      lineFeedCount = 0;
    }
  }

  if (LSD.exists(download_filename))
  {
    // Serial.println("Delete existing file");
    LSD.remove(download_filename);
  }

  // Serial.println("Start download file");

  int totalSize = 0;
  uint8_t buf[TEMP_BUF_SIZE] = {0};
  LFile f = LSD.open(download_filename, FILE_WRITE);
  while (wifiClient.connected())
  {
    size_t bytesRead = wifiClient.read(buf, TEMP_BUF_SIZE);
    if (bytesRead)
    {
      const size_t bytesWrite = f.write((const uint8_t *)&buf[0], (size_t)bytesRead);

      totalSize += bytesWrite;
      // Serial.print("\r");
      // Serial.print(totalSize);
      // Serial.print(" bytes");
    }
    delay(100);
  }
  f.flush();
  f.close();
  // Serial.println();
  // Serial.println("Download finished!");
}
