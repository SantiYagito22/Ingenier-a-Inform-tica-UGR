#include "cola.h"

Cola::Cola() {
    bola=new Esfera(20,40,25,'Y',false);
    cola=new Cilindro(2,50,25,50,'Y',false);

    bola->inicializarColores();
    cola->inicializarColores();

    bola->cambiarColores({1.0,0.0,0.0});
    cola->cambiarColores({0.0,0.0,0.0});

    negro=Material({0.0,0.0,0.0,1.0},{0.0,0.0,0.0,1.0},{0.0,0.0,0.0,1.0},1.0);
    rojo=Material({0.61424,0.04136,0.04136,1.0},{0.727811,0.626959,0.626959,1.0},{0.1745,0.01175,0.01175,1.0},0.6);

    cola->setMaterial(negro);
    bola->setMaterial(rojo);

    bola->setColorFalso({0.0,1.0,0.0});
    cola->setColorFalso({0.0,1.0,0.0});

    bola->setColorAux({1.0,0.0,0.0});
    cola->setColorAux({0.0,0.0,0.0});

    cola->setMaterialAux(negro);
    bola->setMaterialAux(rojo);

}

void Cola::draw(float rotacion,int modo, char letra, bool tapa, bool TenemosCono, bool suave, bool plano,bool ra) {
    glPushMatrix();
    glTranslatef(0,1*25,-1.75*25);
    glRotatef(rotacion,1.0,0.0,0.0); //movimiento cola[-20,15]

    glPushMatrix();
    glRotatef(-90.0,1.0,0.0,0.0);
    glScalef(0.01,1.5,0.01);
    cola->drawObj(modo,letra,tapa,false,suave,plano,ra);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,0.0,-1.75*25);
    glScalef(0.3,0.3,0.3);
    bola->drawObj(modo,letra,tapa,false,suave,plano,ra);
    glPopMatrix();

    glPopMatrix();
}

void Cola::cambiarAmarillo(bool poneQuita) {
    cola->cambiarAmarillo(poneQuita);
    bola->cambiarAmarillo(poneQuita);
}