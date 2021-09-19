

#include "aux.h"     // includes de OpenGL/glut/glew, windows, y librería std de C++
#include "escena.h"
#include "malla.h" // objetos: Cubo y otros....
#include "objrevolucion.h"
#include "luz.h"
//**************************************************************************
// constructor de la escena (no puede usar ordenes de OpenGL)
//**************************************************************************



Escena::Escena()
{
   Front_plane       = 50.0;
   Back_plane        = 2000.0;
   Observer_distance = 4*Front_plane;
   Observer_angle_x  = 0.0 ;
   Observer_angle_y  = 0.0 ;

   ejes.changeAxisSize( 5000 );
   tetraedro= new Tetraedro();
   cubo=new Cubo(50.0);
   cilindro=new Cilindro(2,50,25,50,'Y');
   peon1=new ObjRevolucion("plys/peon.ply",50,true,true);
   peon2=new ObjRevolucion("plys/peon.ply",50,true,true);
   cono=new Cono(2,50,50,25,'Y');
   esfera=new Esfera(20,40,25,'Y');
   esferaLuz=new Esfera(20,40,25,'Y');




    doraemon=new Doraemon();

   for(int i=0;i<3;i++)
   {
      visualizacion.push_back(1);
   }

   esfera->inicializarColores();
   cono->inicializarColores();
   cilindro->inicializarColores();
   cubo->inicializarColores();
   tetraedro->inicializarColores();
   peon1->inicializarColores();
   peon2->inicializarColores();
   esferaLuz->inicializarColores();



   cilindro->cambiarColores({0.0,0.0,0.0});
   esfera->cambiarColores({30.0/255.0,142.0/255.0,255.0/255.0});


    LP=new LuzPosicional(Tupla3f{100.0,200.0,0.0},GL_LIGHT1,{1.0,1.0,1.0,1.0},{1.0,1.0,1.0,1.0},{1.0,1.0,1.0,1.0});
    LD=new LuzDireccional(Tupla2f {-100.0,200.0},GL_LIGHT2,{1.0,1.0,1.0,1.0},{1.0,1.0,1.0,1.0},{1.0,1.0,1.0,1.0});

    esmeralda=Material({0.07568,0.61424,0.07568,1.0},{0.633,0.727811,0.633,1.0},{0.0215,0.1745,0.0215,1.0},0.6);
    oro=Material({0.75164,0.60648,0.22648,0.5},{0.628281,0.555802,0.366065,0.5},{0.24725,0.1995,0.0745,0.5},0.4);
    mdifuso=Material({1.0,1.0,1.0,1.0}, {1.0,1.0,1.0,1.0}, {0.0,0.0,0.0,0.0}, 0.0);
    mespecular=Material({0.0,0.0,0.0,1.0}, {0.0,0.0,0.0,0.0}, {1.0,1.0,1.0,1.0}, 1.0);
    cubo->setMaterial(esmeralda);
    tetraedro->setMaterial(esmeralda);
    esfera->setMaterial(oro);
    cilindro->setMaterial(oro);
    cono->setMaterial(oro);
    peon1->setMaterial(mdifuso);
    peon2->setMaterial(mespecular);
    esferaLuz->setMaterial(esmeralda);




}
//**************************************************************************
// inicialización de la escena (se ejecuta cuando ya se ha creado la ventana, por
// tanto sí puede ejecutar ordenes de OpenGL)
// Principalmemnte, inicializa OpenGL y la transf. de vista y proyección
//**************************************************************************

void Escena::inicializar( int UI_window_width, int UI_window_height )
{
	glClearColor( 1.0, 1.0, 1.0, 1.0 );// se indica cual sera el color para limpiar la ventana	(r,v,a,al)
	glEnable( GL_DEPTH_TEST );	// se habilita el z-bufer
	Width  = UI_window_width/10;
	Height = UI_window_height/10;
   change_projection( float(UI_window_width)/float(UI_window_height) );
	glViewport( 0, 0, UI_window_width, UI_window_height );

}



// **************************************************************************
//
// función de dibujo de la escena: limpia ventana, fija cámara, dibuja ejes,
// y dibuja los objetos
//
// **************************************************************************

