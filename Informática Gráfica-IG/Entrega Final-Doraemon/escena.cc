

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
   pared=new Pared(400.0);
   cielo=new Pared(1050.0);
   campo=new Pared(1050.0);
    cesped=new Pared(500);

    cilindro=new Cilindro(2,25,25,50,'Y',false);
   peon1=new ObjRevolucion("plys/peon.ply",50,true,true);
   peon2=new ObjRevolucion("plys/peon.ply",50,true,true);
   cono=new Cono(2,50,50,25,'Y',false);
   esfera=new Esfera(20,40,25,'Y',true);
   esferaLuz=new Esfera(20,40,25,'Y',false);
   lataSup=new ObjRevolucion("plys/lata-psup.ply",50,true,true,true);
   lataInf=new ObjRevolucion("plys/lata-pinf.ply",50,true,true,true);
    lata=new ObjRevolucion("plys/lata-pcue.ply",50,false,false,true);
    balon=new Esfera(20,40,50,'Y',true);
    habitacion=new Textura("Texturas/Habitacion.jpg");
    pared->setTextura(habitacion);
    puerta=new Puerta();

    Material ruby=Material({0.61424,0.04136,0.04136,1.0},{0.727811,0.626959,0.626959,1.0},{0.1745,0.01175,0.01175,1.0},0.6);
    mdifuso=Material({0.9,0.9,0.9,0.9}, {0.0,0.0,0.0,0.0}, {0.8,0.8,0.8,0.8}, 0.0);
    mespecular=Material({0.0,0.0,0.0,1.0}, {1.0,1.0,1.0,1.0}, {0.0,0.0,0.0,0.0}, 1.0);

    Textura * cocaCola=new Textura("Texturas/text-lata-1.jpg");
    Textura * tapa=new Textura("Texturas/tapasLata.jpg");
    Textura * futbol=new Textura("Texturas/balon.jpg");
    Textura * tcielo=new Textura("Texturas/cielo.jpg");
    Textura * tcampo=new Textura("Texturas/campo.jpg");
    Textura * tcesped=new Textura("Texturas/cesped.jpg");
    lata->setTextura(cocaCola);
    lataSup->setTextura(tapa);
    lataInf->setTextura(tapa);
    lataInf->setMaterial(mespecular);
    lataSup->setMaterial(mespecular);
    lata->setMaterial(mespecular);
    balon->setMaterial(mespecular);
    balon->setTextura(futbol);
    campo->setTextura(tcampo);
    cesped->setTextura(tcesped);
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
   pared->inicializarColores();
   lata->inicializarColores();
   balon->inicializarColores();
   lata->cambiarColores({1.0,1.0,1.0});
   balon->cambiarColores({1.0,1.0,1.0});
   cielo->inicializarColores();
   cielo->setTextura(tcielo);
    campo->inicializarColores();
    cesped->inicializarColores();
    lataInf->inicializarColores();
    lataSup->inicializarColores();
    lataInf->cambiarColores({1.0,1.0,1.0});
    lataSup->cambiarColores({1.0,1.0,1.0});

    pared->cambiarColores({1.0,1.0,1.0});
    cielo->cambiarColores({1.0,1.0,1.0});
    campo->cambiarColores({1.0,1.0,1.0});
   cilindro->cambiarColores({0.0,0.0,0.0});
   esfera->cambiarColores({30.0/255.0,142.0/255.0,255.0/255.0});
    cesped->cambiarColores({1.0,1.0,1.0});
    campo->setMaterial(mespecular);
    balon->setColorFalso({1.0,0.0,1.0});
    cesped->setMaterial(mespecular);


    LP=new LuzPosicional(Tupla3f{0.0,50.0,100.0},GL_LIGHT1,{1.0,1.0,1.0,1.0},{1.0,1.0,1.0,1.0},{1.0,1.0,1.0,1.0});
    LD=new LuzDireccional(Tupla2f {-100.0,200.0},GL_LIGHT2,{1.0,1.0,1.0,1.0},{1.0,1.0,1.0,1.0},{1.0,1.0,1.0,1.0});

    esmeralda=Material({0.07568,0.61424,0.07568,1.0},{0.633,0.727811,0.633,1.0},{0.0215,0.1745,0.0215,1.0},0.6);
    oro=Material({0.75164,0.60648,0.22648,0.5},{0.628281,0.555802,0.366065,0.5},{0.24725,0.1995,0.0745,0.5},0.4);
    cubo->setMaterial(esmeralda);
    tetraedro->setMaterial(esmeralda);
    esfera->setMaterial(oro);
    cilindro->setMaterial(oro);
    cono->setMaterial(oro);
    peon1->setMaterial(mdifuso);
    peon2->setMaterial(mespecular);
    esferaLuz->setMaterial(esmeralda);
    cielo->setMaterial(mespecular);
    Textura * color=new Textura("Texturas/Azul.jpg");
    esfera->setTextura(color);
    pared->setMaterial(oro);

    PrimeraPersonaPerspectiva=new Camara({0.0,0.0,300.0},{0.0,0.0,0.0},{0.0,1.0,0.0},0,-1.0,1.0,0.5,500.0,1.0,-1.0);
    SegundaPersonaPerspectiva=new Camara({100.0,100.0,300.0},{0.0,0.0,0.0},{0.0,1.0,0.0},0,-1.0,1.0,0.5,500.0,1.0,-1.0);
    PrimeraPersonaOrtogonal=new Camara({-80.0,50.0,200.0},{0.0,0.0,0.0},{0.0,1.0,0.0},1,-1.0,1.0,0.5,500.0,300.0,-300.0);
    camaras.push_back(*PrimeraPersonaPerspectiva);
    camaras.push_back(*PrimeraPersonaOrtogonal);
    camaras.push_back(*SegundaPersonaPerspectiva);

    doraemon->centroCamara={0.0,0.0,0.0};

    balon->setColorAux({1.0,1.0,1.0});
    balon->setMaterialAux(mespecular);

    lata->setColorFalso({0.2,0.2,0.2});
    lataSup->setColorFalso({0.2,0.2,0.2});
    lataInf->setColorFalso({0.2,0.2,0.2});

    lataSup->setColorAux({1.0,1.0,1.0});
    lataInf->setColorAux({1.0,1.0,1.0});
    lata->setColorAux({1.0,1.0,1.0});

    lataSup->setMaterialAux(mespecular);
    lataInf->setMaterialAux(mespecular);
    lata->setMaterialAux(mespecular);




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
	glViewport( 0, 0, UI_window_width, UI_window_height );
    change_projection();

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
                letra='N';
                dibujarObjetos('N');
            }
            if(luz2)
            {
                LD->activar();
                letra='N';
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
       letra='P';
       dibujarObjetos('P');
   }

   if(visualizacion[1]==-1 && !ajedrez && !hayLuz)
   {

       glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
       letra='L';
       dibujarObjetos('L');
   }

   if(visualizacion[2]==-1 && !ajedrez && !hayLuz)
   {

       glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
       letra='S';
       dibujarObjetos('S');
   }

   if(ajedrez && !hayLuz){
       letra='A';
       dibujarObjetos('A');

   }



}


