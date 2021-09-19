$(document).ready(function(){
    busqueda.onkeyup =  hacerPeticionAjax;
});

function hacerPeticionAjax()
{

    busqueda = $("#busqueda").val();
    
    
    $.ajax({
        data: {busqueda},
        url: '../ajax.php',
        type: 'get',
        success: function(respuestas){
            procesaRespuestaBusqueda(respuestas);
        }
        
    });

}

function procesaRespuestaBusqueda(respuestas){
    res="";
    $("#tabla > tbody").html(res);

    if(respuestas!=null)
    {
        for(i=0 ; i<respuestas.length ; i++){
            
            res+="<tr><td><a href=evento.php?ev="+respuestas[i].id+">"+ respuestas[i].nombre + "</a></td></tr>" ;
        }
    
        
        
        $("#tabla > tbody").html(res);
    }
    
}