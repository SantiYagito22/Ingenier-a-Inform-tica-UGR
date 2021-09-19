#include "ojos.h"

Ojos::Ojos() {
    ojo=new Esfera(20,40,25,'Y',false);
    pupila=new Esfera(20,40,25,'Y',false);
    ojo->inicializarColores();
    pupila->inicializarColores();
    pupila->cambiarColores({0.0,0.0,0.0});
    ojo->cambiarColores({1.0,1.0,1.0});
    Mblanco=Material({0.55,0.55,0.55,1.0},{0.70,0.70,0.70,1.0},{0.0,0.0,0.0,1.0},0.25);
    negro=Material({0.0,0.0,0.0,1.0},{0.0,0.0,0.0,1.0},{0.0,0.0,0.0,1.0},1.0);
    ojo->setMaterial(Mblanco);
    pupila->setMaterial(negro);

    ojo->setColorFalso({0.0,1.0,0.0});
    pupila->setColorFalso({0.0,1.0,0.0});

    ojo->setColorAux({1.0,1.0,1.0});
    pupila->setColorAux({0.0,0.0,0.0});

    ojo->setMaterialAux(Mblanco);
    pupila->setMaterialAux(negro);
}

void Ojos::draw(int modo, char letra, bool tapa, bool TenemosCono, bool suave, bool plano,bool ra) {
    glPushMatrix();
    glTranslatef(-0.5*25,0.0,0.0);
    glRotatef(-10.0,0.0,0.0,1.0);
    glScalef(0.4,0.6,0.4);
    ojo->drawObj(modo,letra,tapa,false,suave,plano,ra);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.5*25,0.0,0.0);
    glRotatef(10.0,0.0,0.0,1.0);
    glScalef(0.4,0.6,0.4);
    ojo->drawObj(modo,letra,tapa,false,suave,plano,ra);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.4*25,-0.2*25,0.3*25);
    glScalef(0.15,0.2,0.15);
    pupila->drawObj(modo,letra,tapa,false,suave,plano,ra);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.4*25,-0.2*25,0.3*25);
    glScalef(0.15,0.2,0.15);
    pupila->drawObj(modo,letra,tapa,false,suave,plano,ra);
    glPopMatrix();
}

void Ojos::cambiarAmarillo(bool poneQuita) {
    ojo->cambiarAmarillo(poneQuita);
    pupila->cambiarAmarillo(poneQuita);
}