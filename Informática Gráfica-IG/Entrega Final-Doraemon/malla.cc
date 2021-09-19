#include "aux.h"
#include "malla.h"
#include <bits/stdc++.h>

// *****************************************************************************
//
// Clase Malla3D
//
// *****************************************************************************

// Visualización en modo inmediato con 'glDrawElements'


void Malla3D::inicializarColores() {

    for(int i=0;i<v.size();i++)
    {
        cLineas.push_back(Tupla3f{0,0,0});
        cSolido.push_back(Tupla3f{0,0,1});
        cPuntos.push_back(Tupla3f{1,1,0});
        cPares.push_back(Tupla3f{1,0,0});
        cImpares.push_back(Tupla3f{0,0.5019,0});
        cRaro.push_back(Tupla3f{0,0,0});
    }


}

void Malla3D::cambiarColores(Tupla3f colorNuevo) {

    for(int i=0;i<v.size();i++)
    {
       cSolido[i]=colorNuevo;

    }
}

void Malla3D::setColorAux(Tupla3f col) {
    for(int i=0;i<v.size();i++)
        c_aux.push_back(col);
}

void Malla3D::setColorFalso(Tupla3f col) {


    for(int i=0;i<v.size();i++)
        cRaro.push_back(col);
}

void Malla3D::draw_AjedrezInmediato()
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT,0,v.data());
    carasPares.clear();
    carasImpares.clear();


        for (int i = 0; i < f.size(); i++) {
            if (i % 2 == 0) {
                carasPares.push_back(f.at(i));
            } else {
                carasImpares.push_back(f.at(i));
            }
        }
    glEnableClientState( GL_COLOR_ARRAY ); // habilitar uso de array de col.
    glColorPointer( 3, GL_FLOAT, 0, cPares.data()); // especifíca puntero a colores

    glDrawElements(GL_TRIANGLES, carasPares.size()*3 ,GL_UNSIGNED_INT, carasPares.data());

    glColorPointer( 3, GL_FLOAT, 0, cImpares.data()); // especifíca puntero a colores

    glDrawElements(GL_TRIANGLES, carasImpares.size()*3 ,GL_UNSIGNED_INT, carasImpares.data());

    glDisableClientState(GL_VERTEX_ARRAY);

}


void Malla3D::draw_ModoInmediato(char color,bool suave,bool plano,bool ra)
{

//Por defecto se dibuja en modo inmediato


    if(color=='A')
    {
        draw_AjedrezInmediato();
    }
    else {
        if (cPuntos.data() != NULL && color=='P') {
            glEnableClientState(GL_COLOR_ARRAY); // habilitar uso de array de col.
            glColorPointer(3, GL_FLOAT, 0, cPuntos.data()); // especifíca puntero a colores
        }

        if (cLineas.data() != NULL && color=='L') {

            glEnableClientState(GL_COLOR_ARRAY); // habilitar uso de array de col.
            glColorPointer(3, GL_FLOAT, 0, cLineas.data()); // especifíca puntero a colores
        }

        if (cSolido.data() != NULL && color=='S') {
            glEnableClientState(GL_COLOR_ARRAY);
            if(!ra)// habilitar uso de array de col.
                 glColorPointer(3, GL_FLOAT, 0, cSolido.data()); // especifíca puntero a colores
            else
            {
                glColorPointer(3, GL_FLOAT, 0, cRaro.data());
            }


        }

        if(suave) {
            m.aplicar();
            glShadeModel(GL_SMOOTH);
        }
        if(plano) {
            m.aplicar();
            glShadeModel(GL_FLAT);
        }


        if(textura!= nullptr)
        {
            textura->activar();
            glEnableClientState ( GL_TEXTURE_COORD_ARRAY );
            glTexCoordPointer ( 2 , GL_FLOAT , 0 , ct.data());
        }

        glVertexPointer(3, GL_FLOAT, 0, v.data());
        glEnableClientState(GL_VERTEX_ARRAY);
        if(suave || plano)
            glEnableClientState( GL_NORMAL_ARRAY );





        if(suave || plano)
            glNormalPointer( GL_FLOAT, 0, nv.data() );

        glDrawElements(GL_TRIANGLES, f.size() * 3, GL_UNSIGNED_INT, f.data());

        glDisableClientState(GL_VERTEX_ARRAY);

        if(suave || plano)
        glDisableClientState(GL_NORMAL_ARRAY);

        glDisable(GL_TEXTURE_2D);
    }
}




