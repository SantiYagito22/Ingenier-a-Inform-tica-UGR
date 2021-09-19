// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Cubo.h

//
// #############################################################################

#ifndef OBJREVOLUCION_H_INCLUDED
#define OBJREVOLUCION_H_INCLUDED

#include "aux.h"
#include "malla.h"

// *****************************************************************************
//
// clases derivadas de Malla3D (definen constructores específicos)
//
// *****************************************************************************

// *****************************************************************************
// Cubo con centro en el origen y lado unidad por defecto
// (tiene 9 vertices y 6 caras)

class ObjRevolucion : public Malla3D
{

private:
    GLuint id_vbo_ver=0,  id_vbo_tri=0, vbo_solido, vbo_lineas, vbo_puntos, vbo_rojo, vbo_verde,id_vbo_normales;
    GLuint id_vbo_tri_par=0,id_vbo_tri_impar=0,id_vbo_tri_par_Cono=0,id_vbo_tri_impar_Cono=0,id_vbo_tri_par_tapas=0,id_vbo_tri_impar_tapas=0;
    GLuint id_vbo_tri_Cono=0, id_vbo_tri_tapas=0;
    GLuint id_vbo_text=0;
   public:
    ObjRevolucion();
   ObjRevolucion(const std::string & archivo, int num_instancias, bool tapa_sup=true, bool tapa_inf=true, bool text=false);
   ObjRevolucion(std::vector<Tupla3f> archivo, int num_instancias, bool tapa_sup=true, bool tapa_inf=true, bool text=false);
   void drawObj(unsigned int modo,char color,bool tapa,bool TenemosCono,bool suave,bool plano,bool ra);
   void draw_ModoDiferido(char color,bool tapa,bool TenemosCono,bool suave,bool plano);
   void draw_AjedrezDiferido(bool tapa,bool TenemosCono);
   void draw_ModoInmediato(char color,bool tapa,bool TenemosCono,bool suave,bool plano,bool ra);
   void draw_AjedrezInmediato(bool tapa,bool TenemosCono);
   void inicializarColores();
   void draw_Suave();
   void draw_Plano();
   void calcularTexturas(std::vector<Tupla3f> perfil_original, int num_instancias);



protected:
    void crearMalla(std::vector<Tupla3f> perfil_original, int num_instancias,const bool conTapas,char rotacion,bool text);
    void crearTapas(std::vector<Tupla3f> perfil_original, bool tapa_sup, bool tapa_inf,char rotacion);
    const double PI = 3.14159265358979323846;
    float Coordenada_masAlta=-MAXFLOAT,Coordenada_masBaja=MAXFLOAT;
    Tupla3f PuntoMasAlto,PuntoMasBajo;


} ;




#endif
