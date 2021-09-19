<?php
require_once "/usr/local/lib/php/vendor/autoload.php";

$loader = new \Twig\Loader\FilesystemLoader('templates');
$twig = new \Twig\Environment($loader);

require_once 'bd.php';


$errores=array();

$idEv=-1;
session_start();



if( isset($_SESSION['nickUsuario'])) {

if($_SERVER['REQUEST_METHOD'] === 'POST'){

    $tituloEvento=strtoupper($_POST['nombreEvento']); 
    $minDesc = $_POST['minDescp'];
    $introEvento = $_POST['titular'];
    $eslogan = $_POST['esloganEvento'];
    $fecha = $_POST['fechaEvento'];
    $descripcion=$_POST['descripcion'];
    $idEv=-1;
    $etiquetas= [0=>$_POST['Etiqueta1'], 1=>$_POST['Etiqueta2'], 2=>$_POST['Etiqueta3'], 3=>$_POST['Etiqueta4'], 4=>$_POST['Etiqueta5'], 5=>$_POST['Etiqueta6']];
    $unaEtiqueta=false;
    $unProducto=false;

    $tituloProducto= [0=>$_POST['nombreProducto1'],1=>$_POST['nombreProducto2'], 2=>$_POST['nombreProducto3'], 3=>$_POST['nombreProducto4'], 4=>$_POST['nombreProducto5'], 5=>$_POST['nombreProducto6'] ];
    $descProducto= [0=>$_POST['descProducto1'], 1=>$_POST['descProducto2'], 2=>$_POST['descProducto3'], 3=>$_POST['descProducto4'], 4=>$_POST['descProducto5'], 5=>$_POST['descProducto6'] ];
    $imagenes=[0=> $_FILES['foto1']['name'], 1=> $_FILES['foto2']['name'], 2=> $_FILES['foto3']['name'], 3=> $_FILES['foto4']['name'], 4=> $_FILES['foto5']['name'], 5=> $_FILES['foto6']['name'] ];
    $tams=[0=> $_FILES['foto1']['size'], 1=> $_FILES['foto2']['size'], 2=> $_FILES['foto3']['size'], 3=> $_FILES['foto4']['size'], 4=> $_FILES['foto5']['size'], 5=> $_FILES['foto6']['size'] ];
    $tmps=[0=> $_FILES['foto1']['tmp_name'], 1=> $_FILES['foto2']['tmp_name'], 2=> $_FILES['foto3']['tmp_name'], 3=> $_FILES['foto4']['tmp_name'], 4=> $_FILES['foto5']['tmp_name'], 5=> $_FILES['foto6']['tmp_name'] ];
    $tipos=[0=> $_FILES['foto1']['type'], 1=> $_FILES['foto2']['type'], 2=> $_FILES['foto3']['type'], 3=> $_FILES['foto4']['type'], 4=> $_FILES['foto5']['type'], 5=> $_FILES['foto6']['type'] ];
    $exts=[0=> strtolower(end(explode('.',$_FILES['foto1']['name']))), 1=> strtolower(end(explode('.',$_FILES['foto2']['name']))), 2=> strtolower(end(explode('.',$_FILES['foto3']['name']))), 3=> strtolower(end(explode('.',$_FILES['foto4']['name']))), 4=> strtolower(end(explode('.',$_FILES['foto5']['name']))), 5=> strtolower(end(explode('.',$_FILES['foto6']['name']))) ];

    
    for($i=0; $i<sizeof($etiquetas);$i++)
    {
        if(!empty($etiquetas[$i]))
        {
            $unaEtiqueta=true;
        }
    }

    for($i=0; $i<sizeof($tituloProducto);$i++)
    {
        if(!empty($tituloProducto[$i]) and !empty($descProducto[$i]) and !empty($imagenes[$i]))
        {
            $unProducto=true;
        }  
    }

    

    if(empty($tituloEvento) and empty($minDesc) and empty($introEvento) and empty($eslogan) and empty($fecha) and empty($descripcion)){
        $errores[] ="Debes rellenar todos los campos";
    }
    else if(empty($tituloEvento))
    {
        $errores[] ="Debes rellenar el campo del titulo del evento";
    }
    else if(empty($minDesc))
    {
        $errores[] ="Debes rellenar el campo de la descripción mínima";
    }
    else if(empty($introEvento))
    {
        $errores[] ="Debes rellenar el campo de portada del evento";
    }
    else if(empty($eslogan))
    {
        $errores[] ="Debes rellenar el campo de eslogan del evento";
    }
    else if(empty($fecha))
    {
        $errores[] ="Debes introducir la fecha del evento";
    }
    else if(empty($descripcion))
    {
        $errores[] ="Debes rellenar el campo de descripción del evento";
    }
    else if($unaEtiqueta==false)
    {
        $errores[] ="Debes rellenar al menos una etiqueta";
    }
    else if($unProducto==false)
    {
        $errores[] ="Debes rellenar al menos información de un producto (nombre, descripcion y la imagen)";
    }
    else if(isset($_FILES['fotoEvent']))
    {
        
        $file_name= $_FILES['fotoEvent']['name'];
        if(empty($file_name))
        {
            $errores[] ="Debes introducir la imagen del evento";
        }
        else{
            $file_size= $_FILES['fotoEvent']['size'];
            $file_tmp= $_FILES['fotoEvent']['tmp_name'];
            $file_type= $_FILES['fotoEvent']['type'];
            $file_ext=strtolower(end(explode('.',$_FILES['fotoEvent']['name'])));
            
            $errores[]=getFallosImagen($file_ext,$file_size);
            
            for($i=0; $i<sizeof($imagenes);$i++)
            {
                if(!empty($tituloProducto[$i]) and !empty($descProducto[$i]) and !empty($imagenes[$i]))
                {
                    $errores[]=getFallosImagen($exts[$i],$tams[$i]);
                }
            }

            $limpio=true;

            for($i=0; $i<sizeof($errores);$i++)
            {
                if($errores[$i]!="")
                {
                    $limpio=false;
                }
            }
            
            
            if($limpio ==true ){    
                $rutaImgInicio="imgs/" . $file_name;
                move_uploaded_file($file_tmp, $rutaImgInicio);
                $idEv=crearEventoInicio($tituloEvento, $minDesc,$rutaImgInicio);
                crearEvento($idEv,$introEvento,$eslogan,$fecha,$descripcion);

                for($i=0; $i<sizeof($etiquetas);$i++)
                {
                    if(!empty($etiquetas[$i]))
                    {
                       crearEtiqueta($idEv,$etiquetas[$i]);
                    }
                }

                for($i=0; $i<sizeof($imagenes);$i++)
                {
                    $rutaImgEvento="imgs/". $imagenes[$i];
                    move_uploaded_file($tmps[$i], $rutaImgEvento);

                    if(!empty($tituloProducto[$i]) and !empty($descProducto[$i]) and !empty($imagenes[$i]))
                    {
                        crearImagen($idEv,$tituloProducto[$i],$descProducto[$i],$rutaImgEvento);
                    } 
                    
                }

                header("Location: index.php");
            
            }
        }
       
    }
    

    

    
}


}

echo $twig->render('crearEvento.html', ['errores' => $errores])

?>