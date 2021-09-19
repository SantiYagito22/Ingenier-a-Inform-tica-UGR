#include "cuerpo.h"

Cuerpo::Cuerpo() {
    cola=new Cola();
    tronco= new Cilindro(5,50,25,50,'Y',false);
    bolsillo=new SemiEsfera(20,40,25,'Y',false);
    panza=new Esfera(20,40,25,'Y',false);

    bolsillo->inicializarColores();
    tronco->inicializarColores();
    panza->inicializarColores();

    panza->cambiarColores({1.0,1.0,1.0});
    tronco->cambiarColores({30.0/255.0,142.0/255.0,255.0/255.0});
    bolsillo->cambiarColores({242.0/255.0,242.0/255.0,242.0/255.0});

    Mcuerpo=Material({0.396, 0.74151, 0.69102, 0.8},{0.297254, 0.30829, 0.306678, 0.8},{0.1, 0.18725, 0.1745, 0.8},12.8);
    Mblanco=Material({0.55,0.55,0.55,1.0},{0.70,0.70,0.70,1.0},{0.0,0.0,0.0,1.0},0.25);
    tronco->setMaterial(Mcuerpo);
    panza->setMaterial(Mblanco);
    bolsillo->setMaterial(Mblanco);

    tronco->setColorFalso({0.0,1.0,0.0});
    bolsillo->setColorFalso({0.0,1.0,0.0});
    panza->setColorFalso({0.0,1.0,0.0});

    panza->setColorAux({1.0,1.0,1.0});
    tronco->setColorAux({30.0/255.0,142.0/255.0,255.0/255.0});
    bolsillo->setColorAux({242.0/255.0,242.0/255.0,242.0/255.0});

    tronco->setMaterialAux(Mcuerpo);
    panza->setMaterialAux(Mblanco);
    bolsillo->setMaterialAux(Mblanco);



}

void Cuerpo::draw(float rotacion,int modo, char letra, bool tapa, bool TenemosCono, bool suave, bool plano,bool ra) {

    glPushMatrix();
    glScalef(1.5,5.0,1);
    tronco->drawObj(modo,letra,tapa,false,suave,plano,ra);
    glPopMatrix();



    glPushMatrix();
    glTranslatef(0.0,2.6*25,2*25);
    glScalef(2.0,2.0,1.0);
    panza->drawObj(modo,letra,tapa,false,suave,plano,ra);
    glPopMatrix();



    glPushMatrix();
    glTranslatef(0.0,3.0*25,3*25);
    glScalef(1.5,1.5,0.5);
    bolsillo->drawObj(modo,letra,tapa,false,suave,plano,ra);
    glPopMatrix();



    glPushMatrix();
    cola->draw(rotacion,modo,letra,tapa,false,suave,plano,ra);
    glPopMatrix();



}

void Cuerpo::cambiarAmarillo(bool poneQuita) {
    tronco->cambiarAmarillo(poneQuita);
    panza->cambiarAmarillo(poneQuita);
    bolsillo->cambiarAmarillo(poneQuita);
    cola->cambiarAmarillo(poneQuita);
}