<?php
require_once "/usr/local/lib/php/vendor/autoload.php";

$loader = new \Twig\Loader\FilesystemLoader('templates');
$twig = new \Twig\Environment($loader);

require_once 'bd.php';

$datosUsuario = [];
$errores=array();
session_start();

if( isset($_SESSION['nickUsuario'])) {
    $datosUsuario=getDatosUsuario($_SESSION['nickUsuario']);
}

if($_SERVER['REQUEST_METHOD'] === 'POST'){

    if($_POST['submit1'] == "Eliminar cuenta")
    {
        if($datosUsuario['tipo']==='super' and hayMasDeUnSuperusuario()>=2)
        {
            eliminarCuenta($_SESSION['nickUsuario']);
            header("Location: logout.php");
        }
        else{
            $errores[]="No puedes eliminar tu cuenta ya que eres el unico superusuario";
        }
        
    }
    else if($_POST['submit2'] == "Modificar datos")
    {
        header("Location: modificar.php");
    }
}

echo $twig->render('perfil.html', ['errores' => $errores,'datosUsuario' => $datosUsuario]);



?>