<?php
    require_once "/usr/local/lib/php/vendor/autoload.php";

    $loader = new \Twig\Loader\FilesystemLoader('templates');
    $twig = new \Twig\Environment($loader);

    $datosUsuario = [];

    require_once 'bd.php';


    $eventosInicio= getEventosInicio();

    session_start();

    if( isset($_SESSION['nickUsuario'])) {
        $datosUsuario=getDatosUsuario($_SESSION['nickUsuario']);

    }

    
    echo $twig->render('index.html', ['datosUsuario' => $datosUsuario, 'eventosInicio' => $eventosInicio]);
    
?>