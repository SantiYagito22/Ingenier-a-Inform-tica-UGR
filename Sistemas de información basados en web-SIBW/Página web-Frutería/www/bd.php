<?php

$mysqli= new mysqli("mysql", "Santiago", "12345", "SIBW");
if($mysqli->connect_errno){
    echo ("Fallo al conectar: " . $mysqli->connect_error);
}




function getEvento($idEv){
    global $mysqli;

    $sentencia = $mysqli->prepare("SELECT id, nombre, eslogan , fecha, descripcion, publicado FROM eventos WHERE id= ?");
   
    $sentencia->bind_param("i", $idEv);

    $sentencia->execute();
       
    $res=$sentencia->get_result();

    $evento= null;

    if($res->num_rows > 0){
        $row = $res->fetch_assoc();

        $evento = array('nombre' => $row['nombre'], 'eslogan' => $row['eslogan'], 'fecha' => $row['fecha'], 'descripcion' => $row['descripcion'], 'id' => $row['id'], 'publicado' => $row['publicado']);
    }

    return $evento;
}

function getImagen($idEv){
    global $mysqli;
    $sentencia = $mysqli->prepare("SELECT tipo, ruta, descripcion, identificador FROM imagenes WHERE id=?");


    $sentencia->bind_param("i", $idEv);

    $sentencia->execute();
       
    $res=$sentencia->get_result();

    $imagen= null;

    if($res->num_rows > 0){
        
        $imagen= array();
        while($row = $res->fetch_assoc()) {
            $imagen[] = array('tipo' => $row['tipo'], 'ruta' => $row['ruta'], 'descripcion' => $row['descripcion'], 'identificador' => $row['identificador']);
            
        }
        
    }

    return $imagen;
}

function getComentarios($idEv){
    global $mysqli;
    $sentencia = $mysqli->prepare("SELECT nombre, fecha, comentario, identificador, editado FROM comentarios WHERE id=?");
    
    $sentencia->bind_param("i", $idEv);

    $sentencia->execute();
       
    $res=$sentencia->get_result();


    $coment= null;
    

    if($res->num_rows > 0){
        
        $coment= array();

        while($row = $res->fetch_assoc()) {
            $coment[] = array('nombre' => $row['nombre'],'fecha' => $row['fecha'], 'comentario' => $row['comentario'], 'identificador' => $row['identificador'], 'editado' => $row['editado']);
            
        }

        
        
    }

    return $coment;

}

function getPalabrotas(){
    global $mysqli;
    $sentencia = $mysqli->prepare("SELECT * FROM MalasPalabras");


    $sentencia->execute();
       
    $res=$sentencia->get_result();

    $palabrotas= null;
    

    if($res->num_rows > 0){
        
        $palabrotas= array();

        while($row = $res->fetch_assoc()) {
            $palabrotas[] = array('palabrota' => $row['palabrota']);
            
        }

        
        
    }

    return $palabrotas;

}

function checkLogin($user,$pass)
{
    global $mysqli;
    $sentencia = $mysqli->prepare("SELECT nombreUsuario, clave FROM usuarios");

    if(!$sentencia->execute())
    {
        return false;
    }
        
       
    $res=$sentencia->get_result();


    
    if($res->num_rows > 0){
        
        $users= array();

        while($row = $res->fetch_assoc()) {
            $users[] = array('nombreUsuario' => $row['nombreUsuario'], 'clave' => $row['clave']);
            
        }

        for($i = 0 ; $i < sizeof($users) ; $i++)
        {
            
            if($users[$i]['nombreUsuario'] === $user){
                
                if(password_verify($pass, $users[$i]['clave']))
                {      
                    return true;
                }
            }
        }
        return false;
    }
    
}

function getDatosUsuario($user)
{
    global $mysqli;
    $sentencia = $mysqli->prepare("SELECT nombreUsuario, nombreCompleto, correo, tipo  FROM usuarios WHERE nombreUsuario = ?");

    
    $sentencia->bind_param("s", $user);
    $sentencia->execute();
      
    $res=$sentencia->get_result();

    $datos= array('tipo' => 'anonimo');
    
    if($res->num_rows > 0){
        
        $row = $res->fetch_assoc(); 
        $datos = array('nombreUsuario' => $row['nombreUsuario'], 'nombreCompleto' => $row['nombreCompleto'], 'correo' => $row['correo'], 'tipo' => $row['tipo'] );   
        

    }

    return $datos;

}

