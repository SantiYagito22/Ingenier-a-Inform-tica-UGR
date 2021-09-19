// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Malla3D.h
// -- declaraciones de clase Malla3D (mallas indexadas) y derivados
//
// #############################################################################

#ifndef MALLA3D_H_INCLUDED
#define MALLA3D_H_INCLUDED

#include "aux.h"
#include "material.h"
#include "Textura.h"


// *****************************************************************************
//
// clase para objetos 3D (mallas indexadas)
//
// *****************************************************************************

class Malla3D
{
   private:
   GLuint id_vbo_ver=0,  id_vbo_tri=0, vbo_solido, vbo_lineas, vbo_puntos, vbo_rojo, vbo_verde,id_vbo_normales;
   GLuint id_vbo_tri_par=0,id_vbo_tri_impar=0;
   GLuint id_vbo_text=0;


   public:
    int num_instanciasSumar;
    bool raro=false;
    Tupla3f centroNuevo;
    Tupla3f centroCamara;


   // dibuja el objeto en modo inmediato
   void draw_ModoInmediato(char color,bool suave,bool plano,bool ra);

   // dibuja el objeto en modo diferido (usando VBOs)
   void draw_ModoDiferido(char color,bool suave,bool plano);

   //dibuja el objeto en modo ajedrez e inmediato
   void draw_AjedrezInmediato();

    //dibuja el objeto en modo ajedrez e inmediato
    void draw_AjedrezDiferido();

    GLuint CrearVBO ( GLuint tipo_vbo , GLuint tamanio_bytes , GLvoid * puntero_ram );

   // función que redibuja el objeto
   // está función llama a 'draw_ModoInmediato' (modo inmediato)
   // o bien a 'draw_ModoDiferido' (modo diferido, VBOs)
   void draw(unsigned int modo,char color,bool suave,bool plano,bool ra);

   void inicializarColores();

   void setColorRaro(Tupla3f color);

   void cambiarColores(Tupla3f colorNuevo);
   void setColorFalso(Tupla3f col);
   void setMaterial(Material mat);
    void setMaterialAux(Material mat);
   void setTextura(Textura * t);
   Tupla3f getCentroCamara();
    void calcularCentroObjeto();
    void setColorAux(Tupla3f col);

    Tupla3f getFalso();

    void cambiarAmarillo(bool ponerQuitar);

   protected:
   
   
   void calcular_normales() ; // calcula tabla de normales de vértices (práctica 3)
    Material m;
   std::vector<Tupla3f> v ;   // tabla de coordenadas de vértices (una tupla por vértice, con tres floats)
   std::vector<Tupla3i> f ; // una terna de 3 enteros por cada cara o triángulo
   std::vector<Tupla3f> cSolido; //lista de colores a usar por vertices.
   std::vector<Tupla3f> cRaro;
   std::vector<Tupla3f> cPuntos; //lista de colores a usar por vertices.
   std::vector<Tupla3f> cLineas; //lista de colores para las lineas
   std::vector<Tupla3i> carasPares; //caras pares
   std::vector<Tupla3i> carasImpares; //caras impares
   std::vector<Tupla3f> cPares; //lista de colores para las caras pares
   std::vector<Tupla3f> cImpares; //lista de colores para las caras impares
   std::vector<Tupla3f>nv; //lista de normales de vértices
   Textura * textura=nullptr;
   std::vector<Tupla2f>ct; //tabla de coordenadas de textura
   std::vector<Tupla3f> c_aux;
   Material m_aux;









   
   



   
};


#endif