void Escena::dibujarObjetos(char letra) {

    /*
    glPushMatrix();
    glTranslatef(0.0,0.0,0.0);
    pared->draw(modo,letra,suave,plano);
    glPopMatrix();
    */

    /*
    //CUBO
    glPushMatrix();
    glTranslatef(0.0,0.0,0.0);
    cubo->draw(modo,letra,suave,plano,false);
    glPopMatrix();


    //TETRAEDRO
    glPushMatrix();
    glTranslatef(100.0,0.0,0.0);
    tetraedro->draw(modo,letra,suave,plano);
    glPopMatrix();
    */


    /*
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
    */
    /*
    if(camaraActiva!=1){
    if (!animacionTerminada) {
        if (!escenaCampo) {
            if (animarEscena && vuelo >= 70) {

                vuelo--;
            }
            if (vuelo == 69) {
                momentoBalon = true;
                movCabeza = false;
            }
            if (momentoBalon && vuelta <= 90) {
                vuelta += 0.5;

            }
            if (momentoBalon && movBalonx >= 75 && !golpea)
                movBalonx -= 3;

            if (momentoBalon && movBalony >= 110 && !golpea)
                movBalony -= 2.65;

            if (movBalony <= 110)
                golpea = true;

            if (golpea) {
                movBalonx += 3;
                movBalony -= 2.65;
                vuelo -= 3;
                if (golpe != 90)
                    golpe += 0.5;
            }


            if (!momentoBalon) {
                glPushMatrix();
                if (!animarEscena)
                    glTranslatef(2.0 * 25, 40 * 25, -1.0 * 2.5);
                else if (animarEscena && vuelo >= 69) {

                    glTranslatef(0.0, vuelo, 0.0);
                }

                glRotatef(10.0, 1.0, 0.0, .0);
                glScalef(0.50, 0.50, 0.50);
                doraemon->draw(modo, letra, tapa, false, suave, plano, false);
                glPopMatrix();

                doraemon->centroNuevo(X) = 0.65 * doraemon->centroCamara(X) + (2.0 * 25);
            }

            if (momentoBalon) {
                if (!golpea) {
                    glPushMatrix();
                    glTranslatef(0.0, vuelo, 0.0);
                    glRotatef(vuelta, 0.0, 1.0, 0.0);
                    glScalef(0.50, 0.50, 0.50);
                    doraemon->draw(modo, letra, tapa, false, suave, plano, false);
                    glPopMatrix();
                } else {
                    bajaBrazos = false;

                    glPushMatrix();
                    glTranslatef(0.0, vuelo, 0.0);
                    glRotatef(golpe, 0.0, 0.0, 1.0);
                    glRotatef(vuelta, 0.0, 1.0, 0.0);
                    glScalef(0.50, 0.50, 0.50);
                    doraemon->draw(modo, letra, tapa, false, suave, plano, false);
                    glPopMatrix();

                }

                glPushMatrix();
                glTranslatef(movBalonx, movBalony, 0);
                glScalef(0.50, 0.50, 0.50);
                balon->drawObj(modo, letra, tapa, false, suave, plano, false);
                glPopMatrix();
            }


            glPushMatrix();
            glTranslatef(0.0, 0.0, -7.5 * 25);
            cielo->draw(modo, letra, suave, plano, false);
            glPopMatrix();


            if (vuelo <= -800) {
                escenaCampo = true;
                vuelo = 900;
            }


        }


        if (escenaCampo) {


            if (!levanta && vuelo >= -450) {
                dormido = true;
                vuelo -= 4;
            }
            if (!levanta && vuelo < -450) {
                if (dormido) {
                    std::this_thread::sleep_for(std::chrono::seconds(3));
                    dormido = false;
                }
                levanta = true;
            }


            if (levanta && vuelta > -90 && !escenaHabitacion) {
                vuelo++;
                if (golpe >= 0)
                    golpe -= 0.5;
                if (vuelta >= -90)
                    vuelta -= 0.5;
            }

            if (vuelta <= -90)
                puertaMagica = true;

            if (puertaMagica && salePuerta > -250) {
                dormido = true;
                salePuerta--;
                vuelo -= 0.4;
                vePuerta -= 0.25;
                if (escalaPuerta <= 10)
                    escalaPuerta += 0.1;
            }
            if (puertaMagica && salePuerta == -250 && abrePuerta >= 0) {
                if (dormido) {
                    std::this_thread::sleep_for(std::chrono::seconds(2));
                    dormido = false;
                }

                abrePuerta--;
            }
            if (!escenaHabitacion && abrePuerta == -1 && vePuerta >= -325) {
                vePuerta -= 0.5;
            }
            if (vePuerta == -324) {
                escenaHabitacion = true;
            }
            if (escenaHabitacion && vePuerta <= 0) {
                if (vuelta <= 0)
                    vuelta++;

                vePuerta += 2;
            }
            if (vuelta == 1 && escenaHabitacion)
                animacionTerminada = true;


            if (!levanta) {
                glPushMatrix();
                glTranslatef(0.0, vuelo, 0.0);
                glRotatef(golpe, 0.0, 0.0, 1.0);
                glRotatef(vuelta, 0.0, 1.0, 0.0);
                glScalef(0.50, 0.50, 0.50);
                doraemon->draw(modo, letra, tapa, false, suave, plano, false);
                glPopMatrix();

                glPushMatrix();
                glTranslatef(0.0, 0.0, -7.5 * 25);
                campo->draw(modo, letra, suave, plano, false);
                glPopMatrix();
            }
            if (levanta) {
                if (!escenaHabitacion) {
                    glPushMatrix();
                    glTranslatef(vePuerta, vuelo, 0.0);
                    glRotatef(golpe, 0.0, 0.0, 1.0);
                    glRotatef(vuelta, 0.0, 1.0, 0.0);
                    glScalef(0.50, 0.50, 0.50);
                    doraemon->draw(modo, letra, tapa, false, suave, plano, false);
                    glPopMatrix();


                    glPushMatrix();
                    glTranslatef(0.0, 0.0, -7.5 * 25);
                    campo->draw(modo, letra, suave, plano, false);
                    glPopMatrix();


                } else {
                    glPushMatrix();
                    glTranslatef(vePuerta, vuelo, 75.0);
                    glRotatef(golpe, 0.0, 0.0, 1.0);
                    glRotatef(vuelta, 0.0, 1.0, 0.0);
                    glScalef(0.50, 0.50, 0.50);
                    doraemon->draw(modo, letra, tapa, false, suave, plano, false);
                    glPopMatrix();

                    glPushMatrix();
                    glTranslatef(0.0, 0.0, 50.0);
                    pared->draw(modo, letra, suave, plano, false);
                    glPopMatrix();
                }
            }

            if (puertaMagica) {
                glPushMatrix();
                glTranslatef(salePuerta, -135.0, 90.0);
                glRotatef(abrePuerta, 0.0, 1.0, 0.0);
                glScalef(0.10 * escalaPuerta, 0.11 * escalaPuerta, 0.10 * escalaPuerta);
                puerta->draw(modo, letra, tapa, false, suave, plano, false);
                glPopMatrix();
            }

        }
    }*/
    //else {
        movCabeza = true;
        bajaBrazos = true;

        if(camaraActiva==0) {
            glPushMatrix();
            glTranslatef(0.0, 0.0, -100.0);
            pared->draw(modo, letra, suave, plano, false);
            glPopMatrix();
        }

        glPushMatrix();
        glTranslatef(300, 0.0, 0.0);
        puerta->draw(modo, letra, tapa, false, suave, plano, false);
        glPopMatrix();

        puerta->centroNuevo(X)=puerta->centroCamara(X)+300.0;

        glPushMatrix();
        glTranslatef(2.0 * 25, 0.0, -1.0 * 2.5);
        glScalef(0.65, 0.65, 0.65);
        doraemon->draw(modo, letra, tapa, false, suave, plano, false);
        glPopMatrix();

        doraemon->centroNuevo(X)=0.65*doraemon->centroCamara(X)+(2*25);
        doraemon->centroNuevo(Y)=0.65*doraemon->centroCamara(Y);
        doraemon->centroNuevo(Z)=0.65*doraemon->centroCamara(Z)-(1*25);
    //}
//}
    //else{
        /*
        glPushMatrix();
        glTranslatef(100.0, 0.0, 0.0);
        puerta->draw(modo, letra, tapa, false, suave, plano, false);
        glPopMatrix();

        puerta->centroNuevo(X)=puerta->centroCamara(X)+100;
        */
        glPushMatrix();
        glTranslatef(-5.0*25, 0, 0);
        glScalef(1.0, 1.0, 1.0);
        balon->drawObj(modo, letra, tapa, false, suave, plano, false);
        glPopMatrix();

        balon->centroNuevo(X)=1*balon->centroCamara(X)-(5.0*25.0);
    //}


        /*
        balon->centroNuevo(X)=1*balon->centroCamara(X)-(5.0*25.0);
        */

    //puerta->draw(modo,letra,tapa,false,suave,plano,false);


    glPushMatrix();
    glTranslatef(-10.0*25, 0, 0);
    glScalef(5,5,5);
    lata->drawObj(modo,letra,tapa,false,suave,plano,false);
    lataSup->drawObj(modo,letra,tapa,false,suave,plano,false);
    lataInf->drawObj(modo,letra,tapa,false,suave,plano,false);
    glPopMatrix();

    lata->centroNuevo(X)=5*lata->centroCamara(X)-(10.0*25);
    lata->centroNuevo(Y)=5*lata->centroCamara(Y);
    lata->centroNuevo(Z)=5*lata->centroCamara(Z);

    lataSup->centroNuevo(X)=5*lataSup->centroCamara(X)-(10.0*25);
    lataSup->centroNuevo(Y)=5*lataSup->centroCamara(Y);
    lataSup->centroNuevo(Z)=5*lataSup->centroCamara(Z);

    lataInf->centroNuevo(X)=5*lataInf->centroCamara(X)-(10.0*25);
    lataInf->centroNuevo(Y)=5*lataInf->centroCamara(Y);
    lataInf->centroNuevo(Z)=5*lataInf->centroCamara(Z);

    /*
    glPushMatrix();
    glTranslatef(0.75*25,0.0,0.0);
    cilindro->drawObj(modo,letra,tapa,false,suave,plano);
    glPopMatrix();
    /*
   glPushMatrix();
   glTranslatef(0.75*25,-0.6*25,0.0);
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
   */
    /*
    //CONO
    glPushMatrix();
    glTranslatef(-150.0,0.0,0.0);
    cono->drawObj(modo,letra,tapa,true,suave,plano);
    glPopMatrix();
    */

    /*
    //ESFERA
    glPushMatrix();
    glTranslatef(0.0,7*25,0.0);
    glScalef(3.25,3.25,3.25);
    esfera->drawObj(modo,letra,tapa,false,suave,plano);
    glPopMatrix();
     */

    /*
    glPushMatrix();
    //glTranslatef(0.0,1.0*25,0.0);
    glScalef(2,2,-0.5);
    semiesfera->drawObj(modo,letra,tapa,false,suave,plano);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0,-1.25*25,0.2*25);
    glScalef(0.7,0.4,0.3);
    esfera->drawObj(modo,letra,tapa,false,suave,plano);
    glPopMatrix();
    */

    /*
    //PEON 1
    glPushMatrix();
    glTranslatef(200.0,0.0,0.0);
    peon1->drawObj(modo,letra,tapa,false,suave,plano);
    peon2->drawObj(modo,letra,tapa,false,suave,plano);
    glPopMatrix();

    //PEON 2
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
           printf("\nOpciones disponibles: \n'E': desactivar iluminacion \n'1|2': Activar/desactivar luces \n'A': Variacion del ángulo alfa\n'B': Variacion del ángulo alfa\n'+': Incrementar el ángulo\n'-': Decrementar el ángulo\n'S': Dibujar suavizado\n'P': Dibujar plano\n'T': Activar animacion luz posicional\n");
            break;

       case 'M':
           modoMenu=MENUMANUAL;
           printf("\nOpciones disponibles: \n'Numero 0-4':Elegir grado de libertad  \n'+':Aumentar el valor grado libertad  \n'-':Disminuir el valor grado libertad\n'Q': salir\n ");
           break;

       case 'X':
           modoMenu=MENUAUTOMATICO;
           animar=true;
           animarEscena=true;
           printf("\nOpciones disponible: \n'+':Aumentar velocidad animacion \n'-':Disminuir velocidad animacion \n'S':Desactivar animacion(salir)\n ");
           break;

       case 'C':
           modoMenu=MENCAMARA;
           camaraActivada=true;
           printf("\nOpciones disponibles: \n'0': Primera Persona Perspectiva; \n'1': Primera Persona Ortogonal \n'2': Examinar; \n ");
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
               luzAnimar=false;
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


           case 'T':
                if(luzAnimar)
                    luzAnimar=false;
                else
                    luzAnimar=true;
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

           case '3':
               printf("brazos activados\n");
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

           case 'S':
               animar=false;
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

    if(modoMenu==MENCAMARA){
        switch (toupper(tecla)) {
            case'0':
                camaraActiva=0;
                change_observer();
                change_projection();
                break;
            case '1':
                camaraActiva=1;
                change_observer();
                change_projection();
                break;

            case '2':
                camaraActiva=2;
                change_observer();
                change_projection();
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
         camaras[camaraActiva].rotarYExaminar(-1*(M_PI/180));
         break;
	   case GLUT_KEY_RIGHT:
         camaras[camaraActiva].rotarYExaminar(1*(M_PI/180));
         break;
	   case GLUT_KEY_UP:
         camaras[camaraActiva].rotarXExaminar(-1*(M_PI/180));
         break;
	   case GLUT_KEY_DOWN:
         camaras[camaraActiva].rotarXExaminar(1*(M_PI/180));
         break;

	   case GLUT_KEY_PAGE_UP:
           camaras[camaraActiva].zoom(1.1,camaras[camaraActiva].left,camaras[camaraActiva].right,camaras[camaraActiva].top,camaras[camaraActiva].bottom);
         break;
	   case GLUT_KEY_PAGE_DOWN:
           camaras[camaraActiva].zoom(0.9,camaras[camaraActiva].left,camaras[camaraActiva].right,camaras[camaraActiva].top,camaras[camaraActiva].bottom);
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

void Escena::change_projection()
{
   glMatrixMode( GL_PROJECTION );
   glLoadIdentity();
   camaras[camaraActiva].setProyeccion();
}
//**************************************************************************
// Funcion que se invoca cuando cambia el tamaño de la ventana
//***************************************************************************

void Escena::redimensionar( int newWidth, int newHeight )
{
    const float r=(float)newWidth/(float)newHeight;

    for(int i=0 ; i<camaras.size();i++)
    {
        camaras[i].left=camaras[i].bottom*r;
        camaras[i].right=camaras[i].top*r;
    }
   change_projection();
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
   camaras[camaraActiva].setObserver();

}

void Escena::animarModeloJerarquico() {
    if(animar)
    {
        doraemon->animacionDoraemon(movCabeza,bajaBrazos);
    }
    if(luzAnimar)
    {
        LP->animarLuz();
    } glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Limpiar la pantalla
}

void Escena::ratonMovido(int x, int y) {
    if(estadoRaton)
    {
        camaras[camaraActiva].rotarXFirstPerson(x-xant);
        camaras[camaraActiva].rotarYFirstPerson(y-yant);
        xant=x;
        yant=y;
    }
    else
    {
        camaras[camaraActiva].rotarXExaminar(x-xant);
        camaras[camaraActiva].rotarYExaminar(y-yant);
        xant=x;
        yant=y;
    }
}
void Escena::dibujaSeleccion() {



    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Limpiar la pantalla
    glDisable ( GL_DITHER );
    glDisable ( GL_TEXTURE );
    glDisable ( GL_LIGHTING );
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


        balon->setTextura(nullptr);
        glPushMatrix();
        glTranslatef(-5.0 * 25, 0, 0);
        balon->drawObj(1, 'S', tapa, false, suave, plano, true);
        glPopMatrix();


        glPushMatrix();
        glTranslatef(300.0, 0.0, 0.0);
        puerta->draw(1, 'S', tapa, false, suave, plano, true);
        glPopMatrix();


        /*
        glPushMatrix();
        glTranslatef(100.0, 0.0, 0.0);
        pared->draw(modo, 'S', suave, plano, true);
        glPopMatrix();
        */

        glPushMatrix();
        glTranslatef(2.0 * 25, 0.0, -1.0 * 2.5);
        glScalef(0.65, 0.65, 0.65);
        doraemon->draw(1, 'S', tapa, false, suave, plano, true);
        glPopMatrix();

        lata->setTextura(nullptr);
        lataSup->setTextura(nullptr);
        lataInf->setTextura(nullptr);

    glPushMatrix();
    glTranslatef(-10.0*25, 0, 0);
    glScalef(5,5,5);
    lata->drawObj(1,'S',tapa,false,suave,plano,true);
    lataSup->drawObj(1,'S',tapa,false,suave,plano,true);
    lataInf->drawObj(1,'S',tapa,false,suave,plano, true);
    glPopMatrix();



    glEnable ( GL_DITHER );
    glEnable ( GL_TEXTURE );
    glEnable ( GL_LIGHTING );

}



