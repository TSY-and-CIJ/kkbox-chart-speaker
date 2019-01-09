<?php

use Slim\Http\Request;
use Slim\Http\Response;
use App\Controllers\MainController;

// Routes

$app->get('/', function (Request $request, Response $response, array $args) {
    return $this->renderer->render($response, 'index.phtml', $args);
});

$app->get('/daily-chart', MainController::class . ':fetchDailyChart');
$app->get('/hourly-chart', MainController::class . ':fetchHourlyChart');
