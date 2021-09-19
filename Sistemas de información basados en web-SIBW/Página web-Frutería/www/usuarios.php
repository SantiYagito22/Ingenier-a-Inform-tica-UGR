<?php
require_once "/usr/local/lib/php/vendor/autoload.php";

$loader = new \Twig\Loader\FilesystemLoader('templates');
$twig = new \Twig\Environment($loader);

require_once 'bd.php';

$errores=array();

$usuarios= getUsuarios();

session_start();
if( isset($_SESSION['nickUsuario'])) {

    if($_SERVER['REQUEST_METHOD'] === 'POST')
    {
        $nombreUsuario = $_POST['nombreUsuario'];
        $tipo= strtolower($_POST['tipoUsuario']);
        $usuarioAcambiar=getDatosUsuario($nombreUsuario);

        if(empty($tipo))
        {
            $errores[] ="No puedes cambiar el tipo de ".$nombreUsuario." a nada";
        }
        else if($tipo===$usuarioAcambiar['tipo'])
        {
            
            $errores[] ="El usuario ".$nombreUsuario." ya es del tipo ".$tipo;
        }
        else if($usuarioAcambiar['tipo']==='super' and $tipo!='super') 
        {
            if(hayMasDeUnSuperusuario()>=2)
            {
                actualizarTipo($nombreUsuario,$tipo);
                header("Location: index.php");
            }
            else
            {
                $errores[]="El usuario ".$nombreUsuario." no puede dejar de ser super ya que es el unico del sistema";
            }
        }
        else{
            actualizarTipo($nombreUsuario,$tipo);
            header("Location: usuarios.php");
        }
    }

}

echo $twig->render('usuarios.html', ['errores' => $errores, 'usuarios' => $usuarios])
?>