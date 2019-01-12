# KKBOX Chart Speaker
Demo 影片：https://youtu.be/AjD9IsPjwqc   
<a href="https://youtu.be/AjD9IsPjwqc"><img src="https://github.com/TSY-and-CIJ/kkbox-chart-speaker/blob/master/thumbnail.png" height="240"></a>

## 功能簡介
* 顯示當前時間
* 播報 KKBOX 新歌即時榜
* 播報 KKBOX 華語單曲日榜
* 指定時間播報

## 使用的外部服務
* [KKBOX Open API](https://docs-zhtw.kkbox.codes/docs)
* [工研院文字轉語音Web服務](http://tts.itri.org.tw/index.php)

## 系統架構

<img src="https://github.com/TSY-and-CIJ/kkbox-chart-speaker/blob/master/system.png" height="240">

使用開發版處理所有邏輯十分耗時，因此另外架設 API 處理外部服務的資料，加快處理的速度。

## 取榜流程
* 啟動：取日榜、即時榜
* 每小時 10 分：取即時榜
* 每日 8 點：取日榜

## API 端

* Language：php
* Framework：Slim Framework
* Cloud Application Platform：Heroku   
  (將開發好的內容 merge 至 deploy branch 即可自動 deploy 至 Heroku。)


### Routes

* `daily-chart`：取得最新華語日榜的語音檔
* `hourly-chart`：取得綜合新歌即時榜的語音檔

### 環境建置

#### 環境變數

名稱 | 說明
------------ | -------------
TTS_ACCOUNT | 工研院文字轉語音Web服務帳號
TTS_PASSWORD | 工研院文字轉語音Web服務密碼
KKBOX_ID | KKBOX Open API ID
KKBOX_SECRET | KKBOX Open API Secret

#### Local 建置方法

複製 env example 檔案，在 `.env` 檔將需要的 id / secret 填入。
```
cp .env.example .env
```

#### Heroku 建置方法

於 Heroku 的 `Config Vars` 將環境變數加上。


## 開發板端
#### 開發板與其他設備
* Linkit ONE
  * 鋰電池   
  * Wi-Fi與藍牙天線   
* 喇叭
* 4 位 7 段顯示器
* 按鈕 x 2

#### 線路圖

<img src="https://github.com/TSY-and-CIJ/kkbox-chart-speaker/blob/master/schematic.png" height="360">

#### 環境設置
於`kkbox_chart_speaker.ino`中：  

名稱 | 說明
------------ | -------------
AP_SSID | 無線基地台 SSID
AP_PASSWORD | 無線基地台密碼
API_HOST | 架設的 API URL
