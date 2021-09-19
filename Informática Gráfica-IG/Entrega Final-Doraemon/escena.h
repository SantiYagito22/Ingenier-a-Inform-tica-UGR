#ifndef _ESCENA_H
#define _ESCENA_H

#include "ejes.h"
#include "malla.h"
#include "cubo.h"
#include "cilindro.h"
#include "cono.h"
#include "esfera.h"
#include "tetraedro.h"
#include "objply.h"
#include "objrevolucion.h"
#include "luz.h"
#include "luzdireccional.h"
#include "luzposicional.h"
#include "semiesfera.h"
#include "doraemon.h"
#include "pared.h"
#include "camara.h"
#include "puerta.h"

typedef enum {NADA, SELOBJETO,SELVISUALIZACION,SELDIBUJADO,MENUILUMINACION,MENUAUTOMATICO,MENUMANUAL,MENCAMARA} menu;
class Escena
{

   private:



    std::vector<int>  visualizacion;
    bool ajedrez=false,tapa=true,TenemosCono=false,hayLuz=false,luz1=false,luz2=false,variacionAlfa=false,variacionBeta=false,suave=false,plano=false;
    unsigned int modo=1;
    float vuelo=800.0;
    bool momentoBalon=false;
    char letra;
    bool animarEscena=false;
    bool vuela=false,helice=false,cabezaGira=false,brazoGira=false,colaMov=false;
    bool puertaMagica=false;
    bool animar=false,direccionVuelo=true,luzAnimar=false;
    float salePuerta=0,escalaPuerta=0;
    int camaraActiva=0;
    float abrePuerta=90;
    bool camaraActivada=false;
    bool dormido=false;
    float vuelta=-1;
    float vePuerta=0;
    bool movCabeza=true;
    bool golpea=false;
    bool escenaCampo=false;
    float golpe=0;
    bool levanta=false;
    float movBalonx=660,movBalony=600;
    bool bajaBrazos=true,escenaHabitacion=false;
    bool animacionTerminada=false;

 // ** PARÁMETROS DE LA CÁMARA (PROVISIONAL)
       
       // variables que definen la posicion de la camara en coordenadas polares
   GLfloat Observer_distance;
   GLfloat Observer_angle_x;
   GLfloat Observer_angle_y;

   // variables que controlan la ventana y la transformacion de perspectiva
   GLfloat Width, Height, Front_plane, Back_plane;

    // Transformación de cámara
	void change_projection();
	void change_observer();
    


   void clear_window();

   menu modoMenu=NADA;
   // Objetos de la escena
   Ejes ejes;
   Cubo * cubo = nullptr ; // es importante inicializarlo a 'nullptr'
   Tetraedro * tetraedro= nullptr ; // es importante inicializarlo a 'nullptr'
   ObjPLY * ObjetoPly=nullptr;
   ObjRevolucion * peon1= nullptr;
   ObjRevolucion * peon2=nullptr;
   Cilindro * cilindro=nullptr;
   Cono * cono=nullptr;
   Esfera * esfera=nullptr;
   Esfera * esferaLuz= nullptr;
   LuzDireccional * LD= nullptr;
   LuzPosicional * LP= nullptr;
   Material  esmeralda,oro,mdifuso,mespecular;
   Doraemon * doraemon= nullptr;
   Pared * pared= nullptr;
    Pared * cielo= nullptr;
    Pared * campo= nullptr;
    Pared * cesped= nullptr;
   Textura * habitacion= nullptr;
    ObjRevolucion * lata= nullptr;
    ObjRevolucion * lataSup= nullptr;
    ObjRevolucion * lataInf= nullptr;
    Esfera * balon=nullptr;
    Puerta * puerta= nullptr;
    std::vector<Camara> camaras;
    Camara * PrimeraPersonaPerspectiva= nullptr;
    Camara * PrimeraPersonaOrtogonal= nullptr;
    Camara * SegundaPersonaPerspectiva= nullptr;

    GLfloat matriz[16];



   public:
    bool estadoRaton=false;
    int xant=0,yant=0;

    void dibujarObjetos(char letra);
    void dibujaSeleccion();
    void CentrarCamaraClick(int x,int y);
    void animarModeloJerarquico();

    Escena();
	void inicializar( int UI_window_width, int UI_window_height );
	void redimensionar( int newWidth, int newHeight ) ;

	// Dibujar
	void dibujar() ;

	// Interacción con la escena
	bool teclaPulsada( unsigned char Tecla1, int x, int y ) ;
	void teclaEspecial( int Tecla1, int x, int y );

	void ratonMovido(int x,int y);


};
#endif