void Escena::dibujar()
{

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Limpiar la pantalla
	change_observer();
    glEnable(GL_NORMALIZE);
    glEnable(GL_CULL_FACE);


        glDisable(GL_LIGHTING);
        LP->desactivar();
        LD->desactivar();
        //ejes.draw();


        if(hayLuz) {
            glEnable(GL_LIGHTING);
            if(luz1) {
                LP->activar();
                dibujarObjetos('N');
            }
            if(luz2)
            {
                LD->activar();
                dibujarObjetos('N');
            }
        }



    /*
    glPushMatrix();
    glTranslatef(100.0,200.0,0.0);
    esferaLuz->drawObj(modo,'S',tapa,false,suave,plano);
    glPopMatrix();
    */



    //visualizacion por defecto
    if(visualizacion[0]==1 && visualizacion[1]==1 && visualizacion[2]==1 && !ajedrez && !hayLuz)
        {
            visualizacion[2]=-1;
        }



   if(visualizacion[0]==-1 && !ajedrez && !hayLuz)
   {
       glPointSize(5);
       glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
       dibujarObjetos('P');
   }

   if(visualizacion[1]==-1 && !ajedrez && !hayLuz)
   {

       glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
       dibujarObjetos('L');
   }

   if(visualizacion[2]==-1 && !ajedrez && !hayLuz)
   {

       glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
       dibujarObjetos('S');
   }

   if(ajedrez && !hayLuz)
       dibujarObjetos('A');


}


void Escena::dibujarObjetos(char letra)
{
/*
    CUBO
    glPushMatrix();
    glTranslatef(0.0,0.0,0.0);
    cubo->draw(modo,letra,suave,plano);
    glPopMatrix();

    TETRAEDRO
    glPushMatrix();
    glTranslatef(100.0,0.0,0.0);
    tetraedro->draw(modo,letra,suave,plano);
    glPopMatrix();

    */

    //CILINDRO

    if(vuelo==75)
        direccionVuelo=false;
    if(vuelo==-75)
        direccionVuelo=true;

    if(animar){
        if(direccionVuelo)
            vuelo+=1;
        else
            vuelo-=1;
    }


    glPushMatrix();
    glTranslatef(0.0,vuelo,-2.5*25);
    glScalef(0.75,0.75,0.75);
    doraemon->draw(modo,letra,tapa,false,suave,plano);
    glPopMatrix();
    


    /*
    glPushMatrix();
    glTranslatef(0.75*25,0.0,0.0);
    glRotatef(-90.0,0.0,0.0,1.0);
    glScalef(0.05,2.5,0.05);
    cilindro->drawObj(modo,letra,tapa,false,suave,plano);
    glPopMatr*25tef(0.75*25,-0.6*25,0.0);
    glRotatef(-115.0,0.0,0.0,1.0);
    glScalef(0.05,2.5,0.05);
    cilindro->drawObj(modo,letra,tapa,false,suave,plano);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.75*25,0.6*25,0.0);
    glRotatef(65.0,0.0,0.0,1.0);
    glScalef(0.05,2.5,0.05);
    cilindro->drawObj(modo,letra,tapa,false,suave,plano);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-0.75*25,0.0,0.0);
    glRotatef(90.0,0.0,0.0,1.0);
    glScalef(0.05,2.5,0.05);
    cilindro->drawObj(modo,letra,tapa,false,suave,plano);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.75*25,-0.6*25,0.0);
    glRotatef(115.0,0.0,0.0,1.0);
    glScalef(0.05,2.5,0.05);
    cilindro->drawObj(modo,letra,tapa,false,suave,plano);
    glPopMatrix();
    
    CONO
    glPushMatrix();
    glTranslatef(-150.0,0.0,0.0);
    cono->drawObj(modo,letra,tapa,true,suave,plano);
    glPopMatrix();
    

    
    ESFERA
    glPushMatrix();
    glTranslatef(0.0,7*25,0.0);
    glScalef(3.25,3.25,3.25);
    esfera->drawObj(modo,letra,tapa,false,suave,plano);
    glPopMatrix();
    

    
    glPushMatrix();
    glTranslatef(0.0,1.0*25,0.0);
    glScalef(2,2,-0.5);
    semiesfera->drawObj(modo,letra,tapa,false,suave,plano);
    glPopMatrix();

   glPushMatrix();
    glTranslatef(0.0,-1.25*25,0.2*25);
    glScalef(0.7,0.4,0.3);
    esfera->drawObj(modo,letra,tapa,false,suave,plano);
    glPopMatrix();
    

    
    PEON 1
    glPushMatrix();
    glTranslatef(200.0,0.0,0.0);
    peon1->drawObj(modo,letra,tapa,false,suave,plano);
    peon2->drawObj(modo,letra,tapa,false,suave,plano);
    glPopMatrix();

    PEON 2
    glPushMatrix();
    glTranslatef(270.0,0.0,0.0);
    peon2->drawObj(modo,letra,tapa,false,suave,plano);
    glPopMatrix();
    */
}
//**************************************************************************
//
// función que se invoca cuando se pulsa una tecla
// Devuelve true si se ha pulsado la tecla para terminar el programa (Q),
// devuelve false en otro caso.
//
//**************************************************************************