function checkRegistro($user){
global $mysqli;
    $sentencia = $mysqli->prepare("SELECT nombreUsuario FROM usuarios");

    if(!$sentencia->execute())
    {
        return true;
    }
        
       
    $res=$sentencia->get_result();
    
    $users=null;

    while($row = $res->fetch_assoc()) {
        $users[] = array('nombreUsuario' => $row['nombreUsuario']);
        
    }

    if($users != null)
    {
        for($i = 0 ; $i < sizeof($users) ; $i++)
    {
        
        if($users[$i]['nombreUsuario'] === $user){
            return true;
        }
    }
    return false;
    }
    
}

function Registrar($user,$pass,$nombre,$email){
    global $mysqli;

        $sentencia = $mysqli->prepare("INSERT INTO usuarios (nombreUsuario, nombreCompleto, correo, clave, tipo) VALUES (?, ?, ?, ?, ?)");

        $passHash=password_hash($pass, PASSWORD_DEFAULT);
        $tipo="registrado";

        $sentencia->bind_param('sssss', $user, $nombre, $email, $passHash, $tipo );

        return $sentencia->execute();   
    }



function getTextoFecha(){
    $fecha=" el " . date("d") . "-" . date("m") . "-" . date("Y") . " a las " . date("H") . ":" . date("i");

    return $fecha;
}


function comentar($usuario,$fecha,$comentario,$idEv){
    global $mysqli;
    $sentencia = $mysqli->prepare("INSERT INTO comentarios (id, nombre, fecha, comentario) VALUES (?, ?, ?, ?)");

    $sentencia->bind_param('isss', $idEv, $usuario, $fecha, $comentario);

    $sentencia->execute(); 
}

function eliminarCuenta($user){
    global $mysqli;
    $sentencia = $mysqli->prepare("DELETE FROM usuarios WHERE nombreUsuario = ?");
    $sentencia2 = $mysqli->prepare("DELETE FROM comentarios WHERE nombre = ?");


    $sentencia->bind_param('s', $user);
    $sentencia2->bind_param('s',$user);

    $sentencia->execute();
    $sentencia2->execute();

}

function cambiarDatos($nombre,$pass,$correo,$usuario,$usuarioActual){
    global $mysqli;
    
    if($pass!=null)
    {
        if($usuario==$usuarioActual)
        {
        $sentencia = $mysqli->prepare("UPDATE usuarios set nombreCompleto = ? , clave = ? , correo = ? , nombreUsuario = ?  WHERE nombreUsuario= ?");

        $passHash=password_hash($pass, PASSWORD_DEFAULT);
        $sentencia->bind_param('sssss', $nombre, $passHash,$correo,$usuarioActual,$usuarioActual);

        return $sentencia->execute();
        }
        else if(!checkRegistro($usuario))
        {
        $sentencia = $mysqli->prepare("UPDATE usuarios set nombreCompleto = ? , clave = ? , correo = ? , nombreUsuario = ?  WHERE nombreUsuario= ?");
        
        $sentencia2=$mysqli->prepare("UPDATE comentarios set nombre= ? WHERE nombre= ? ");
        $passHash=password_hash($pass, PASSWORD_DEFAULT);

        $sentencia->bind_param('sssss', $nombre, $passHash,$correo,$usuario,$usuarioActual);
        $sentencia2->bind_param('ss',$usuario,$usuarioActual);
        

        return $sentencia->execute() && $sentencia2->execute();
        }
    }
    else{
        if($usuario==$usuarioActual)
        {
            $sentencia = $mysqli->prepare("UPDATE usuarios set nombreCompleto = ? , correo = ? , nombreUsuario = ?  WHERE nombreUsuario= ?");
    
            $sentencia->bind_param('ssss', $nombre,$correo,$usuarioActual,$usuarioActual);
    
            return $sentencia->execute();
        }
        else if(!checkRegistro($usuario))
        {
            $sentencia = $mysqli->prepare("UPDATE usuarios set nombreCompleto = ? , correo = ? , nombreUsuario = ?  WHERE nombreUsuario= ?");
            $sentencia2=$mysqli->prepare("UPDATE comentarios set nombre= ? WHERE nombre= ? ");

            $sentencia->bind_param('ssss', $nombre,$correo,$usuario,$usuarioActual);
            $sentencia2->bind_param('ss',$usuario,$usuarioActual);
            

            return $sentencia->execute() && $sentencia2->execute();
        }
    }
    
       
    return false;
    
   
}