// -----------------------------------------------------------------------------
// Visualización en modo diferido con 'glDrawElements' (usando VBOs)





void Malla3D::draw_AjedrezDiferido()
{

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    // especificar localización y formato de la tabla de vértices, habilitar tabla
    if(id_vbo_ver==0)
    {
        id_vbo_ver= CrearVBO(GL_ARRAY_BUFFER,v.size()*sizeof(Tupla3f),v.data());
    }

        for (int i = 0; i < f.size(); i++) {
            if (i % 2 == 0) {
                carasPares.push_back(f.at(i));
            } else {
                carasImpares.push_back(f.at(i));
            }
        }


        if (id_vbo_tri_par == 0)
            id_vbo_tri_par = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, carasPares.size() * sizeof(Tupla3i), carasPares.data());

        if (id_vbo_tri_impar == 0)
            id_vbo_tri_impar = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, carasImpares.size() * sizeof(Tupla3i), carasImpares.data());




    glBindBuffer ( GL_ARRAY_BUFFER , id_vbo_ver ); // activar VBO de vértices

    glVertexPointer ( 3 , GL_FLOAT , 0 , 0 ); // especifica formato y offset (=0)

    glBindBuffer ( GL_ARRAY_BUFFER , 0 ); // desactivar VBO de vértices.

    glEnableClientState ( GL_VERTEX_ARRAY ); // habilitar tabla de vértices

    //Para las caras pares metemos color rojo

    vbo_rojo= CrearVBO(GL_ARRAY_BUFFER,cPares.size()*sizeof(Tupla3f),cPares.data());
    glEnableClientState( GL_COLOR_ARRAY ); // habilitar uso de array de col.
    glBindBuffer ( GL_ARRAY_BUFFER , vbo_rojo);
    glColorPointer( 3, GL_FLOAT, 0, 0);
    glBindBuffer ( GL_ARRAY_BUFFER , vbo_rojo);


    glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER , id_vbo_tri_par ); // activar VBO de triángulos



    glDrawElements ( GL_TRIANGLES , 3*carasPares.size () , GL_UNSIGNED_INT , 0 );//Dibujar triangulos
    glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER , 0 ); // desactivar VBO de triángulos


    //Para las caras impares metemos color verde
    vbo_verde= CrearVBO(GL_ARRAY_BUFFER,cImpares.size()*sizeof(Tupla3f),cImpares.data());
    glEnableClientState( GL_COLOR_ARRAY ); // habilitar uso de array de col.
    glBindBuffer ( GL_ARRAY_BUFFER , vbo_verde);
    glColorPointer( 3, GL_FLOAT, 0, 0);
    glBindBuffer ( GL_ARRAY_BUFFER , vbo_verde);

    glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER , id_vbo_tri_impar ); // activar VBO de triángulos

    glDrawElements ( GL_TRIANGLES , 3*carasImpares.size () , GL_UNSIGNED_INT , 0 );//Dibujar traingulos
    glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER , 0 ); // desactivar VBO de triángulos


    // desactivar uso de array de vértices
    glDisableClientState ( GL_VERTEX_ARRAY );
}


GLuint Malla3D::CrearVBO ( GLuint tipo_vbo , GLuint tamanio_bytes , GLvoid * puntero_ram )
{
    GLuint id_vbo ;      // resultado: identificador de VBO
    glGenBuffers ( 1 , & id_vbo ); // crear nuevo VBO, obtener identificador (nunca 0)
    glBindBuffer ( tipo_vbo , id_vbo ); // activar el VBO usando su identificador

// esta instrucción hace la transferencia de datos desde RAM hacia GPU

    glBufferData ( tipo_vbo , tamanio_bytes , puntero_ram , GL_STATIC_DRAW );
    glBindBuffer ( tipo_vbo , 0 ); // desactivación del VBO (activar 0)
    return id_vbo ; // devolver el identificador resultado
}




