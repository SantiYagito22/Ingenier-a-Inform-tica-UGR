<?php
require_once "/usr/local/lib/php/vendor/autoload.php";

$loader = new \Twig\Loader\FilesystemLoader('templates');
$twig = new \Twig\Environment($loader);

require_once 'bd.php';
$errores=array();

session_start();
if( isset($_SESSION['nickUsuario'])) {
    $datosUsuario=getDatosUsuario($_SESSION['nickUsuario']);
}

if($_SERVER['REQUEST_METHOD'] === 'POST'){
    
    
    $nombre=$_POST['nombreCompleto'];
    $pass=$_POST['password'];
    $correo=$_POST['correo'];
    
    $usuario=$_POST['usuario'];

    if(empty($nombre))
    {
        $errores[] ="No puedes cambiar tu nombre a nada";
    }
    else if(empty($correo))
    {
        $errores[] ="No puedes cambiar el correo electrónico a nada";
    }
    else if(!filter_var($correo, FILTER_VALIDATE_EMAIL))
    {
        $errores[] ="El formato de correo electronico es incorrecto";
    }
    else if(empty($usuario))
    {
        $errores[] ="No puedes cambiar el nombre de usuario a nada";
    }
    
    else if(cambiarDatos($nombre,$pass,$correo,$usuario,$_SESSION['nickUsuario']))
    {
        $_SESSION['nickUsuario'] = $usuario;
        
        header("Location: modificar.php",);
    }
    else{
        $errores[] ="El nombre de usuario al que quieres cambiar ya existe en el sistema";
    }
    

    
}
    

    


echo $twig->render('modificar.html', ['datosUsuario' => $datosUsuario, 'errores' => $errores])



?>