function borrarComentario($idComentario){

    global $mysqli;
    $sentencia = $mysqli->prepare("DELETE FROM comentarios WHERE identificador = ?");

    $sentencia->bind_param('i',$idComentario);

    $sentencia->execute();
}

function cambiarComentario($idComentario,$textoACambiar){

    global $mysqli;
    $sentencia = $mysqli->prepare("UPDATE comentarios set comentario = ? , editado= ?  WHERE identificador = ?");

    $editado=1;
    $sentencia->bind_param('sii',$textoACambiar,$editado,$idComentario);

    $sentencia->execute();
}

function getTodosComentarios()
{
    global $mysqli;
    $sentencia = $mysqli->prepare("SELECT nombre, fecha, comentario, identificador, editado FROM comentarios");

    $sentencia->execute();

    $res=$sentencia->get_result();


    $coment= null;
    

    if($res->num_rows > 0){
        
        $coment= array();

        while($row = $res->fetch_assoc()) {
            $coment[] = array('nombre' => $row['nombre'],'fecha' => $row['fecha'], 'comentario' => $row['comentario'], 'identificador' => $row['identificador'], 'editado' => $row['editado']);  
        }
    }
    
    return $coment;
}

function getEventosInicio()
{
    global $mysqli;
    $sentencia = $mysqli->prepare("SELECT tipo, introduccion, imagen, id, visible FROM eventosInicio");

    $sentencia->execute();

    $res=$sentencia->get_result();


    $eventos= null;

    if($res->num_rows > 0){
        
        $eventos= array();

        while($row = $res->fetch_assoc()) {
            $eventos[] = array('tipo' => $row['tipo'],'introduccion' => $row['introduccion'], 'imagen' => $row['imagen'], 'id' => $row['id'], 'visible' => $row['visible']);  
        }
    }

    return $eventos;

}


function getEtiquetas($idEv)
{
    global $mysqli;
    $sentencia = $mysqli->prepare("SELECT id, tipo  FROM etiquetas WHERE identificador= ?");

    $sentencia->bind_param('i',$idEv);

    $sentencia->execute();

    $res=$sentencia->get_result();


    $etiquetas= null;

    if($res->num_rows > 0){
        
        $etiquetas= array();

        while($row = $res->fetch_assoc()) {
            $etiquetas[] = array('id' => $row['id'],'tipo' => $row['tipo']);  
        }
    }

    return $etiquetas;
}

function getFallosImagen($file_ext,$file_size){
    
$extensions= array("jpeg","jpg","png");


    if(in_array($file_ext,$extensions) === false)
    {
        return "Extensión no permitida, elige una imagen JPEG o PNG";
    }
    else if($file_size > 2097152)
        return "Tamaño del fichero demasiado grande";
    else
        return null;
    
}

function crearEventoInicio($tituloEvento, $minDesc,$rutaImgInicio){
    global $mysqli;
    $sentencia = $mysqli->prepare("INSERT INTO eventosInicio (tipo, introduccion, imagen) VALUES (?, ?, ?)");
    $sentencia->bind_param('sss', $tituloEvento, $minDesc, $rutaImgInicio);
    $sentencia->execute();

    $sentencia2 = $mysqli->prepare("SELECT id FROM eventosInicio WHERE tipo= ? and introduccion= ? and imagen= ?");

    $sentencia2->bind_param('sss', $tituloEvento, $minDesc, $rutaImgInicio);

    $sentencia2->execute();

    $res=$sentencia2->get_result();

    $id= null;
    
    if($res->num_rows > 0){
        
        $id= 0;
        $row = $res->fetch_assoc(); 
        $id = $row['id'];  
        
    }

    return $id;
   


}

function crearEvento($idEv,$introEvento,$eslogan,$fecha,$descripcion){

    global $mysqli;
    $sentencia = $mysqli->prepare("INSERT INTO eventos (id, nombre, eslogan, fecha, descripcion) VALUES (?, ?, ?, ?, ?)");
    $sentencia->bind_param('issss', $idEv, $introEvento, $eslogan,$fecha,$descripcion);
    $sentencia->execute();

}

function crearEtiqueta($idEv,$etiqueta){

    global $mysqli;
    $sentencia = $mysqli->prepare("INSERT INTO etiquetas (identificador, tipo)  VALUES (?, ?)");
    $sentencia->bind_param('is', $idEv,$etiqueta);
    $sentencia->execute();
}

