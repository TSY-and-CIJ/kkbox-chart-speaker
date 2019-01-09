<?php
$envFile = __DIR__ . '/../.env';

if (file_exists($envFile)) {
    $fp = fopen($envFile, 'r');
    while ($line = fgets($fp)) {
        putenv(trim($line));
    }
    fclose($fp);
}

return [
    'settings' => [
        'displayErrorDetails' => true, // set to false in production
        'addContentLengthHeader' => false, // Allow the web server to send the content-length header

        // Renderer settings
        'renderer' => [
            'template_path' => __DIR__ . '/../templates/',
        ],

        // Monolog settings
        'logger' => [
            'name' => 'slim-app',
            'path' => isset($_ENV['docker']) ? 'php://stdout' : __DIR__ . '/../logs/app.log',
            'level' => \Monolog\Logger::DEBUG,
        ],

        // TTS info
        'TTS' => [
            'account' => getenv('TTS_ACCOUNT', 'account'),
            'password' => getenv('TTS_PASSWORD', 'password'),
        ],
    ],
];
