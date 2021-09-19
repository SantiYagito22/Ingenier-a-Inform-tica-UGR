#include "brazoDch.h"

BrazoDch::BrazoDch() {
    brazodch=new Cilindro(10,50,25,50,'Y',false);
    mano=new Esfera(20,40,25,'Y',false);
    visagra=new Esfera(20,40,25,'Y',false);

    brazodch->inicializarColores();
    mano->inicializarColores();
    visagra->inicializarColores();


    brazodch->cambiarColores({30.0/255.0,142.0/255.0,255.0/255.0});
    visagra->cambiarColores({30.0/255.0,142.0/255.0,255.0/255.0});
    mano->cambiarColores({242.0/255.0,242.0/255.0,242.0/255.0});

    Mbrazo=Material({0.396, 0.74151, 0.69102, 0.8},{0.297254, 0.30829, 0.306678, 0.8},{0.1, 0.18725, 0.1745, 0.8},12.8);
    Mblanco=Material({0.55,0.55,0.55,1.0},{0.70,0.70,0.70,1.0},{0.0,0.0,0.0,1.0},0.25);

    brazodch->setMaterial(Mbrazo);
    mano->setMaterial(Mblanco);

    brazodch->setColorFalso({0.0,1.0,0.0});
    mano->setColorFalso({0.0,1.0,0.0});
    visagra->setColorFalso({0.0,1.0,0.0});

    brazodch->setColorAux({30.0/255.0,142.0/255.0,255.0/255.0});
    visagra->setColorAux({30.0/255.0,142.0/255.0,255.0/255.0});
    mano->setColorAux({242.0/255.0,242.0/255.0,242.0/255.0});

    brazodch->setMaterialAux(Mbrazo);
    mano->setMaterialAux(Mblanco);


}

void BrazoDch::draw(float rotacion, int modo, char letra, bool tapa, bool TenemosCono, bool suave, bool plano,bool ra) {

    glPushMatrix();
    glRotatef(rotacion,0.0,0.0,1.0); //Movimiento brazo entero[-35,35]
    visagra->drawObj(modo,letra,tapa,false,suave,plano,ra);


    glPushMatrix();
    glTranslatef(0.5*25,0.0,0.0);
    glPushMatrix();
    glRotatef(-90.0,0.0,0.0,1.0);
    glScalef(0.6,4.0,0.6);
    brazodch->drawObj(modo,letra,tapa,false,suave,plano,ra);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(4.0*25,0.0,0.0);
    glScalef(1.25,1.25,1.25);
    mano->drawObj(modo,letra,tapa,false,suave,plano,ra);
    glPopMatrix();

    glPopMatrix();
    glPopMatrix();
}

void BrazoDch::cambiarAmarillo(bool poneQuita) {
    brazodch->cambiarAmarillo(poneQuita);
    mano->cambiarAmarillo(poneQuita);
}