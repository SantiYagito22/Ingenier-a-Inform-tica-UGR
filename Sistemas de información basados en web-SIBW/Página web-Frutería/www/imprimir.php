<?php

require_once "/usr/local/lib/php/vendor/autoload.php";
include("bd.php");

$loader = new \Twig\Loader\FilesystemLoader('templates');
$twig = new \Twig\Environment($loader);


if(!is_numeric($_GET['ev'])){
    die("Error evento no reconocido. Este evento no consta en nuestra web, pruebe con otro.");
  }
if( isset($_GET['ev'])){
    $idEv= $_GET['ev'];
}
else{
    $idEv= -1;
}

$evento = getEvento($idEv);
$imagen = getImagen($idEv);
$coment = getComentarios($idEv);

session_start();

if( isset($_SESSION['nickUsuario'])) {
    $datosUsuario=getDatosUsuario($_SESSION['nickUsuario']);
}








echo $twig->render('Evento_imprimir.html', ['evento' => $evento, 'imagen' => $imagen, 'comentario' => $coment, 'datosUsuario' => $datosUsuario ] );


?>
