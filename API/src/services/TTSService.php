<?php

namespace App\Services;

class TTSService
{
    const TTS_Web_Service_Server = 'http://tts.itri.org.tw/TTSService/Soap_1_3.php?wsdl';

    const STATUS_COMPLETED_CODE = 2;
    const RESULT_SUCCESS_CODE = 0;

    private $account;
    private $password;
    private $client;

    public function __construct($settings)
    {
        $this->account = $settings['settings']['TTS']['account'];
        $this->password = $settings['settings']['TTS']['password'];
        $this->client = new \SoapClient(self::TTS_Web_Service_Server);
    }

    public function convert($text)
    {
        $result = $this->client->ConvertSimple($this->account, $this->password, $text);

        list($resultCode, $resultString, $resultConvertID) = explode("&", $result);

        return [
            'code' => $resultCode,
            'id' => $resultConvertID
        ];
    }

    public function getConvertStatus($id)
    {
        $result = $this->client->GetConvertStatus($this->account, $this->password, $id);

        list($resultCode, $resultString, $statusCode, $status) = explode("&",$result);

        return [
            'code' => $resultCode,
            'status' => $statusCode,
        ];
    }

    public function getConvertUrl($id)
    {
        $result = $this->client->GetConvertStatus($this->account, $this->password, $id);
        list($resultCode, $resultString, $statusCode, $status, $url) = explode("&",$result);
        return $url;
    }
}
