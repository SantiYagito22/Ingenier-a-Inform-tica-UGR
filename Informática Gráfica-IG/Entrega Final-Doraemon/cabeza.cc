#include "cabeza.h"

Cabeza::Cabeza() {
    cabeza=new Esfera(20,100,25,'Y',false);
    gorrocoptero=new Gorrocoptero();
    boca=new Boca();
    bigotes=new Bigotes();
    ojos=new Ojos();
    nariz=new Nariz();
    cabezaBlanca=new Esfera(20,40,25,'Y',false);
    cabezaBlanca->inicializarColores();
    cabeza->inicializarColores();
    cabezaBlanca->cambiarColores({254.0/255.0,254.0/255.0,254.0/255.0});
    cabeza->cambiarColores({30.0/255.0,142.0/255.0,255.0/255.0});
    Mcabeza=Material({0.396, 0.74151, 0.69102, 0.8},{0.297254, 0.30829, 0.306678, 0.8},{0.1, 0.18725, 0.1745, 0.8},12.8);
    Mblanco=Material({0.55,0.55,0.55,1.0},{0.70,0.70,0.70,1.0},{0.0,0.0,0.0,1.0},0.25);
    cabeza->setMaterial(Mcabeza);
    cabezaBlanca->setMaterial(Mblanco);


    cabeza->setColorFalso({0.0,1.0,0.0});
    cabezaBlanca->setColorFalso({0.0,1.0,0.0});

    cabeza->setColorAux({30.0/255.0,142.0/255.0,255.0/255.0});
    cabezaBlanca->setColorAux({254.0/255.0,254.0/255.0,254.0/255.0});

    cabeza->setMaterialAux(Mcabeza);
    cabezaBlanca->setMaterialAux(Mblanco);

}

void Cabeza::draw(float giro,int modo, char letra, bool tapa, bool TenemosCono, bool suave, bool plano,bool ra) {

    glPushMatrix();
    glScalef(3.25,3.25,3.25);
    cabeza->drawObj(modo,letra,tapa,false,suave,plano,ra);

    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0,-0.3*25,2.35*25);
    glRotatef(90.0,0.0,0.0,1.0);
    glScalef(2.3,2.3,1.0);
    cabezaBlanca->drawObj(modo,letra,tapa,false,suave,plano,ra);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0.0,4.75*25,1.0*25);
    gorrocoptero->draw(giro,modo,letra,tapa,TenemosCono,suave,plano,ra);
    glRotatef(10.0,1.0,0.0,0.0);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0.0,0.6*25,3.75*25);
    nariz->draw(modo,letra,tapa,TenemosCono,suave,plano,ra);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0.0,1.4*25,3.35*25);
    ojos->draw(modo,letra,tapa,TenemosCono,suave,plano,ra);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0.0,0.3*25,3.6*25);
    bigotes->draw(modo,letra,tapa,TenemosCono,suave,plano,ra);
    glPopMatrix();


    boca->draw(modo,letra,tapa,TenemosCono,suave,plano,ra);


}

void Cabeza::cambiarAmarillo(bool poneQuita)
{
    cabeza->cambiarAmarillo(poneQuita);
    cabezaBlanca->cambiarAmarillo(poneQuita);
    gorrocoptero->cambiarAmarillo(poneQuita);
    nariz->cambiarAmarillo(poneQuita);
    ojos->cambiarAmarillo(poneQuita);
    bigotes->cambiarAmarillo(poneQuita);
    boca->cambiarAmarillo(poneQuita);
}

