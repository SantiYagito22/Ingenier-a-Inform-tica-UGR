#include "collar.h"

Collar::Collar() {
    hueco=new Cilindro(2,50,25,50,'Y',false);
    collar=new Cilindro(2,50,25,50,'Y',false);
    cascabelSaliente=new Cilindro(2,50,25,50,'Y',false);
    cascabel=new Esfera(20,40,25,'Y',false);

    hueco->inicializarColores();
    collar->inicializarColores();
    cascabelSaliente->inicializarColores();
    cascabel->inicializarColores();

    cascabel->cambiarColores({230.0/255.0,246.0/255.0,54.0/255.0});
    collar->cambiarColores({1.0,0,0});
    cascabelSaliente->cambiarColores({230.0/255.0,246.0/255.0,54.0/255.0});
    hueco->cambiarColores({0.0,0.0,0.0});

    negro=Material({0.0,0.0,0.0,1.0},{0.0,0.0,0.0,1.0},{0.0,0.0,0.0,1.0},1.0);
    rojo=Material({0.61424,0.04136,0.04136,1.0},{0.727811,0.626959,0.626959,1.0},{0.1745,0.01175,0.01175,1.0},0.6);
    oro=Material({0.75164,0.60648,0.22648,0.5},{0.628281,0.555802,0.366065,0.5},{0.24725,0.1995,0.0745,0.5},0.4);
    collar->setMaterial(rojo);
    cascabel->setMaterial(oro);
    cascabelSaliente->setMaterial(oro);
    hueco->setMaterial(negro);

    hueco->setColorFalso({0.0,1.0,0.0});
    collar->setColorFalso({0.0,1.0,0.0});
    cascabelSaliente->setColorFalso({0.0,1.0,0.0});
    cascabel->setColorFalso({0.0,1.0,0.0});


    cascabel->setColorAux({230.0/255.0,246.0/255.0,54.0/255.0});
    collar->setColorAux({1.0,0,0});
    cascabelSaliente->setColorAux({230.0/255.0,246.0/255.0,54.0/255.0});
    hueco->setColorAux({0.0,0.0,0.0});

    collar->setMaterialAux(rojo);
    cascabel->setMaterialAux(oro);
    cascabelSaliente->setMaterialAux(oro);
    hueco->setMaterialAux(negro);

}


void Collar::draw(int modo, char letra, bool tapa, bool TenemosCono, bool suave, bool plano,bool ra) {

    glPushMatrix();
    glScalef(1,1,1);
    collar->drawObj(modo,letra,true,true,suave,plano,ra);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0.0,-0.1*25,2.25*25);
    glPushMatrix();
    glScalef(0.25,0.05,0.2);
    cascabelSaliente->drawObj(modo,letra,tapa,false,suave,plano,ra);
    glPopMatrix();

    glPushMatrix();
    glScalef(0.3,0.3,0.2);
    cascabel->drawObj(modo,letra,tapa,false,suave,plano,ra);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0.0,-0.3*25,0.2*25);
    glScalef(0.01,0.2,0.01);
    hueco->drawObj(modo,letra,tapa,false,suave,plano,ra);
    glPopMatrix();

    glPopMatrix();


}

void Collar::cambiarAmarillo(bool poneQuita) {
    collar->cambiarAmarillo(poneQuita);
    cascabelSaliente->cambiarAmarillo(poneQuita);
    cascabel->cambiarAmarillo(poneQuita);
    hueco->cambiarAmarillo(poneQuita);


}