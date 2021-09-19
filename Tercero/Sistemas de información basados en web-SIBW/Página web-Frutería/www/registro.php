<?php
require_once "/usr/local/lib/php/vendor/autoload.php";

$loader = new \Twig\Loader\FilesystemLoader('templates');
$twig = new \Twig\Environment($loader);

require_once 'bd.php';

$errores=array();

if($_SERVER['REQUEST_METHOD'] === 'POST'){
    $user= $_POST['usuario'];
    $pass = $_POST['password'];
    $nombre = $_POST['nombreCompleto'];
    $correo = $_POST['correo'];

    if(empty($user) and empty($pass) and empty($nombre) and empty($correo))
    {
        
        $errores[] ="Debes rellenar todos los campos";
        
    }
    else if(empty($nombre))
    {
        $errores[] ="Debes rellenar el campo de nombre completo";
    }
    else if(empty($correo))
    {
        $errores[] ="Debes rellenar el campo de correo electronico";
    }
    else if(!filter_var($correo, FILTER_VALIDATE_EMAIL))
    {
        $errores[] ="El formato de correo electronico es incorrecto";
    }
    else if(empty($user))
    {
        $errores[] ="Debes rellenar el campo de nombre de usuario";
    }
    else if(empty($pass))
    {
        $errores[] ="Debes rellenar el campo de contraseña";
    }
    else if(!checkRegistro($user))
    {
        if(Registrar($user,$pass,$nombre,$correo)){
            session_start();
            $_SESSION['nickUsuario'] = $user;
            header("Location: index.php");
        }
        else{
            $errores[] ="Fallo en el sistema.";
        }
    }
    else{
        $errores[] ="El usuario ya se encuentra registrado en el sistema";
    }
    

}
echo $twig->render('registro.html', ['errores' => $errores])




?>