function crearImagen($idEv,$tituloProducto,$descProducto,$rutaImgEvento){
    global $mysqli;
    $sentencia = $mysqli->prepare("INSERT INTO imagenes (id, tipo, ruta, descripcion)  VALUES (?, ?, ?, ?)");
    $sentencia->bind_param('isss', $idEv,$tituloProducto, $rutaImgEvento, $descProducto);
    $sentencia->execute();
}



function eliminarEvento($idEv){
    global $mysqli;
    $sentencia = $mysqli->prepare("DELETE FROM etiquetas WHERE identificador = ?");
    $sentencia->bind_param('i', $idEv);
    $sentencia->execute();

    $sentencia2 = $mysqli->prepare("DELETE FROM comentarios WHERE id = ?");
    $sentencia2->bind_param('i', $idEv);
    $sentencia2->execute();

    $sentencia3 = $mysqli->prepare("DELETE FROM eventos WHERE id = ?");
    $sentencia3->bind_param('i', $idEv);
    $sentencia3->execute();

    $sentencia4 = $mysqli->prepare("SELECT imagen FROM eventosInicio WHERE id= ?");
    $sentencia4->bind_param('i', $idEv);
    $sentencia4->execute();

    $res=$sentencia4->get_result();

    $rutaInicio= null;
    
    if($res->num_rows > 0){
        

        $row = $res->fetch_assoc(); 
        $rutaInicio = $row['imagen'];  
        unlink($rutaInicio);
    }

    
    $sentencia5 = $mysqli->prepare("DELETE FROM eventosInicio WHERE id = ?");
    $sentencia5->bind_param('i', $idEv);
    $sentencia5->execute();


    $sentencia6 = $mysqli->prepare("SELECT ruta FROM imagenes WHERE id= ?");
    $sentencia6->bind_param('i', $idEv);
    $sentencia6->execute();

    $res2=$sentencia6->get_result();

    if($res2->num_rows > 0){
        
        $rutas= array();

        while($row = $res2->fetch_assoc()) {
            $rutas[] = array('ruta' => $row['ruta']);  
        }
    }

    for($i=0; $i<sizeof($rutas);$i++)
    {
       unlink($rutas[$i]['ruta']);
    }

    $sentencia7 = $mysqli->prepare("DELETE FROM imagenes WHERE id = ?");
    $sentencia7->bind_param('i', $idEv);
    $sentencia7->execute();


}

function getDatosEventoInicio($idEv){
    global $mysqli;
    $sentencia = $mysqli->prepare("SELECT tipo, introduccion, imagen FROM eventosInicio WHERE id= ?");
    $sentencia->bind_param('i', $idEv);
    $sentencia->execute();

    $res=$sentencia->get_result();

    $evento= null;

    if($res->num_rows > 0){
        
        $row = $res->fetch_assoc();    
        $evento = array('tipo' => $row['tipo'],'introduccion' => $row['introduccion'], 'imagen' => $row['imagen']);  
    
    }

    return $evento;
}

function actualizarEventoInicio($tituloEvento,$minDesc,$rutaImgInicio,$idEv){
    global $mysqli;
    $sentencia = $mysqli->prepare("UPDATE eventosInicio set tipo = ? , introduccion = ? , imagen = ?  WHERE id= ?");
    
    $sentencia->bind_param('sssi', $tituloEvento, $minDesc,$rutaImgInicio,$idEv);

    $sentencia->execute();
}

function  actualizarEvento($introEvento,$eslogan,$fecha,$descripcion,$idEv){
    global $mysqli;
    $sentencia = $mysqli->prepare("UPDATE eventos set nombre = ? , eslogan = ? , fecha = ?, descripcion= ?  WHERE id= ?");
    
    $sentencia->bind_param('ssssi', $introEvento, $eslogan,$fecha,$descripcion,$idEv);

    $sentencia->execute();
}

function actualizarEtiqueta($etiquetas,$etiquetas2,$idEv){
    global $mysqli;
    $sentencia = $mysqli->prepare("UPDATE etiquetas set tipo = ?  WHERE identificador= ? and tipo= ?");
    
    $sentencia->bind_param('sis', $etiquetas, $idEv,$etiquetas2);

    $sentencia->execute();
}

function borrarEtiqueta($etiquetas2,$idEv){
    global $mysqli;
    $sentencia = $mysqli->prepare("DELETE FROM etiquetas WHERE identificador = ? and tipo= ?");
    $sentencia->bind_param('is', $idEv, $etiquetas2);
    $sentencia->execute();
}