bool Escena::teclaPulsada( unsigned char tecla, int x, int y )
{
   using namespace std ;
   
   cout << "Tecla pulsada: '" << tecla << "'" << endl;
   bool salir=false;
   switch( toupper(tecla) )
   {
      
      case 'Q' :
         if (modoMenu!=NADA)
            modoMenu=NADA;            
         else {
            salir=true ;
         }
         break ;
         /*
      case 'O' :
         // ESTAMOS EN MODO SELECCION DE OBJETO
         modoMenu=SELOBJETO;

         printf("Opciones disponibles: \n 'C': Cubo \n 'T': Tetraedro \n 'R': Revolucion \n 'I': Cilindro \n 'N':Cono \n 'E': Esfera \n Q': salir\n");
         break ;
          */
        case 'V' :
         // ESTAMOS EN MODO SELECCION DE MODO DE VISUALIZACION
         
         modoMenu=SELVISUALIZACION;
         printf("\nOpciones disponibles: \n'L': Línea \n'P': Puntos \n'S': Sólido\n'A': Ajedrez\n'T':Activar/Desactivar Tapas\nq'Q': salir\n");
         break ;

       case 'D' :
         // ESTAMOS EN MODO SELECCION DE DIBUJADO
         modoMenu=SELDIBUJADO;
         printf("\nOpciones disponibles: \n'1': glDrawElements; \n'2': VBOs; \n'Q': salir\n ");
         break ;

       case 'I':
           hayLuz=true;
           suave=true;
           luz1=true;
           modoMenu=MENUILUMINACION;
           visualizacion[0]=1;
           visualizacion[1]=1;
           visualizacion[2]=1;
           ajedrez=false;
           printf("\nOpciones disponibles: \n'E': desactivar iluminacion \n'1|2': Activar/desactivar luces \n'A': Variacion del ángulo alfa\n'B': Variacion del ángulo alfa\n'+': Incrementar el ángulo\n'-': Decrementar el ángulo\n'S': Dibujar suavizado\n'P': Dibujar plano\n");
            break;

       case 'M':
           modoMenu=MENUMANUAL;
           printf("\nOpciones disponibles: \n'Numero 0-4':Elegir grado de libertad  \n'+':Aumentar el valor grado libertad  \n'-':Disminuir el valor grado libertad\n'Q': salir\n ");
           break;

       case 'A':
           modoMenu=MENUAUTOMATICO;
           animar=true;
           printf("\nOpciones disponible: \n'+':Aumentar velocidad animacion \n'-':Disminuir velocidad animacion \n'Q':Desactivar animacion(salir)\n ");
           break;



   }
    /*
   if(modoMenu==SELOBJETO)
         {

           switch (toupper(tecla))
           {

            case 'C':
               hayCubo*=-1;
               hayTetraedro=1;
               hayObjRevolucion=1;
               hayCilindro=1;
               hayCono=1;
               hayEsfera=1;
                  break;

            case 'T':
               hayTetraedro*=-1;
               hayCubo=1;
               hayObjRevolucion=1;
               hayCilindro=1;
               hayCono=1;
               hayEsfera=1;
                  break;

               case 'R':
                   hayObjRevolucion*=-1;
                   hayCubo=1;
                   hayTetraedro=1;
                   hayCilindro=1;
                   hayCono=1;
                   hayEsfera=1;
                   break;

               case 'I':
                   hayCilindro*=-1;
                   hayObjRevolucion=1;
                   hayCubo=1;
                   hayTetraedro=1;
                   hayCono=1;
                   hayEsfera=1;
                   break;

               case 'N':
                   hayCilindro=1;
                   hayObjRevolucion=1;
                   hayCubo=1;
                   hayTetraedro=1;
                   hayCono*=-1;
                   hayEsfera=1;
                   break;

               case 'E':
                   hayCilindro=1;
                   hayObjRevolucion=1;
                   hayCubo=1;
                   hayTetraedro=1;
                   hayCono=1;
                   hayEsfera*=-1;
                   break;
               case 'Q':
               salir=true;
                   break;

           }
         }
    */

   if(modoMenu==SELVISUALIZACION)
   {
                switch (toupper(tecla)) {
                    case 'P':
                        visualizacion[0] *= -1;
                        if (modo)
                            break;
                    case 'L':
                        visualizacion[1] *= -1;
                        break;
                    case 'S':
                        visualizacion[2] *= -1;
                        break;

                    case 'A': ///si esta ajedrez se desactivan las demas visualizaciones
                        if (!ajedrez) {
                            ajedrez = true;
                        } else {
                            ajedrez = false;
                        }

                        break;
                    case 'T':
                        if (tapa)
                            tapa = false;
                        else if (!tapa)
                            tapa = true;
                        break;

                    case 'Q':
                        salir = true;
                        break;
                }




   }

   if(modoMenu==MENUILUMINACION) {

       switch (toupper(tecla)) {

           case 'E':
               hayLuz = false;
               break;

           case '1':
               if (!luz1) {
                   luz1 = true;
               } else if (luz1) {
                   luz1 = false;
               }
               break;

           case '2':
               if (!luz2) {
                   luz2 = true;
               } else if (luz2) {
                   luz2 = false;
               }
               break;

           case 'S':
               suave=true;
               plano=false;
               break;

           case 'P':
               plano=true;
               suave=false;
               break;

           case 'A':
               if(!variacionAlfa) {
                   printf("Variacion alfa activada\n");
                   variacionAlfa = true;
               }
               else {
                   printf("Variacion alfa desactivada\n");
                   variacionAlfa = false;
               }
                variacionBeta=false;
               break;

           case 'B':
               if(!variacionBeta) {
                   printf("Variacion beta activada\n");
                   variacionBeta = true;
               }
               else {;
                   printf("Variacion beta desactivada\n");
                   variacionBeta = false;
               }
               variacionAlfa=false;
               break;

           case '+':

               if(variacionAlfa){
                   printf("Aumentamos alfa\n");
                   LD->variarAnguloAlpha(25.0);
               }

               else if(variacionBeta) {
                   printf("Aumentamos beta\n");
                   LD->variarAnguloBeta(25.0);
               }
            break;

           case '-':
               if(variacionAlfa) {
                   printf("Disminuimos alfa\n");
                   LD->variarAnguloAlpha(-25.0);

               }
               else if(variacionBeta) {
                   printf("Disminuimos beta\n");
                   LD->variarAnguloBeta(-25.0);
               }
               break;

       }

   }
   if(modoMenu==MENUMANUAL){

       switch (toupper(tecla))
       {
           case '0':
               printf("Vuelo activado\n");
               vuela=true;
               helice=false;
               cabezaGira=false;
               brazoGira= false;
               colaMov=false;
               break;

           case '1':
               printf("helicoptero activado\n");
               helice=true;
               vuela= false;
               cabezaGira=false;
               brazoGira=false;
               colaMov=false;
               break;

           case '2':
               printf("cabeza activada\n");
               cabezaGira=true;
               helice=false;
               vuela= false;
               brazoGira=false;
               colaMov=false;
               break;

           case '3':("brazos activados\n");
               cabezaGira=false;
               helice=false;
               vuela= false;
               brazoGira= true;
               colaMov=false;
               break;

           case '4':
               printf("cola activada\n");
               cabezaGira=false;
               helice=false;
               vuela= false;
               brazoGira= false;
               colaMov=true;
               break;

           case '+':
               printf("Aumentamos grado de libertad\n");
               if(vuela && vuelo<10)
                   vuelo+=1;
               else if(helice)
                   doraemon->modificarGiroHelicoptero(2.5);
               else if(cabezaGira)
                   doraemon->modificarGiroCabeza(2.5);
               else if(brazoGira)
                   doraemon->modificarGiroBrazo(1.5);
               else if(colaMov)
                   doraemon->modificarGiroCola(2.0);
               break;

           case '-':
               printf("Disminuimos grado de libertad\n");
               if(vuela && vuelo>-10)
                   vuelo-=1;
               else if(helice)
                   doraemon->modificarGiroHelicoptero(-2.5);
               else if(cabezaGira)
                   doraemon->modificarGiroCabeza(-2.5);
               else if(brazoGira)
                   doraemon->modificarGiroBrazo(-2.5);
               else if(colaMov)
                   doraemon->modificarGiroCola(-1.0);

               break;

           case 'Q':
               salir = true;
               break;
       }


   }

   if(modoMenu==MENUAUTOMATICO)
   {
       switch (toupper(tecla))
       {
           case '+':
                printf("Aumentamos velocidad\n");
                doraemon->aumentarVelocidad();
               break;

           case '-':
                printf("Disminuimos velocidad\n");
                doraemon->disminuirVelocidad();
               break;

           case 'Q':
               animar=false;
               salir=true;
               break;
       }
   }
 if(modoMenu==SELDIBUJADO)
   {
       switch (toupper(tecla))
       {
          case '1':
            modo=1;
          break;

          case '2':
            modo=2;
          break;

          case 'Q':
            salir=true;
          break;
       }
   }



   return salir;
}
//**************************************************************************

