<?php

require('../vendor/autoload.php');
//require('/high_score_storage.txt');




$app = new Silex\Application();
$app['debug'] = true;

$high_socre = 0;

$dbopts = parse_url(getenv('DATABASE_URL'));
$app->register(new Csanquer\Silex\PdoServiceProvider\Provider\PDOServiceProvider('pdo'),
               array(
                'pdo.server' => array(
                   'driver'   => 'pgsql',
                   'user' => $dbopts["user"],
                   'password' => $dbopts["pass"],
                   'host' => $dbopts["host"],
                   'port' => $dbopts["port"],
                   'dbname' => ltrim($dbopts["path"],'/')
                   )
               )
);

// Register the monolog logging service
$app->register(new Silex\Provider\MonologServiceProvider(), array(
  'monolog.logfile' => 'php://stderr',
));

// Register view rendering
$app->register(new Silex\Provider\TwigServiceProvider(), array(
    'twig.path' => __DIR__.'/views',
));

// Our web handlers

$app->get('/', function() use($app) {
  $app['monolog']->addDebug('home');
  return $app['twig']->render('home.html');
});

$app->get('/home', function() use($app) {
  $app['monolog']->addDebug('home');
  return $app['twig']->render('home.html');
});

$app->get('/contact', function() use($app) {
  $app['monolog']->addDebug('contact');
  return $app['twig']->render('contact.html');
});

$app->get('/cowsay', function() use($app) {
  $app['monolog']->addDebug('cowsay');
  return "<pre>".\Cowsayphp\Cow::say("Cool beans")."</pre>";
});

$app->get('/CV2021_eng.pdf', function() use($app) {
  $app['monolog']->addDebug('cowsay');
  return $app['twig']->render('CV2021_eng.pdf');
});

$app->get('/oj', function() use($app) {
  $app['monolog']->addDebug('olli');
  return $app['twig']->render('olli.html');
});

$app->get('/qml', function() use($app) {
  $app['monolog']->addDebug('qml');
  return $app['twig']->render('qml.html');
});

$app->get('/python', function() use($app) {
  $app['monolog']->addDebug('python');
  return $app['twig']->render('python.html');
});

$app->get('/android', function() use($app) {
  $app['monolog']->addDebug('android');
  return $app['twig']->render('android.html');
});

$app->get('/cv', function() use($app) {
  $app['monolog']->addDebug('cv');
  return $app['twig']->render('cv.html');
});

$app->get('/secretpathforhighscore', function() use($app) {

  $st = $app['pdo']->prepare('SELECT MAX(score) as score FROM high_score');
  $st->execute();

  $scores = array();
  while ($row = $st->fetch(PDO::FETCH_ASSOC)) {
    $app['monolog']->addDebug('Row ' . $row['score']);
    $scores[] = $row;
  }

  return $scores[0]['score'];
  
/*

  //global $high_socre;
  $app['monolog']->addDebug('secretpathforhighscore');

  // read high score, locking for safe concurrent use
  $f = fopen('high_score_storage.txt', "r");

  return "999";
  //flock($f, LOCK_EX);
  $high_socre = fread($f, filesize('high_score_storage.txt'));
  //flock($f, LOCK_UN);
  fclose($f); 

  return $high_socre; */
});

use Symfony\Component\HttpFoundation\Request;
use Symfony\Component\HttpFoundation\ParameterBag;

$app->before(function (Request $request) {
    if (0 === strpos($request->headers->get('Content-Type'), 'application/json')) {
        $data = json_decode($request->getContent(), true);
        $request->request->replace(is_array($data) ? $data : array());
    }
});

use Symfony\Component\HttpFoundation\Response;

$app->post('/secretpathforhighscore', function (Request $request) use($app) {
  //global $high_socre;
  $password = "JerusaleminPalmu2020";
  $message = "OJ";
  $message = $request->request->get('msgg');
  $pos = strpos($message, $password);
  $response_message = "";
  $status = 200;


  if ($pos === false) {
    $response_message = "password incorrect. password: $password, message: $message??end.";
    $status = 400;
  } else {
    $high_socre = intval((substr($message, (strlen($password)-1), (strlen($message)-1))));

    $sql_statement = 'INSERT INTO high_score VALUES ('.$high_socre.');';

    $st = $app['pdo']->prepare($sql_statement);
    $st->execute();
    //$st = $app['pdo']->prepare('INSERT INTO high_score VALUES ($high_socre)');
    //$st->execute();
  

    // write new high score, locking for safe concurrent use
    /*
    $f = fopen('/high_score_storage.txt', 'wa+');
    flock($f, LOCK_EX);
    fwrite($f, $high_socre);
    flock($f, LOCK_UN);
    fclose($f); */
  
    $response_message = "High score updated".strval($high_socre);
  }

  return new Response($response_message, $status);
});


$app->get('/react', function() use($app) {
  $app['monolog']->addDebug('react');
  return $app['twig']->render('react.html');
});


$app->run();
