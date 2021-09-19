#include "aux.h"
#include "objrevolucion.h"
#include "objply.h"
#include <bits/stdc++.h>
#include "cmath"



// *****************************************************************************
//
// Clase ObjRevolucion (práctica 2)
//
// *****************************************************************************


// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un PLY)

ObjRevolucion::ObjRevolucion() {}

ObjRevolucion::ObjRevolucion(const std::string & archivo, int num_instancias, bool tapa_sup, bool tapa_inf,bool text) {
    std::vector<Tupla3f> perfil_original;
    bool tieneTapas;
    ply::read_vertices(archivo,perfil_original);
    if(!tapa_sup && !tapa_inf)
    tieneTapas=true;
    else
        tieneTapas=false;

    crearMalla(perfil_original,num_instancias,tieneTapas,'Y',text);
    calcular_normales();
    calcularCentroObjeto();



}

// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un vector de puntos)

 
ObjRevolucion::ObjRevolucion(std::vector<Tupla3f> archivo, int num_instancias, bool tapa_sup, bool tapa_inf,bool text) {
    bool tieneTapas;
    if(!tapa_sup && !tapa_inf)
        tieneTapas=true;
    else
        tieneTapas=false;
    crearMalla(archivo,num_instancias,tieneTapas,'Y',text);
    calcular_normales();
    calcularCentroObjeto();

}

void ObjRevolucion::crearMalla(std::vector<Tupla3f> perfil_original, int num_instancias,const bool conTapas,char rotacion,bool text) {
    int N = num_instancias;
    num_instanciasSumar = N;
    int M = perfil_original.size();
    double rotacionAngulo;
    //Creacion de la tabla de vértices
    Tupla3f VerticeRotado;
    v.clear();


    //MIRO LA TOPOLOGÍA

    if (rotacion == 'Y' && (perfil_original.at(0)(Y) > perfil_original.at(perfil_original.size() - 1)(Y)))
        std::reverse(perfil_original.begin(), perfil_original.end());
    else if (rotacion == 'X' && (perfil_original.at(0)(X) > perfil_original.at(perfil_original.size() - 1)(X)))
        std::reverse(perfil_original.begin(), perfil_original.end());
    if (rotacion == 'Z' && (perfil_original.at(0)(Z) > perfil_original.at(perfil_original.size() - 1)(Z)))
        std::reverse(perfil_original.begin(), perfil_original.end());


    for (int i = 0; i < N; i++) {
        rotacionAngulo = 2 * PI * i / N;
        for (int j = 0; j < M; j++) {
            Tupla3f verticePerfil = perfil_original.at(j);
            if (rotacion == 'Y') {
                VerticeRotado(X) = cos(rotacionAngulo) * verticePerfil(X) + sin(rotacionAngulo) * verticePerfil(Z);
                VerticeRotado(Y) = verticePerfil(Y);
                VerticeRotado(Z) = -sin(rotacionAngulo) * verticePerfil(X) + cos(rotacionAngulo) * verticePerfil(Z);
            } else if (rotacion == 'X') {
                VerticeRotado(X) = verticePerfil(X);
                VerticeRotado(Y) = cos(rotacionAngulo) * verticePerfil(Y) - sin(rotacionAngulo) * verticePerfil(Z);
                VerticeRotado(Z) = sin(rotacionAngulo) * verticePerfil(Y) + cos(rotacionAngulo) * verticePerfil(Z);
            } else if (rotacion == 'Z') {
                VerticeRotado(X) = cos(rotacionAngulo) * verticePerfil(X) - sin(rotacionAngulo) * verticePerfil(Y);
                VerticeRotado(Y) = sin(rotacionAngulo) * verticePerfil(X) + cos(rotacionAngulo) * verticePerfil(Y);
                VerticeRotado(Z) = verticePerfil(Z);
            }
            v.push_back(VerticeRotado);

        }


    }

    if (text) {
        num_instanciasSumar++;
        for (int z = 0; z < perfil_original.size(); z++)
            v.push_back(perfil_original[z]);
    }

    /*
    for(int i=0; i<perfil_original.size();i++)
    {
        std::cout<<v[i](X)<<" "<<v[i](Y)<<" "<<v[i](Z)<<std::endl;
    }
    printf("COMPARAMOS\n");
    for(int i=v.size()-perfil_original.size(); i<v.size();i++)
    {
        std::cout<<v[i](X)<<" "<<v[i](Y)<<" "<<v[i](Z)<<std::endl;
    }
    */



    //Creacion de la tabla de triángulos
    f.clear();
    if (!conTapas) {
        crearTapas(perfil_original, true, true, rotacion);
    }

    int a, b;
    if (!text)
    {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M - 1; j++) {

                a = M * i + j;
                b = M * ((i + 1) % N) + j;
                f.push_back(Tupla3i{a, b, b + 1});
                f.push_back(Tupla3i{a, b + 1, a + 1});

            }
        }
    }
    if(text)
    {

        for(int i=0;i<N-1;i++)
        {
            for(int j=0;j<M-1;j++)
            {

                a=M*i+j;
                b=M*((i+1) % N)+j;
                f.push_back(Tupla3i {a,b,b+1});
                f.push_back(Tupla3i {a,b+1,a+1});

            }
        }

        for(int i=0;i<M-1;i++)
        {
            a=M*(N-1)+i;
            b=(M*N)+i;
            f.push_back(Tupla3i {a,b,b+1});
            f.push_back(Tupla3i {a,b+1,a+1});
        }



    }
    if(text) {
        calcularTexturas(perfil_original, num_instancias);

    }


    /*
    for(Tupla3f t: v)
    {
        std::cout<<t(X)<<" "<<t(Y)<<" "<<t(Z)<<std::endl;
    }
    */
}