void Escena::teclaEspecial( int Tecla1, int x, int y )
{
   switch ( Tecla1 )
   {
	   case GLUT_KEY_LEFT:
         Observer_angle_y-- ;
         break;
	   case GLUT_KEY_RIGHT:
         Observer_angle_y++ ;
         break;
	   case GLUT_KEY_UP:
         Observer_angle_x-- ;
         break;
	   case GLUT_KEY_DOWN:
         Observer_angle_x++ ;
         break;
	   case GLUT_KEY_PAGE_UP:
         Observer_distance *=1.2 ;
         break;
	   case GLUT_KEY_PAGE_DOWN:
         Observer_distance /= 1.2 ;
         break;
	}

	//std::cout << Observer_distance << std::endl;
}

//**************************************************************************
// Funcion para definir la transformación de proyeccion
//
// ratio_xy : relacción de aspecto del viewport ( == ancho(X) / alto(Y) )
//
//***************************************************************************

void Escena::change_projection( const float ratio_xy )
{
   glMatrixMode( GL_PROJECTION );
   glLoadIdentity();
   const float wx = float(Height)*ratio_xy ;
   glFrustum( -wx, wx, -Height, Height, Front_plane, Back_plane );
}
//**************************************************************************
// Funcion que se invoca cuando cambia el tamaño de la ventana
//***************************************************************************

void Escena::redimensionar( int newWidth, int newHeight )
{
   Width  = newWidth/10;
   Height = newHeight/10;
   change_projection( float(newHeight)/float(newWidth) );
   glViewport( 0, 0, newWidth, newHeight );
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void Escena::change_observer()
{
   // posicion del observador
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef( 0.0, 0.0, -Observer_distance );
   glRotatef( Observer_angle_y, 0.0 ,1.0, 0.0 );
   glRotatef( Observer_angle_x, 1.0, 0.0, 0.0 );
}

void Escena::animarModeloJerarquico() {
    if(animar)
    {
        doraemon->animacionDoraemon();
    }
}