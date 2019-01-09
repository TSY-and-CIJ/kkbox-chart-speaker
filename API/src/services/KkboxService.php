<?php

namespace App\services;

use KKBOX\KKBOXOpenAPI\OpenAPI;

class KkboxService
{
    const HOURLY_CHART_ID = 'LZPhK2EyYzN15dU-PT';

    private $clientID;
    private $clientSecret;
    private $openAPI;

    public function __construct($setting)
    {
        $this->clientID = $setting['settings']['KKBOX']['id'];
        $this->clientSecret = $setting['settings']['KKBOX']['secret'];
        $this->openAPI = new OpenAPI($this->clientID, $this->clientSecret);
    }

    public function fetchCPOPDailyChartInfo($limit = 10)
    {
        $this->openAPI->fetchAndUpdateAccessToken();
        $id = json_decode($this->openAPI->fetchCharts()->getBody(), true)['data'][0]['id'];
        return $this->fetchPlaylistById($id, $limit);
    }

    public function fetchHourlyChart($limit = 10)
    {
        $this->openAPI->fetchAndUpdateAccessToken();
        return $this->fetchPlaylistById(self::HOURLY_CHART_ID, $limit);
    }

    private function fetchPlaylistById($id, $limit)
    {
        $this->openAPI->fetchAndUpdateAccessToken();
        $info = json_decode($this->openAPI->fetchPlaylist($id)->getBody(), true);

        return [
            'title' => $info['title'],
            'updated_at' => $info['updated_at'],
            'songs' => array_slice($info['tracks']['data'], 0, $limit, true),
        ];
    }
}
