<?php

namespace App\services;

class ContentService
{
    public function getChartContent($chartInfo, $isHourlyChart = false)
    {
        $chartTitle = $this->chartTitle($chartInfo, $isHourlyChart);
        $chart = $this->chart($chartInfo);
        return $chartTitle . $chart;
    }

    private function chartTitle($chartInfo, $isHourlyChart = false)
    {
        $dateTime = new \DateTime($chartInfo['updated_at'], new \DateTimeZone('UTC'));
        $dateTime->setTimezone(new \DateTimeZone("Asia/Taipei"));

        if ($isHourlyChart) {
            $dateTime->modify("- 1 hour");
        } else {
            $dateTime->modify("- 1 day");
        }

        return sprintf("登～等～登登登～為您播報%s年%s月%s日%s的%s。",
            $dateTime->format('Y'),
            $dateTime->format('m'),
            $dateTime->format('d'),
            $isHourlyChart ? $dateTime->format('H') .'點' : '',
            $chartInfo['title']
        );
    }

    private function chart($chartInfo)
    {
        $string = "";
        foreach (array_reverse($chartInfo['songs'], true) as $index => $song) {
            $rank = $index + 1;

            if (5 === $rank) {
                $string .= "登等~登登登～ TA TA Top Five!";
            }

            if (10 === $rank) {
                $string .= "等登登～ TA TA Top Ten!";
            }

            $string .= "第{$rank}名，{$song['album']['artist']['name']}，{$song['name']}。。。";
        }

        return $string;
    }
}