void ObjRevolucion::crearTapas(std::vector <Tupla3f> perfil_original, bool tapa_sup, bool tapa_inf,char rotacion) {



    if(tapa_inf)
    {

        //buscamos el punto de y mas bajo
        std::vector<int> IndiceBajos;

        if(rotacion=='Y') {
            for (int i = 0; i < perfil_original.size(); i++) {
                if (perfil_original.at(i)(Y) < Coordenada_masBaja)
                    Coordenada_masBaja = perfil_original.at(i)(Y);
            }

            PuntoMasBajo = {0.0, Coordenada_masBaja, 0.0};
            //buscamos los vertices que esten a la misma altura y lo guardamos en un vector de indices

            for (int i = 0; i < v.size(); i++) {
                if (Coordenada_masBaja == v.at(i)(Y))
                    IndiceBajos.push_back(i);
            }
            v.push_back(PuntoMasBajo);
            //Hacemos triangulo con el punto mas bajo y los puntos de este indice
        }
        else if (rotacion=='X')
            {
                for (int i = 0; i < perfil_original.size(); i++) {
                    if (perfil_original.at(i)(X) < Coordenada_masBaja)
                        Coordenada_masBaja = perfil_original.at(i)(X);
                }

                PuntoMasBajo = {Coordenada_masBaja,0.0,0.0};
                //buscamos los vertices que esten a la misma altura y lo guardamos en un vector de indices

                for (int i = 0; i < v.size(); i++) {
                    if (Coordenada_masBaja == v.at(i)(X))
                        IndiceBajos.push_back(i);
                }
                v.push_back(PuntoMasBajo);
                //Hacemos triangulo con el punto mas bajo y los puntos de este indice
            }
        else if (rotacion=='Z')
        {
            for (int i = 0; i < perfil_original.size(); i++) {
                if (perfil_original.at(i)(Z) < Coordenada_masBaja)
                    Coordenada_masBaja = perfil_original.at(i)(Z);
            }

            PuntoMasBajo = {0.0,0.0,Coordenada_masBaja};
            //buscamos los vertices que esten a la misma altura y lo guardamos en un vector de indices

            for (int i = 0; i < v.size(); i++) {
                if (Coordenada_masBaja == v.at(i)(Z))
                    IndiceBajos.push_back(i);
            }
            v.push_back(PuntoMasBajo);
            //Hacemos triangulo con el punto mas bajo y los puntos de este indice
        }

        for(int i=0; i<IndiceBajos.size()-1;i++)
        {

            f.push_back(Tupla3i {(int)v.size()-1,IndiceBajos.at(i+1),IndiceBajos.at(i) });

        }
        f.push_back(Tupla3i {(int)v.size()-1,IndiceBajos.at(0),IndiceBajos.at(IndiceBajos.size()-1)});
    }

    if(tapa_sup) {

        //buscamos el punto de y mas alto
        std::vector<int> IndiceAltos;
        if(rotacion=='Y')
        {
        for (int i = 0; i < perfil_original.size(); i++) {
            if (Coordenada_masAlta < perfil_original.at(i)(Y))
                Coordenada_masAlta = perfil_original.at(i)(Y);
        }
        PuntoMasAlto = {0.0, Coordenada_masAlta, 0.0};

        //buscamos los vertices que esten a la misma altura y lo guardamos en un vector de indices

        for (int i = 0; i < v.size(); i++) {
            if (Coordenada_masAlta == v.at(i)(Y))
                IndiceAltos.push_back(i);
        }
        v.push_back(PuntoMasAlto);
    }

        else if(rotacion=='X')
        {
            for (int i = 0; i < perfil_original.size(); i++) {
                if (Coordenada_masAlta < perfil_original.at(i)(X))
                    Coordenada_masAlta = perfil_original.at(i)(X);
            }
            PuntoMasAlto = {Coordenada_masAlta,0.0 ,0.0};

            //buscamos los vertices que esten a la misma altura y lo guardamos en un vector de indices

            for (int i = 0; i < v.size(); i++) {
                if (Coordenada_masAlta == v.at(i)(X))
                    IndiceAltos.push_back(i);
            }
            v.push_back(PuntoMasAlto);
        }

        else if(rotacion=='Z')
        {
            for (int i = 0; i < perfil_original.size(); i++) {
                if (Coordenada_masAlta < perfil_original.at(i)(Z))
                    Coordenada_masAlta = perfil_original.at(i)(Z);
            }
            PuntoMasAlto = {0.0 ,0.0,Coordenada_masAlta};

            //buscamos los vertices que esten a la misma altura y lo guardamos en un vector de indices

            for (int i = 0; i < v.size(); i++) {
                if (Coordenada_masAlta == v.at(i)(Z))
                    IndiceAltos.push_back(i);
            }
            v.push_back(PuntoMasAlto);
        }
        //Hacemos triangulo con el punto mas alto y los puntos de este indice
        for(int i=0; i<IndiceAltos.size()-1;i++)
        {

            f.push_back(Tupla3i {(int)v.size()-1,IndiceAltos.at(i),IndiceAltos.at(i+1) } );

        }
        f.push_back(Tupla3i {(int)v.size()-1,IndiceAltos.at(IndiceAltos.size()-1),IndiceAltos.at(0)});
    }


    /*
     if(tapa_inf)
    {

        //buscamos el punto de y mas bajo

        Y_masBaja = perfil_original.at(0);
        for (int i = 1; i < perfil_original.size(); i++) {
            if (perfil_original.at(i)(Y) < Y_masBaja(Y))
                Y_masBaja = perfil_original.at(i);
        }
        if(!(Y_masBaja(X)==0.0 && Y_masBaja(Z)==0))
        {
            PuntoMasBajo={0.0,Y_masBaja(Y),0.0};
            //buscamos los vertices que esten a la misma altura y lo guardamos en un vector de indices
            std::vector<int> IndiceBajos;
            for (int i = 0; i < v.size(); i++) {
                if ( Y_masBaja(Y)==v.at(i)(Y))
                    IndiceBajos.push_back(i);
            }
            v.push_back(PuntoMasBajo);
            //Hacemos triangulo con el punto mas bajo y los puntos de este indice


            for(int i=0; i<IndiceBajos.size()-1;i++)
            {

                f.push_back(Tupla3i {v.size()-1,IndiceBajos.at(i+1),IndiceBajos.at(i) } );

            }
            f.push_back(Tupla3i {v.size()-1,IndiceBajos.at(0),IndiceBajos.at(IndiceBajos.size()-1)});
        }
        }





    if(tapa_sup) {

        //buscamos el punto de y mas alto

        Y_masAlta=perfil_original.at(0);
        for (int i = 0; i < perfil_original.size(); i++) {
            if ( Y_masAlta(Y) < perfil_original.at(i)(Y))
                Y_masAlta=perfil_original.at(i);
        }
        if(!(Y_masAlta(X)==0.0 && Y_masAlta(Z)==0))
        {
            PuntoMasAlto={0.0,Y_masAlta(Y),0.0};
            //buscamos los vertices que esten a la misma altura y lo guardamos en un vector de indices
            std::vector<int>IndiceAltos;
            for (int i = 0; i < v.size(); i++) {
                if ( Y_masAlta(Y)==v.at(i)(Y))
                    IndiceAltos.push_back(i);
            }
            v.push_back(PuntoMasAlto);

            //Hacemos triangulo con el punto mas alto y los puntos de este indice
            for(int i=0; i<IndiceAltos.size()-1;i++)
            {

                f.push_back(Tupla3i {v.size()-1,IndiceAltos.at(i),IndiceAltos.at(i+1) } );

            }
            f.push_back(Tupla3i {v.size()-1,IndiceAltos.at(IndiceAltos.size()-1),IndiceAltos.at(0)});
        }
        }
    */

}


