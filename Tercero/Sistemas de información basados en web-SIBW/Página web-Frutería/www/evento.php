<?php
    require_once "/usr/local/lib/php/vendor/autoload.php";
    include("bd.php");


    $loader = new \Twig\Loader\FilesystemLoader('templates');
    $twig = new \Twig\Environment($loader);

    $busqueda;

    function pasarPalabra($palabraBusqueda){
        global $busqueda;
        $busqueda=$palabraBusqueda;
    }
   
    $errores=array();
    
    if( isset($_GET['ev'])){
        $idEv= $_GET['ev'];
    }
    else{
        $idEv= -1;
    }

    $evento = getEvento($idEv);

    if($evento === null)
    {
        die("Error evento no reconocido. Este evento no consta en nuestra web, pruebe con otro.");
    }

    $imagen = getImagen($idEv);
   

    $coment = getComentarios($idEv);
   
    
    $malasPalabras = getPalabrotas();
    if($malasPalabras === null)
    {
        die("Fallo en la base de datos, sentencia fallida");
    }

    $etiquetas = getEtiquetas($idEv);

    


    $aux=$idEv;
    settype($aux,'string');
    $aux2= "./imprimir.php?ev=";
    $rutaImpr= $aux2.$aux;


    session_start();

    $palabraBusqueda=$_SESSION['busqueda'];
    $_SESSION['busqueda']="";

    if(!empty($palabraBusqueda))
    {
        $evento['nombre']=resaltar($evento['nombre'],$palabraBusqueda);
        $evento['eslogan']=resaltar($evento['eslogan'],$palabraBusqueda);
        $evento['fecha']=resaltar($evento['fecha'],$palabraBusqueda);
        $evento['descripcion']=resaltar($evento['descripcion'],$palabraBusqueda);
    }
   
    
    if( isset($_SESSION['nickUsuario'])) {
        $datosUsuario=getDatosUsuario($_SESSION['nickUsuario']);


        if($_SERVER['REQUEST_METHOD'] === 'POST'){
            

           if($_POST['submit1'] === "ENVIAR COMENTARIO")
           {
            $comentario = $_POST['comentario'];
            
            $fechaComentario=getTextoFecha();
            
            if(!empty($comentario))
            {
                
                comentar($_SESSION['nickUsuario'],$fechaComentario,$comentario,$idEv);
                header("Location: evento.php?ev=".$aux);
            }
            else{
                $errores[] ="No se ha subido el comentario anterior, tienes que escribir algo para poder comentar";
            }
            
            } 
            else if($_POST['submit1'] === "MODIFICAR COMENTARIO" ){
               $idComentario= $_POST['idComentario2'];
               $textoACambiar= $_POST['comentario'];
                if(!empty($textoACambiar))
                {
                    cambiarComentario($idComentario,$textoACambiar);
                    header("Location: evento.php?ev=".$aux);
                }
                else{
                    $errores[] ="No puedes cambiar un comentario a nada";
                }
               
               
               
               
            }
            else if($_POST['submit3'] === "borrar")
            {
                $idComentario= $_POST['idComentario'];
                borrarComentario($idComentario);
                header("Location: evento.php?ev=".$aux);
                
            }
            else if($_POST['submit4'] === "eliminar")
            {
                eliminarEvento($idEv);
                header("Location: index.php");
            }
            else if($_POST['submit5'] === "editar")
            {
               
                header("Location: modificarEvento.php?ev=".$aux);
            }
            else if($_POST['submit6'] === "publicar")
            {
                cambiarVisibilidad(1,$idEv);
                header("Location: index.php");
            }
            else if($_POST['submit7'] === "ocultar")
            {
                cambiarVisibilidad(0,$idEv);
                header("Location: index.php");
            }
            

        }

        
        
    }

    



    echo $twig->render('evento.html', ['evento' => $evento, 'imagen' => $imagen, 'comentario' => $coment, 'rutaImprimir' => $rutaImpr, 'malasPalabras' => $malasPalabras, 'datosUsuario' => $datosUsuario , 'errores' => $errores, 'etiquetas' => $etiquetas]  );
?>


<script> var insultos = <?php echo json_encode($malasPalabras); ?>; </script>