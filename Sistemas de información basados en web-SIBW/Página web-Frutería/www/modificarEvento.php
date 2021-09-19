<?php
require_once "/usr/local/lib/php/vendor/autoload.php";
    include("bd.php");


    $loader = new \Twig\Loader\FilesystemLoader('templates');
    $twig = new \Twig\Environment($loader);

   
    $errores=array();
    
    if( isset($_GET['ev'])){
        $idEv= $_GET['ev'];
    }
    else{
        $idEv= -1;
    }

    

    
    $datosEventoInicio=getDatosEventoInicio($idEv);
    $datosEvento=getEvento($idEv);
    $etiquetas2=getEtiquetas($idEv);
    $galeria=getImagen($idEv);

    session_start();

    if(isset($_SESSION['nickUsuario']))
    {
        if($_SERVER['REQUEST_METHOD'] === 'POST'){

        $tituloEvento=strtoupper($_POST['nombreEvento']); 
        $minDesc = $_POST['minDescp'];
        $introEvento = $_POST['titular'];
        $eslogan = $_POST['esloganEvento'];
        $fecha = $_POST['fechaEvento'];
        $descripcion=$_POST['descripcion'];
        $etiquetas= [0=>$_POST['Etiqueta1'], 1=>$_POST['Etiqueta2'], 2=>$_POST['Etiqueta3'], 3=>$_POST['Etiqueta4'], 4=>$_POST['Etiqueta5'], 5=>$_POST['Etiqueta6']];
        $unaEtiqueta=false;
        $unProducto=false;
        $limpio=true;
        $puedesActualizar=false;

        $tituloProducto= [0=>$_POST['nombreProducto0'],1=>$_POST['nombreProducto1'], 2=>$_POST['nombreProducto2'], 3=>$_POST['nombreProducto3'], 4=>$_POST['nombreProducto4'], 5=>$_POST['nombreProducto5'] ];
        $descProducto= [0=>$_POST['descProducto0'], 1=>$_POST['descProducto1'], 2=>$_POST['descProducto2'], 3=>$_POST['descProducto3'], 4=>$_POST['descProducto4'], 5=>$_POST['descProducto5'] ];
        $imagenes=[0=> $_FILES['foto0']['name'], 1=> $_FILES['foto1']['name'], 2=> $_FILES['foto2']['name'], 3=> $_FILES['foto3']['name'], 4=> $_FILES['foto4']['name'], 5=> $_FILES['foto5']['name'] ];
        $tams=[0=> $_FILES['foto0']['size'], 1=> $_FILES['foto1']['size'], 2=> $_FILES['foto2']['size'], 3=> $_FILES['foto3']['size'], 4=> $_FILES['foto4']['size'], 5=> $_FILES['foto5']['size'] ];
        $tmps=[0=> $_FILES['foto0']['tmp_name'], 1=> $_FILES['foto1']['tmp_name'], 2=> $_FILES['foto2']['tmp_name'], 3=> $_FILES['foto3']['tmp_name'], 4=> $_FILES['foto4']['tmp_name'], 5=> $_FILES['foto5']['tmp_name'] ];
        $tipos=[0=> $_FILES['foto0']['type'], 1=> $_FILES['foto1']['type'], 2=> $_FILES['foto2']['type'], 3=> $_FILES['foto3']['type'], 4=> $_FILES['foto4']['type'], 5=> $_FILES['foto5']['type'] ];
        $exts=[0=> strtolower(end(explode('.',$_FILES['foto0']['name']))), 1=> strtolower(end(explode('.',$_FILES['foto1']['name']))), 2=> strtolower(end(explode('.',$_FILES['foto2']['name']))), 3=> strtolower(end(explode('.',$_FILES['foto3']['name']))), 4=> strtolower(end(explode('.',$_FILES['foto4']['name']))), 5=> strtolower(end(explode('.',$_FILES['foto5']['name']))) ];
    
        for($i=0; $i<sizeof($etiquetas);$i++)
        {
            if(!empty($etiquetas[$i]))
            {
                $unaEtiqueta=true;
            }
        }
    
        for($i=0; $i<sizeof($tituloProducto);$i++)
        {
            if(!empty($tituloProducto[$i]) and !empty($descProducto[$i]))
            {
                $unProducto=true;
            }  
        }

        if(empty($tituloEvento) and empty($minDesc) and empty($introEvento) and empty($eslogan) and empty($fecha) and empty($descripcion)){
            $errores[] ="Debes rellenar todos los campos";
        }
        else if(empty($tituloEvento))
        {
            $errores[] ="No puedes cambiar el campo del titulo del evento a nada";
        }
        else if(empty($minDesc))
        {
            $errores[] ="No puedes cambiar el campo de la descripción mínima a nada";
        }
        else if(empty($introEvento))
        {
            $errores[] ="No puedes cambiar el campo de portada del evento a nada";
        }
        else if(empty($eslogan))
        {
            $errores[] ="No puedes cambiar el campo de eslogan del evento a nada";
        }
        else if(empty($fecha))
        {
            $errores[] ="No puedes cambiar la fecha del evento a nada";
        }
        else if(empty($descripcion))
        {
            $errores[] ="No puedes cambiar el campo de descripción del evento a nada";
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
            if(!empty($file_name))
            {
                $file_size= $_FILES['fotoEvent']['size'];
                $file_tmp= $_FILES['fotoEvent']['tmp_name'];
                $file_type= $_FILES['fotoEvent']['type'];
                $file_ext=strtolower(end(explode('.',$_FILES['fotoEvent']['name'])));
            
                $errores[]=getFallosImagen($file_ext,$file_size);

                

                for($i=0; $i<sizeof($errores);$i++)
                {
                    if($errores[$i]!="")
                    {
                        $limpio=false;
                    }
                }
            
                if($limpio == true ){  
                    unlink($datosEventoInicio['imagen']); 
                    $rutaImgInicio="imgs/" . $file_name;
                    move_uploaded_file($file_tmp, $rutaImgInicio);
                    actualizarEventoInicio($tituloEvento,$minDesc,$rutaImgInicio,$idEv);
                    $puedesActualizar=true;
                }

            }
            else{
                $rutaImgInicio=$datosEventoInicio['imagen'];
                actualizarEventoInicio($tituloEvento,$minDesc,$rutaImgInicio,$idEv);
                $puedesActualizar=true;
            }
        }

        
        if($puedesActualizar==true)
        {
            actualizarEvento($introEvento,$eslogan,$fecha,$descripcion,$idEv);
            
            for($i=0; $i<sizeof($etiquetas);$i++)
            {
                
                if($etiquetas[$i]!=$etiquetas2[$i]['tipo'] and !empty($etiquetas[$i]) and !empty($etiquetas2[$i]['tipo']) )
                {
                    actualizarEtiqueta($etiquetas[$i],$etiquetas2[$i]['tipo'],$idEv);
                }
                else if($etiquetas[$i]!=$etiquetas2[$i]['tipo'] and empty($etiquetas[$i]) and !empty($etiquetas2[$i]['tipo']))
                {
                    
                    borrarEtiqueta($etiquetas2[$i]['tipo'],$idEv);
                }
                else if($etiquetas[$i]!=$etiquetas2[$i]['tipo'] and !empty($etiquetas[$i]) and empty($etiquetas2[$i]['tipo']))
                {
                    crearEtiqueta($idEv,$etiquetas[$i]);
                }
            }
    
            for($i=0; $i<sizeof($imagenes);$i++)
            {
                if(!empty($tituloProducto[$i]) and !empty($descProducto[$i]) and !empty($imagenes[$i]))
                {
                    $errores[]=getFallosImagen($exts[$i],$tams[$i]);
                }
            }
                for($i=0; $i<sizeof($errores);$i++)
                {
                    if($errores[$i]!="")
                    {
                        $limpio=false;
                    }
                }

                if($limpio == true ){  
                    for($i=0; $i<sizeof($imagenes);$i++)
                    {
                        if( ($tituloProducto[$i]!=$galeria[$i]['tipo'] or $descProducto[$i]!=$galeria[$i]['descripcion'] or $galeria[$i]['ruta']!="imgs/".$imagenes[$i] ) and 
                        ( !empty($tituloProducto[$i]) and !empty($descProducto[$i]) ) and 
                        (!empty($galeria[$i]['tipo']) or !empty($galeria[$i]['descripcion']) or !empty($galeria[$i]['ruta'])) )
                        {
                            if(!empty($imagenes[$i]))
                            {
                                unlink($galeria[$i]['ruta']);
                                move_uploaded_file($tmps[$i], "imgs/".$imagenes[$i]);
                                actualizarGaleria($galeria[$i]['identificador'],$tituloProducto[$i],$descProducto[$i],"imgs/".$imagenes[$i]);
                            }
                            else{
                                actualizarGaleria($galeria[$i]['identificador'],$tituloProducto[$i],$descProducto[$i],$galeria[$i]['ruta']);
                            }
                            
                        }
                        else if( ($tituloProducto[$i]!=$galeria[$i]['tipo'] or $descProducto[$i]!=$galeria[$i]['descripcion'] or $galeria[$i]['ruta']!="imgs/".$imagenes[$i] ) and
                        ( empty($tituloProducto[$i]) and empty($descProducto[$i]) ) and
                        (!empty($galeria[$i]['tipo']) and !empty($galeria[$i]['descripcion']) and !empty($galeria[$i]['ruta'])))
                        {
                            
                            unlink($galeria[$i]['ruta']);
                            borrarGaleria($galeria[$i]['identificador']);
                        }
                        else if( ($tituloProducto[$i]!=$galeria[$i]['tipo'] or $descProducto[$i]!=$galeria[$i]['descripcion'] or $galeria[$i]['ruta']!="imgs/".$imagenes[$i] ) and
                        ( !empty($tituloProducto[$i]) and !empty($descProducto[$i]) and !empty($imagenes[$i]) ) and 
                        ( empty($galeria[$i]['tipo']) and empty($galeria[$i]['descripcion']) and empty($galeria[$i]['ruta'])))
                        {

                                move_uploaded_file($tmps[$i], "imgs/".$imagenes[$i]);
                                crearImagen($idEv,$tituloProducto[$i],$descProducto[$i],"imgs/".$imagenes[$i]);
                        }

                    }
                }



                header("Location: modificarEvento.php?ev=".$idEv);
            }



        }
       
        
        
        
        
    }


    echo $twig->render('modificarEvento.html', ['errores' => $errores,'eventoInicio' => $datosEventoInicio, 'evento' => $datosEvento, 'etiquetas' => $etiquetas2, 'galeria' => $galeria])

?>