GLuint CrearVBO ( GLuint tipo_vbo , GLuint tamanio_bytes , GLvoid * puntero_ram )
{
    GLuint id_vbo ;      // resultado: identificador de VBO
    glGenBuffers ( 1 , & id_vbo ); // crear nuevo VBO, obtener identificador (nunca 0)
    glBindBuffer ( tipo_vbo , id_vbo ); // activar el VBO usando su identificador

// esta instrucción hace la transferencia de datos desde RAM hacia GPU

    glBufferData ( tipo_vbo , tamanio_bytes , puntero_ram , GL_STATIC_DRAW );
    glBindBuffer ( tipo_vbo , 0 ); // desactivación del VBO (activar 0)
    return id_vbo ; // devolver el identificador resultado
}


void ObjRevolucion::inicializarColores() {
    for(int i=0;i<v.size();i++)
    {
        cLineas.push_back(Tupla3f{0,0,0});
        cSolido.push_back(Tupla3f{0,0,1});
        cPuntos.push_back(Tupla3f{1,1,0});
        cPares.push_back(Tupla3f{1,0,0});
        cImpares.push_back(Tupla3f{0,0.5019,0});
    }
}

void ObjRevolucion::draw_AjedrezInmediato(bool tapa,bool TenemosCono)
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT,0,v.data());
    carasPares.clear();
    carasImpares.clear();

    if(tapa) {
        for (int i = 0; i < f.size(); i++) {
            if (i % 2 == 0) {
                carasPares.push_back(f.at(i));
            } else {
                carasImpares.push_back(f.at(i));
            }

        }
    }
    else if(!tapa && TenemosCono)
    {
        for (int i = num_instanciasSumar; i < f.size(); i++) {
            if (i % 2 == 0) {
                carasPares.push_back(f.at(i));
            } else {
                carasImpares.push_back(f.at(i));
            }

        }
    }
    else if(!tapa)
    {
        for (int i = num_instanciasSumar*2; i < f.size(); i++) {
            if (i % 2 == 0) {
                carasPares.push_back(f.at(i));
            } else {
                carasImpares.push_back(f.at(i));
            }

        }
    }

    glEnableClientState( GL_COLOR_ARRAY ); // habilitar uso de array de col.
    glColorPointer( 3, GL_FLOAT, 0, cPares.data()); // especifíca puntero a colores

    glDrawElements(GL_TRIANGLES, carasPares.size()*3 ,GL_UNSIGNED_INT, carasPares.data());

    glColorPointer( 3, GL_FLOAT, 0, cImpares.data()); // especifíca puntero a colores

    glDrawElements(GL_TRIANGLES, carasImpares.size()*3 ,GL_UNSIGNED_INT, carasImpares.data());

    glDisableClientState(GL_VERTEX_ARRAY);

}


