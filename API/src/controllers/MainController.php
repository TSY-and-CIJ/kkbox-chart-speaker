<?php

namespace App\Controllers;

use App\Services\TTSService;

class MainController
{
    private $settings;
    private $TTSService;

    public function __construct()
    {
        $this->settings = require __DIR__ . '/../settings.php';
        $this->TTSService = new TTSService($this->settings);
    }

    public function fetchTTSUrl($text)
    {
        $info = $this->TTSService->convert($text);
        $convertId = $info['id'];
        $status = 0;

        // retry 到音檔完成
        while (TTSService::STATUS_COMPLETED_CODE !== $status) {
            $result = $this->TTSService->getConvertStatus($convertId);
            $status = (int) $result['status'];
        }

        return $this->TTSService->getConvertUrl($convertId);
    }
}
