# KKBOX Chart Speaker
Demo 影片：

## 功能簡介
* 顯示當前時間
* 播報 KKBOX 新歌即時榜
* 播報 KKBOX 華語單曲日榜
* 指定時間播報

## 使用的外部服務
* [KKBOX Open API](https://docs-zhtw.kkbox.codes/docs)
* [工研院文字轉語音Web服務](http://tts.itri.org.tw/index.php)

## 系統架構

## 運行流程

## API 端

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