void ObjRevolucion::draw_ModoInmediato(char color,bool tapa,bool TenemosCono,bool suave,bool plano,bool ra)
{

//Por defecto se dibuja en modo inmediato


    if(color=='A')
    {
        draw_AjedrezInmediato(tapa,TenemosCono);
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
                glColorPointer(3, GL_FLOAT, 0, cRaro.data());
        }

        if(suave) {
            glShadeModel(GL_SMOOTH);
            m.aplicar();
        }
        if(plano)
        {
            glShadeModel(GL_FLAT);
            m.aplicar();
        }



        if(textura!= nullptr)
        {
            textura->activar();
            glEnableClientState ( GL_TEXTURE_COORD_ARRAY );
            glTexCoordPointer ( 2 , GL_FLOAT , 0 , ct.data());
        }


        glEnableClientState(GL_VERTEX_ARRAY);

        if(plano || suave)
            glEnableClientState( GL_NORMAL_ARRAY );

        glVertexPointer(3, GL_FLOAT, 0, v.data());

        if(plano || suave)
            glNormalPointer( GL_FLOAT, 0, nv.data() );


        if (tapa)
            glDrawElements(GL_TRIANGLES, f.size() * 3, GL_UNSIGNED_INT, f.data());
        else if (TenemosCono && !tapa)
            glDrawElements(GL_TRIANGLES, f.size() * 3, GL_UNSIGNED_INT, f.data() + num_instanciasSumar);
        else if (!tapa) {
            glDrawElements(GL_TRIANGLES, f.size() * 3, GL_UNSIGNED_INT, f.data() + num_instanciasSumar * 2);
        }


        glDisableClientState(GL_VERTEX_ARRAY);
        if(plano || suave)
            glDisableClientState( GL_NORMAL_ARRAY );

        glDisable(GL_TEXTURE_2D);
    }
}

