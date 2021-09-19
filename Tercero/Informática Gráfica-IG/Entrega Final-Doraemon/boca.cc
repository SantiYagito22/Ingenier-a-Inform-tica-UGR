#include "boca.h"

Boca::Boca() {
    boca = new SemiEsfera(20, 40, 25, 'Y',false);
    lengua = new Esfera(20, 40, 25, 'Y',false);
    boca->inicializarColores();
    lengua->inicializarColores();
    rojo=Material({0.61424,0.04136,0.04136,1.0},{0.727811,0.626959,0.626959,1.0},{0.1745,0.01175,0.01175,1.0},0.6);
    leng=Material({0.7038,0.27048,0.0828,1.0 },{0.256777, 0.137622, 0.086014, 1.0 },{0.19125, 0.0735, 0.0225, 1.0 },12.8);
    lengua->cambiarColores({255.0 / 255.0, 138.0 / 255.0, 5.0 / 255.0});
    boca->cambiarColores({1.0,0,0});
    boca->setMaterial(rojo);
    lengua->setMaterial(leng);

    boca->setColorFalso({0.0,1.0,0.0});
    lengua->setColorFalso({0.0,1.0,0.0});

    boca->setColorAux({1.0,0,0});
    lengua->setColorAux({255.0 / 255.0, 138.0 / 255.0, 5.0 / 255.0});

    boca->setMaterialAux(rojo);
    lengua->setMaterialAux(leng);

}

void Boca::draw(int modo, char letra, bool tapa, bool TenemosCono, bool suave, bool plano,bool ra) {
    glPushMatrix();
    glTranslatef(0.0,-0.4*25,3.25*25);
    glScalef(1.5,1.5,0.5);
    boca->drawObj(modo,letra,tapa,false,suave,plano,ra);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0,-1.25*25,3.5*25);
    glScalef(0.7,0.4,0.3);
    lengua->drawObj(modo,letra,tapa,false,suave,plano,ra);
    glPopMatrix();

}
void Boca::cambiarAmarillo(bool poneQuita) {
    boca->cambiarAmarillo(poneQuita);
    lengua->cambiarAmarillo(poneQuita);

}