function actualizarGaleria($id,$tituloProducto,$descProducto,$ruta)
{
    global $mysqli;
    $sentencia = $mysqli->prepare("UPDATE imagenes set tipo = ? , ruta= ?, descripcion= ?   WHERE identificador= ? ");
    
    $sentencia->bind_param('sssi', $tituloProducto, $ruta,$descProducto,$id);

    $sentencia->execute();
}

function borrarGaleria($id){

    global $mysqli;
    $sentencia = $mysqli->prepare("DELETE FROM imagenes WHERE identificador = ? ");
    $sentencia->bind_param('i', $id);
    $sentencia->execute();

}

function getUsuarios()
{
    global $mysqli;
    $sentencia = $mysqli->prepare("SELECT nombreUsuario, nombreCompleto, tipo  from usuarios");
    $sentencia->execute();

    $usuarios= null;
    $res=$sentencia->get_result();

    if($res->num_rows > 0){
        
        $usuarios= array();

        while($row = $res->fetch_assoc()) {
            $usuarios[] = array('nombreUsuario' => $row['nombreUsuario'],'nombreCompleto' => $row['nombreCompleto'], 'tipo' => $row['tipo']);  
        }
    }

    return $usuarios;
}

function hayMasDeUnSuperusuario(){
    global $mysqli;
    $sentencia = $mysqli->prepare("SELECT tipo  from usuarios WHERE tipo= ?");
    $super='super';
    $sentencia->bind_param('s', $super);
    $sentencia->execute();

    
    $res=$sentencia->get_result();
    
    $numUsuarios=0;

    if($res->num_rows > 1){
        
        while($row = $res->fetch_assoc()) {
           $numUsuarios++;
        }
        
    }

    return $numUsuarios;
    
}

function actualizarTipo($nombreUsuario,$tipo){
    global $mysqli;
    $sentencia = $mysqli->prepare("UPDATE usuarios set tipo = ? WHERE nombreUsuario= ? ");
    $sentencia->bind_param('ss', $tipo,$nombreUsuario);
    $sentencia->execute();
}

function cambiarVisibilidad($visibilidad,$idEv){
    global $mysqli;
    $sentencia = $mysqli->prepare("UPDATE eventos set publicado = ? WHERE id= ? ");
    $sentencia->bind_param('ii', $visibilidad,$idEv);
    $sentencia->execute();

    $sentencia2 = $mysqli->prepare("UPDATE eventosInicio set visible = ? WHERE id= ? ");
    $sentencia2->bind_param('ii', $visibilidad,$idEv);
    $sentencia2->execute();
}

function getEventos($palabraBusqueda,$tipo)
{
    if($palabraBusqueda!="")
    {
        if($tipo=="gestor" or $tipo=="super")
        {
            global $mysqli;
            $sentencia = $mysqli->prepare("SELECT nombre, id FROM eventos WHERE nombre LIKE ? or descripcion LIKE ? ");
            $palabraBusqueda= "%$palabraBusqueda%";
            $sentencia->bind_param('ss', $palabraBusqueda,$palabraBusqueda);
            $sentencia->execute();
        
            $respuestas= null;
        
            $res=$sentencia->get_result();
            if($res->num_rows > 0){
                
                $respuestas= array();
        
                while($row = $res->fetch_assoc()) {
                    $respuestas[] = array('nombre' => $row['nombre'],'id' => $row['id']);  
                }
            }
        
            return $respuestas;
        }
        else{
            global $mysqli;
            $sentencia = $mysqli->prepare("SELECT nombre, id FROM eventos WHERE (nombre LIKE ? or descripcion LIKE ?) and publicado= ? ");
            $palabraBusqueda= "%$palabraBusqueda%";
            $p=1;
            $sentencia->bind_param('ssi', $palabraBusqueda,$palabraBusqueda,$p);
            $sentencia->execute();
        
            $respuestas= null;
        
            $res=$sentencia->get_result();
            if($res->num_rows > 0){
                
                $respuestas= array();
        
                while($row = $res->fetch_assoc()) {
                    $respuestas[] = array('nombre' => $row['nombre'],'id' => $row['id']);  
                }
            }
        
            return $respuestas;
        }
      
    }
   
}

function resaltar($text, $word){
    $text = preg_replace('#'. preg_quote($word) .'#i', '<mark>\0</mark>', $text);
    return $text;
}

?>