void ObjRevolucion::draw_AjedrezDiferido(bool tapa,bool TenemosCono)
{

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    // especificar localización y formato de la tabla de vértices, habilitar tabla
    if(id_vbo_ver==0)
    {
        id_vbo_ver= CrearVBO(GL_ARRAY_BUFFER,v.size()*sizeof(Tupla3f),v.data());
    }
    carasImpares.clear();
    carasPares.clear();
    if(tapa) {
        for (int i = 0; i < f.size(); i++) {
            if (i % 2 == 0) {
                carasPares.push_back(f.at(i));
            } else {
                carasImpares.push_back(f.at(i));
            }
        }
    }
    else if(!tapa && TenemosCono){
        for (int i = num_instanciasSumar; i < f.size(); i++) {
            if (i % 2 == 0) {
                carasPares.push_back(f.at(i));
            } else {
                carasImpares.push_back(f.at(i));
            }
        }
    }
    else if(!tapa)
    {
        for (int i = num_instanciasSumar*2; i < f.size(); i++) {
            if (i % 2 == 0) {
                carasPares.push_back(f.at(i));
            } else {
                carasImpares.push_back(f.at(i));
            }
        }
    }

    if(tapa) {

        if (id_vbo_tri_par == 0)
            id_vbo_tri_par = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, carasPares.size() * sizeof(Tupla3i), carasPares.data());

        if (id_vbo_tri_impar == 0)
            id_vbo_tri_impar = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, carasImpares.size() * sizeof(Tupla3i), carasImpares.data());
    }
    if(!tapa && TenemosCono)
    {
        if (id_vbo_tri_par_Cono == 0)
            id_vbo_tri_par_Cono = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, carasPares.size() * sizeof(Tupla3i), carasPares.data());

        if (id_vbo_tri_impar_Cono == 0)
            id_vbo_tri_impar_Cono = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, carasImpares.size() * sizeof(Tupla3i), carasImpares.data());
    }

    if(!tapa)
    {
        if (id_vbo_tri_par_tapas == 0)
            id_vbo_tri_par_tapas = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, carasPares.size() * sizeof(Tupla3i), carasPares.data());

        if (id_vbo_tri_impar_tapas == 0)
            id_vbo_tri_impar_tapas = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, carasImpares.size() * sizeof(Tupla3i), carasImpares.data());
    }


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

    if(tapa)
        glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER , id_vbo_tri_par ); // activar VBO de triángulos
    else if(!tapa && TenemosCono)
        glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER , id_vbo_tri_par_Cono );
    else if(!tapa)
        glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER , id_vbo_tri_par_tapas );


    glDrawElements ( GL_TRIANGLES , 3*carasPares.size () , GL_UNSIGNED_INT , 0 );//Dibujar triangulos
    glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER , 0 ); // desactivar VBO de triángulos


    //Para las caras impares metemos color verde
    vbo_verde= CrearVBO(GL_ARRAY_BUFFER,cImpares.size()*sizeof(Tupla3f),cImpares.data());
    glEnableClientState( GL_COLOR_ARRAY ); // habilitar uso de array de col.
    glBindBuffer ( GL_ARRAY_BUFFER , vbo_verde);
    glColorPointer( 3, GL_FLOAT, 0, 0);
    glBindBuffer ( GL_ARRAY_BUFFER , vbo_verde);

    if(tapa)
        glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER , id_vbo_tri_impar ); // activar VBO de triángulos
    else if(!tapa && TenemosCono)
        glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER , id_vbo_tri_impar_Cono );
    else if(!tapa)
        glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER , id_vbo_tri_impar_tapas );


    glDrawElements ( GL_TRIANGLES , 3*carasImpares.size () , GL_UNSIGNED_INT , 0 );//Dibujar traingulos
    glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER , 0 ); // desactivar VBO de triángulos


    // desactivar uso de array de vértices
    glDisableClientState ( GL_VERTEX_ARRAY );
}




