#include "puerta.h"

Puerta::Puerta() {
    puerta=new Cubo(50);
    pomo=new Cilindro(2,50,25,50,'Y',false);
    pomo->inicializarColores();
    puerta->inicializarColores();

    rosa=Material({1.0f, 0.829, 0.829, 0.922},{0.296648, 0.296648, 0.296648, 0.922 },{0.25, 0.20725, 0.20725, 0.922},11.264);
    puerta->setMaterialAux(rosa);
    puerta->setMaterial(rosa);

    gris=Material({0.50754, 0.50754, 0.50754, 1.0},{0.508273, 0.508273f, 0.508273f, 1.0f },{0.19225f, 0.19225f, 0.19225f, 1.0f},51.2);
    pomo->setMaterial(gris);
    pomo->setMaterialAux(gris);

    puerta->cambiarColores({255.0/255.0,64.0/255.0,160.0/255.0});
    puerta->setColorAux({255.0/255.0,64.0/255.0,160.0/255.0});

    pomo->cambiarColores({155.0/255.0,155.0/255.0,155.0/255.0});
    pomo->setColorAux({155.0/255.0,155.0/255.0,155.0/255.0});

    pomo->setColorFalso({1.0,0.0,0.0});
    puerta->setColorFalso({1.0,0.0,0.0});

}


void Puerta::draw(int modo, char color, bool tapa, bool TenemosCono, bool suave, bool plano, bool ra) {

    glPushMatrix();
    glScalef(1.5,3.25,0.15);
    puerta->draw(modo,color,suave,plano,ra);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(1.5*25.0,0.0,0.25*25);
    glRotatef(90.0,1.0,0.0,0.0);
    glScalef(0.25,0.25,0.25);
    pomo->drawObj(modo,color,true,true,suave,plano,ra);
    glPopMatrix();
}

void  Puerta::cambiarAmarillo(bool poneQuita) {
    puerta->cambiarAmarillo(poneQuita);
    pomo->cambiarAmarillo(poneQuita);
}