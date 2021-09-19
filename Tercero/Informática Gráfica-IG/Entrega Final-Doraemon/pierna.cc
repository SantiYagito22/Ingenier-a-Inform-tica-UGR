#include "pierna.h"

Pierna::Pierna() {
    pierna=new Cilindro(10,50,25,50,'Y',false);
    pie=new Cilindro(10,50,25,50,'Y',false);
    pierna->inicializarColores();
    pie->inicializarColores();
    pie->cambiarColores({242.0/255.0,242.0/255.0,242.0/255.0});
    pierna->cambiarColores({30.0/255.0,142.0/255.0,255.0/255.0});


    Mpierna=Material({0.396, 0.74151, 0.69102, 0.8},{0.297254, 0.30829, 0.306678, 0.8},{0.1, 0.18725, 0.1745, 0.8},12.8);
    Mblanco=Material({0.55,0.55,0.55,1.0},{0.70,0.70,0.70,1.0},{0.0,0.0,0.0,1.0},0.25);

    pierna->setMaterial(Mpierna);
    pie->setMaterial(Mblanco);

    pierna->setColorFalso({0.0,1.0,0.0});
    pie->setColorFalso({0.0,1.0,0.0});

    pie->setColorAux({242.0/255.0,242.0/255.0,242.0/255.0});
    pierna->setColorAux({30.0/255.0,142.0/255.0,255.0/255.0});

    pierna->setMaterialAux(Mpierna);
    pie->setMaterialAux(Mblanco);
}

void Pierna::draw(int modo, char letra, bool tapa, bool TenemosCono, bool suave, bool plano,bool ra) {

    glPushMatrix();
    glTranslatef(0.0,0.0,-0.25*25);
    glScalef(0.6,3.0,0.5);
    pierna->drawObj(modo,letra,tapa,false,suave,plano,ra);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0,-0.3*25,-0.25*25);
    glScalef(0.7,0.5,0.6);
    pie->drawObj(modo,letra,tapa,false,suave,plano,ra);
    glPopMatrix();





}

void Pierna::cambiarAmarillo(bool poneQuita) {
    pierna->cambiarAmarillo(poneQuita);
    pie->cambiarAmarillo(poneQuita);
}