void ObjRevolucion::draw_ModoDiferido(char color,bool tapa,bool TenemosCono,bool suave, bool plano)
{

    if(color=='A')
    {
        draw_AjedrezDiferido(tapa,TenemosCono);
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
        if(id_vbo_normales)
        {
            id_vbo_normales= CrearVBO(GL_ELEMENT_ARRAY_BUFFER, nv.size() * sizeof(Tupla3f), nv.data());
        }

        if(id_vbo_tri_Cono==0 && !tapa && TenemosCono)
        {
            id_vbo_tri_Cono = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, f.size() * sizeof(Tupla3i), f.data() + num_instanciasSumar);
        }
        if(id_vbo_tri_tapas==0 && !tapa)
        {
            id_vbo_tri_tapas=CrearVBO(GL_ELEMENT_ARRAY_BUFFER, f.size() * sizeof(Tupla3i), f.data() + num_instanciasSumar * 2);
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

        glBindBuffer(GL_ARRAY_BUFFER, id_vbo_ver); // activar VBO de vértices

        if(plano || suave)
            glBindBuffer(GL_NORMAL_ARRAY, id_vbo_normales); // activar VBO de normales

        glVertexPointer(3, GL_FLOAT, 0, 0); // especifica formato y offset (=0)

        if(plano || suave)
            glNormalPointer( GL_FLOAT, 0, 0 );

        glBindBuffer(GL_ARRAY_BUFFER, 0); // desactivar VBO de vértices.

        if(plano || suave)
            glBindBuffer(GL_NORMAL_ARRAY, 0);

        glEnableClientState(GL_VERTEX_ARRAY); // habilitar tabla de vértices

        if(plano || suave)
            glEnableClientState(GL_NORMAL_ARRAY);

// visualizar triángulos con glDrawElements (puntero a tabla == 0)


        if(tapa)
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_vbo_tri); // activar VBO de triángulos
        else if(!tapa && TenemosCono)
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_vbo_tri_Cono);
        else if(!tapa)
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_vbo_tri_tapas);



        glDrawElements(GL_TRIANGLES, f.size() * 3, GL_UNSIGNED_INT, 0);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // desactivar VBO de triángulos

// desactivar uso de array de vértices
        glDisableClientState(GL_VERTEX_ARRAY);
        if(plano || suave)
            glDisableClientState(GL_NORMAL_ARRAY);

        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        glDisable(GL_TEXTURE_2D);
    }
}




// -----------------------------------------------------------------------------
// Función de visualización de la malla,
// puede llamar a  draw_ModoInmediato o bien a draw_ModoDiferido

void ObjRevolucion::drawObj(unsigned int modo,char color,bool tapa,bool TenemosCono,bool suave, bool plano,bool ra)
{



    if(modo==1)
        draw_ModoInmediato(color,tapa,TenemosCono,suave,plano,ra);
    else if(modo==2)
        draw_ModoDiferido(color,tapa,TenemosCono,suave,plano);


}

void ObjRevolucion::calcularTexturas(std::vector<Tupla3f> perfil_original, int num_instancias) {

    float N=num_instancias;
    float M=perfil_original.size();
    std::vector<float>distancias;

    float s,t;
    distancias.resize(M);
    distancias[0]=0;
    Tupla3f resta;
    for(int i=1;i<M;i++)
    {
        resta=v[i]-v[i-1];
        distancias[i]=distancias[i-1]+sqrtf(pow(resta(X),2)+pow(resta(Y),2)+pow(resta(Z),2));
    }

    ct.resize(v.size());
    for(int i=0; i<N+1;i++)
    {

        s=i/N;

        for(int j=0 ; j<M; j++)
        {
            t=distancias[j]/distancias[M-1];
            ct[(M*i)+j]={s,t};
            //std::cout<<ct[i](X)<<" "<<ct[i](Y)<<std::endl;
        }

    }
    /*
    for(int i=0;i<perfil_original.size();i++)
    {
        std::cout<<ct[i](X)<<" "<<ct[i](Y)<<std::endl;
    }
    */
    //std::reverse(ct.begin(),ct.end());




}
