#include "bigotes.h"

Bigotes::Bigotes() {
    bigote=new Cilindro(2,50,25,50,'Y',false);
    bigote->inicializarColores();
    bigote->cambiarColores({0.0,0.0,0.0});
    negro=Material({0.0,0.0,0.0,1.0},{0.0,0.0,0.0,1.0},{0.0,0.0,0.0,1.0},1.0);
    bigote->setMaterial(negro);

    bigote->setColorFalso({0.0,1.0,0.0});

    bigote->setColorAux({0.0,0.0,0.0});
    bigote->setMaterialAux(negro);
}

void Bigotes::draw(int modo, char letra, bool tapa, bool TenemosCono, bool suave, bool plano,bool ra) {
    glPushMatrix();
    glTranslatef(0.75*25,0.4*25,0.0);
    glRotatef(-65.0,0.0,0.0,1.0);
    glScalef(0.01,1.0,0.01);
    bigote->drawObj(modo,letra,tapa,false,suave,plano,ra);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.75*25,0.0,0.0);
    glRotatef(-90.0,0.0,0.0,1.0);
    glScalef(0.01,1.0,0.01);
    bigote->drawObj(modo,letra,tapa,false,suave,plano,ra);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.75*25,-0.4*25,0.0);
    glRotatef(-115.0,0.0,0.0,1.0);
    glScalef(0.01,1.0,0.01);
    bigote->drawObj(modo,letra,tapa,false,suave,plano,ra);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.75*25,0.4*25,0.0);
    glRotatef(65.0,0.0,0.0,1.0);
    glScalef(0.01,1.0,0.01);
    bigote->drawObj(modo,letra,tapa,false,suave,plano,ra);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-0.75*25,0.0,0.0);
    glRotatef(90.0,0.0,0.0,1.0);
    glScalef(0.01,1.0,0.01);
    bigote->drawObj(modo,letra,tapa,false,suave,plano,ra);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.75*25,-0.4*25,0.0);
    glRotatef(115.0,0.0,0.0,1.0);
    glScalef(0.01,1.0,0.01);
    bigote->drawObj(modo,letra,tapa,false,suave,plano,ra);
    glPopMatrix();
}

void Bigotes::cambiarAmarillo(bool poneQuita) {
    bigote->cambiarAmarillo(poneQuita);
}