void Escena::CentrarCamaraClick(int x, int y) {

    glDisable ( GL_LIGHTING );
    GLfloat pixels[3];
    GLint viewport[4];

    glGetIntegerv(GL_VIEWPORT,viewport);
    glReadPixels(x,viewport[3]-y,1,1,GL_RGB,GL_FLOAT,pixels);

    Tupla3f colorLeido={pixels[0],pixels[1],pixels[2]};




    std::cout<<colorLeido(X)<<std::endl;
    std::cout<<colorLeido(Y)<<std::endl;
    std::cout<<colorLeido(Z)<<std::endl;



    if(colorLeido(X)==0.0 && colorLeido(Y)==1.0 && colorLeido(Z)==0.0)
    {

        balon->cambiarAmarillo(false);
        doraemon->cambiarAmarillo(true);
        puerta->cambiarAmarillo(false);
        lataSup->cambiarAmarillo(false);
        lataInf->cambiarAmarillo(false);
        lata->cambiarAmarillo(false);
        camaras[camaraActiva].setAt(doraemon->getCentroCamara());
    }

    if(colorLeido(X)==1.0 && colorLeido(Y)==0.0 && colorLeido(Z)==1.0)
    {

        balon->cambiarAmarillo(true);
        doraemon->cambiarAmarillo(false);
        puerta->cambiarAmarillo(false);
        lataSup->cambiarAmarillo(false);
        lataInf->cambiarAmarillo(false);
        lata->cambiarAmarillo(false);
        camaras[camaraActiva].setAt(balon->getCentroCamara());
    }

    if(colorLeido(X)==1.0 && colorLeido(Y)==0.0 && colorLeido(Z)==0.0 || colorLeido(X)==0.0 && colorLeido(Y)==0.0 && colorLeido(Z)==0.0)
    {

        balon->cambiarAmarillo(false);
        doraemon->cambiarAmarillo(false);
        puerta->cambiarAmarillo(true);
        lataSup->cambiarAmarillo(false);
        lataInf->cambiarAmarillo(false);
        lata->cambiarAmarillo(false);
        camaras[camaraActiva].setAt(puerta->getCentroCamara());
    }
    if(colorLeido(X)==lata->getFalso()(X) && colorLeido(Y)==lata->getFalso()(Y) && colorLeido(Z)==lata->getFalso()(Z))
    {
        lataSup->cambiarAmarillo(true);
        lataInf->cambiarAmarillo(true);
        lata->cambiarAmarillo(true);
        doraemon->cambiarAmarillo(false);
        puerta->cambiarAmarillo(false);
        balon->cambiarAmarillo(false);

        camaras[camaraActiva].setAt(lata->getCentroCamara());
    }
    if(colorLeido(X)==1.0 && colorLeido(Y)==1.0 && colorLeido(Z)==1.0)
    {
        lataSup->cambiarAmarillo(false);
        lataInf->cambiarAmarillo(false);
        lata->cambiarAmarillo(false);
        doraemon->cambiarAmarillo(false);
        puerta->cambiarAmarillo(false);
        balon->cambiarAmarillo(false);
    }



    Textura * futbol=new Textura("Texturas/balon.jpg");
    balon->setTextura(futbol);



        Textura *cocaCola = new Textura("Texturas/text-lata-1.jpg");
        Textura *tapa = new Textura("Texturas/tapasLata.jpg");
        lata->setTextura(cocaCola);
        lataSup->setTextura(tapa);
        lataInf->setTextura(tapa);


    glEnable ( GL_LIGHTING );
}


