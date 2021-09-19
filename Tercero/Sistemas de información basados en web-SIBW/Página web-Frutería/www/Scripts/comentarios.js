


function aparecer() {
    onclick = document.getElementById('cm').style.display = 'flex';
    onclick = document.getElementById('ef').style.display = 'none';
}

function cerrar() {
    onclick = document.getElementById('cm').style.display = 'none';
    onclick = document.getElementById('ef').style.display = 'block';
}

function enviarComentario(nombreUsuario) {
    //onclick=document.getElementById('whoWhen').innerHTML=document.getElementsByClassName('nombre')[0].value;
    
    if (document.getElementsByClassName('coment')[0].value.length == 0)
        alert("Debe rellenar todos los campos para enviar un comentario");
    else {

        //var emailExReg = /^(([^<>()[\]\.,;:\s@\"]+(\.[^<>()[\]\.,;:\s@\"]+)*)|(\".+\"))@(([^<>()[\]\.,;:\s@\"]+\.)+[^<>()[\]\.,;:\s@\"]{2,})$/i;


        //if (!emailExReg.test(document.getElementsByClassName('email')[0].value)) {
          //  alert("El formato del email es incorrecto");
        //}
        
        
            const fecha = new Date();
            var creador = document.createElement('h2');
            var contenido = document.createTextNode(nombreUsuario + " comento el " + fecha.getDate() + "-" + (fecha.getMonth() + 1) + "-" + fecha.getFullYear() + " a las " + fecha.getHours() + ":" + fecha.getMinutes());
            creador.appendChild(contenido);
            onclick = document.getElementById('lc').insertAdjacentElement('beforeend', creador);

            var comentario = document.createElement('p');
            var contenido2 = document.createTextNode(document.getElementsByClassName('coment')[0].value);
            comentario.appendChild(contenido2);
            onclick = document.getElementById('lc').insertAdjacentElement('beforeend', comentario);
        

}

}       




function comprobarInsultos() {

    var x = document.getElementsByClassName('coment')[0].value;
    var x2 = x.split(" ");
    var res = new RegExp(insultos.join("|") + "|" + "/gi");


    for (let i = 0; i < x2.length; i++) {

        for (let j = 0; j < insultos.length; j++) {

                if (x2[i].toLowerCase()==insultos[j].palabrota) {
                console.log("entro");
                var censura="*";
                censura+=censura.repeat(x2[i].length-1);
                
                res = x.replace(x2[i], censura);
                document.getElementsByClassName('coment')[0].value = res;


            }
        }




    }

}

function cambiarTexto(texto,id)
{
    document.getElementById('cm2').innerHTML=texto;
    document.getElementById('enviar').value="MODIFICAR COMENTARIO";
    document.getElementById('idEscondido').value=id;
    
}