<?php

require_once 'bd.php';
require_once "/usr/local/lib/php/vendor/autoload.php";


session_start();

if( isset($_SESSION['nickUsuario'])) {
    $datosUsuario=getDatosUsuario($_SESSION['nickUsuario']);

}

header('Content-Type: application/json');


$palabraBusqueda=$_GET['busqueda'];

$_SESSION['busqueda']=$palabraBusqueda;

$resultados= array();

$resultados = getEventos($palabraBusqueda,$datosUsuario['tipo']);

echo(json_encode($resultados));

?>