<?php

namespace App\Controllers;

use App\services\ContentService;
use App\Services\TTSService;
use App\services\KkboxService;

class MainController
{
    private $settings;
    private $TTSService;
    private $kkboxService;
    private $contentService;

    public function __construct()
    {
        $this->settings = require __DIR__ . '/../settings.php';
        $this->TTSService = new TTSService($this->settings);
        $this->kkboxService = new KkboxService($this->settings);
        $this->contentService = new ContentService();
    }

    public function fetchDailyChart()
    {
        $dailyChartInfo = $this->kkboxService->fetchCPOPDailyChartInfo();
        $content = $this->contentService->getChartContent($dailyChartInfo);
        echo $this->TTSService->fetchTTSUrl($content);
    }

    public function fetchHourlyChart()
    {
        $hourlyChartInfo = $this->kkboxService->fetchHourlyChart(5);
        $content = $this->contentService->getChartContent($hourlyChartInfo, true);
        echo $this->TTSService->fetchTTSUrl($content);
    }
}
