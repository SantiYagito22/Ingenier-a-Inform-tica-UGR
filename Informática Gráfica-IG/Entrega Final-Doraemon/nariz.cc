#include "nariz.h"

Nariz::Nariz() {
    mostacho=new Cilindro(2,50,25,50,'Y',false);
    narizRoja=new Esfera(20,40,25,'Y',false);
    narizRoja->inicializarColores();
    mostacho->inicializarColores();
    narizRoja->cambiarColores({1.0,0.0,0.0});
    mostacho->cambiarColores({0.0,0.0,0.0});

    negro=Material({0.0,0.0,0.0,1.0},{0.0,0.0,0.0,1.0},{0.0,0.0,0.0,1.0},1.0);
    rojo=Material({0.61424,0.04136,0.04136,1.0},{0.727811,0.626959,0.626959,1.0},{0.1745,0.01175,0.01175,1.0},0.6);
    mostacho->setMaterial(negro);
    narizRoja->setMaterial(rojo);

    mostacho->setColorFalso({0.0,1.0,0.0});
    narizRoja->setColorFalso({0.0,1.0,0.0});

    mostacho->setColorAux({0.0,0.0,0.0});
    narizRoja->setColorAux({1.0,0.0,0.0});

    mostacho->setMaterialAux(negro);
    narizRoja->setMaterialAux(rojo);

}

void Nariz::draw(int modo, char color, bool tapa, bool TenemosCono, bool suave, bool plano,bool ra) {
    glPushMatrix();
    glTranslatef(0.0,-1.25*25,0.0);
    glScalef(0.01,1.35,0.01);
    mostacho->drawObj(modo,color,tapa,false,suave,plano,ra);
    glPopMatrix();

    glPushMatrix();
    glScalef(0.3,0.3,0.3);
    narizRoja->drawObj(modo,color,tapa,false,suave,plano,ra);
    glPopMatrix();
}

void Nariz::cambiarAmarillo(bool poneQuita) {
    mostacho->cambiarAmarillo(poneQuita);
    narizRoja->cambiarAmarillo(poneQuita);
}