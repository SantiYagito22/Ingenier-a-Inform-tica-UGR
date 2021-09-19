<?php
    require_once "/usr/local/lib/php/vendor/autoload.php";
    include("bd.php");


    $loader = new \Twig\Loader\FilesystemLoader('templates');
    $twig = new \Twig\Environment($loader);


    $coment = getTodosComentarios();

    $malasPalabras = getPalabrotas();
    if($malasPalabras === null)
    {
        die("Fallo en la base de datos, sentencia fallida");
    }

    session_start();
    if( isset($_SESSION['nickUsuario'])) {
        $datosUsuario=getDatosUsuario($_SESSION['nickUsuario']);

        if($_SERVER['REQUEST_METHOD'] === 'POST'){

            if($_POST['submit1'] === "MODIFICAR COMENTARIO" ){
                $idComentario= $_POST['idComentario2'];
                $textoACambiar= $_POST['comentario'];
                 if(!empty($textoACambiar))
                 {
                     cambiarComentario($idComentario,$textoACambiar);
                     header("Location: comentarios.php");
                 }
                 else{
                     $errores[] ="No puedes cambiar un comentario a nada";
                     }
            }
            else if($_POST['submit3'] === "borrar")
            {
                $idComentario= $_POST['idComentario'];
                borrarComentario($idComentario);
                header("Location: comentarios.php");
                
            }
        }
    }
    echo $twig->render('comentarios.html', ['errores' => $errores, 'datosUsuario' => $datosUsuario, 'comentario' => $coment])
?>



<script> var insultos = <?php echo json_encode($malasPalabras); ?>; </script>