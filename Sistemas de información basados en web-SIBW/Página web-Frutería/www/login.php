<?php
require_once "/usr/local/lib/php/vendor/autoload.php";

$loader = new \Twig\Loader\FilesystemLoader('templates');
$twig = new \Twig\Environment($loader);

require_once 'bd.php';


$errores=array();
if($_SERVER['REQUEST_METHOD'] === 'POST'){
    $user = $_POST['nombreUsuario'];
    $pass = $_POST['contraseña'];

    
    if(empty($user) and empty($pass))
    {
        
        $errores[] ="Debes rellenar todos los campos";
        
    }
    else if(empty($user))
    {
        
        $errores[] ="Debe rellenar el campo de usuario";
    }
    else if(empty($pass)){
        $errores[] ="Debe rellenar el campo de contraseña";
        
    }
    else if(checkLogin($user,$pass)){
        session_start();
        
        $_SESSION['nickUsuario'] = $user;

        header("Location: index.php");
    }
    else
    {
        $errores[] ="Nombre de usuario o contraseña incorrecto";
    }
    
    

    
}

echo $twig->render('identificacion.html', ['errores' => $errores])



?>