void Malla3D::draw_ModoDiferido(char color,bool suave, bool plano)
{

    if(color=='A')
    {
        draw_AjedrezDiferido();
    }

else {

// especificar localización y formato de la tabla de vértices, habilitar tabla

        if (id_vbo_ver == 0) {
            id_vbo_ver = CrearVBO(GL_ARRAY_BUFFER, v.size() * sizeof(Tupla3f), v.data());
        }
        if(id_vbo_tri==0)
        {
            id_vbo_tri = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, f.size() * sizeof(Tupla3i), f.data());
        }
        if(id_vbo_normales==0)
        {
            id_vbo_normales=CrearVBO(GL_ARRAY_BUFFER, nv.size() * sizeof(Tupla3f), nv.data());
        }
        if(id_vbo_text==0)
        {
            id_vbo_text=CrearVBO(GL_ARRAY_BUFFER, ct.size() * sizeof(Tupla2f), ct.data());
        }


        if (color=='S') {
            vbo_solido = CrearVBO(GL_ARRAY_BUFFER, cSolido.size() * sizeof(Tupla3f), cSolido.data());
            glEnableClientState(GL_COLOR_ARRAY); // habilitar uso de array de col.
            glBindBuffer(GL_ARRAY_BUFFER, vbo_solido);
            glColorPointer(3, GL_FLOAT, 0, 0);
            glBindBuffer(GL_ARRAY_BUFFER, vbo_solido);
        }

        if (color=='P') {
            vbo_puntos = CrearVBO(GL_ARRAY_BUFFER, cPuntos.size() * sizeof(Tupla3f), cPuntos.data());
            glEnableClientState(GL_COLOR_ARRAY); // habilitar uso de array de col.
            glBindBuffer(GL_ARRAY_BUFFER, vbo_puntos);
            glColorPointer(3, GL_FLOAT, 0, 0);
            glBindBuffer(GL_ARRAY_BUFFER, vbo_puntos);
        }

        if (color=='L') {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            vbo_lineas = CrearVBO(GL_ARRAY_BUFFER, cLineas.size() * sizeof(Tupla3f), cLineas.data());
            glEnableClientState(GL_COLOR_ARRAY); // habilitar uso de array de col.
            glBindBuffer(GL_ARRAY_BUFFER, vbo_lineas);
            glColorPointer(3, GL_FLOAT, 0, 0);
            glBindBuffer(GL_ARRAY_BUFFER, vbo_lineas);
        }

        if(suave) {
            m.aplicar();
            glShadeModel(GL_SMOOTH);
        }
        if(plano) {
            m.aplicar();
            glShadeModel(GL_FLAT);
        }


        if(textura!= nullptr)
        {
            textura->activar();
            glEnableClientState ( GL_TEXTURE_COORD_ARRAY );
            glBindBuffer( GL_ARRAY_BUFFER , id_vbo_text);
            glTexCoordPointer ( 2 , GL_FLOAT , 0 , 0);
            glBindBuffer( GL_ARRAY_BUFFER , 0);

        }

        if(plano || suave) {
            glBindBuffer(GL_ARRAY_BUFFER, id_vbo_normales); // activar VBO de normales
            glNormalPointer( GL_FLOAT, 0, 0 );
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glEnableClientState(GL_NORMAL_ARRAY);
        }


        glBindBuffer(GL_ARRAY_BUFFER, id_vbo_ver); // activar VBO de vértices
        glVertexPointer(3, GL_FLOAT, 0, 0); // especifica formato y offset (=0)


        glBindBuffer(GL_ARRAY_BUFFER, 0); // desactivar VBO de vértices.

        glEnableClientState(GL_VERTEX_ARRAY); // habilitar tabla de vértices



// visualizar triángulos con glDrawElements (puntero a tabla == 0)


        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_vbo_tri); // activar VBO de triángulos

        glDrawElements(GL_TRIANGLES, f.size() * 3, GL_UNSIGNED_INT, 0);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // desactivar VBO de triángulos

// desactivar uso de array de vértices
        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_NORMAL_ARRAY);
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        glDisable(GL_TEXTURE_2D);
    }
}




// -----------------------------------------------------------------------------
// Función de visualización de la malla,
// puede llamar a  draw_ModoInmediato o bien a draw_ModoDiferido

void Malla3D::draw(unsigned int modo,char color,bool suave,bool plano,bool ra)
{


   if(modo==1)
      draw_ModoInmediato(color,suave,plano,ra);
   else if(modo==2)
      draw_ModoDiferido(color,suave,plano);

}


void Malla3D::calcular_normales() {

    //Primero calculamos las normales de las caras

    Tupla3f p,q,r;  //Vertices de cada cara
    Tupla3f a,b; //Vectores para cálculo de la perpendicular
    float mV;   //Magnitud del vector
    Tupla3f vP; //vector perpendicular a la cara
    Tupla3f vectorNormalizado; //vector normalizado el cual sera


    nv.resize(v.size());
    for(int i=0;i<v.size();i++)
        nv.push_back({0.0,0.0,0.0});


    for(int i=0; i<f.size();i++)
    {
        //Obtenemos el valor de los tres vertices de la cara con indice i
        p=v.at(f.at(i)(X));
        q=v.at(f.at(i)(Y));
        r=v.at(f.at(i)(Z));

        //Calculamos los vectores correspondientes a dos aristas
        a=q-p;
        b=r-p;

        //Calculamos el vector perpendicular a la cara con indice i, a x b

        vP=a.cross(b);


        //Calculamos la magnitud del vector
        mV=sqrt(vP(X)*vP(X)+vP(Y)*vP(Y)+vP(Z)*vP(Z));

        //Normalizamos este último vector para obtener el vector normal (de longitud unidad)

        vectorNormalizado={vP(X)/mV,vP(Y)/mV,vP(Z)/mV};
        //vectorNormalizado=vP.normalized();

        //Va sumando al vertice correspondiente el vector normal de cada cara en la que aparezca
        nv[f.at(i)(X)]=nv[f.at(i)(X)]+vectorNormalizado;
        nv[f.at(i)(Y)]=nv[f.at(i)(Y)]+vectorNormalizado;
        nv[f.at(i)(Z)]=nv[f.at(i)(Z)]+vectorNormalizado;
    }

    //Normalizamos para cada uno de los elementos de mv y estos seras los vectores normales de los vertices

    for(int i=0;i<nv.size();i++)
    {

        float mg=sqrt(nv[i](X)*nv[i](X)+nv[i](Y)*nv[i](Y)+nv[i](Z)*nv[i](Z)); //Magnitud de cada vertice
        Tupla3f d={nv[i](X)/mg,nv[i](Y)/mg,nv[i](Z)/mg};  //Normalizamos el vector
        nv[i]=d; //lo meto en el vector de vertices
    }
}

void Malla3D::setMaterial(Material mat) {
    m.setMaterial(mat);
}
void Malla3D::setMaterialAux(Material mat) {
    m_aux.setMaterial(mat);
}

void Malla3D::setTextura(Textura *t) {
    textura=t;
}

Tupla3f Malla3D::getCentroCamara() {
    return centroNuevo;
}

void Malla3D::calcularCentroObjeto() {


    for(int i=0;i<v.size();i++)
        centroCamara=centroCamara+v[i];

    centroCamara=centroCamara/v.size();

}

void Malla3D::cambiarAmarillo(bool ponerQuitar) {
    if(ponerQuitar)
    {

        cambiarColores({247.0/255.0,247.0/255.0,73.0/255.0});

        m.setMaterial(Material({0.5,0.5,0.22648,1.0},{0.6,0.6,0.5,1.0},{0.0,0.0,0.0,1.0},0.25));
    }

    else{
        cambiarColores(c_aux[0]);
        m.setMaterial(m_aux);
    }

}

Tupla3f Malla3D::getFalso() {
    return cRaro[0];
}