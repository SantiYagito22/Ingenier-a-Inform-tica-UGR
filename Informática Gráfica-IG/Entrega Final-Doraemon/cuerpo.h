//
// Created by santiago on 3/12/20.
//
#include "malla.h"
#include "objrevolucion.h"
#include "semiesfera.h"
#include "esfera.h"
#include "cilindro.h"
#include "cola.h"



#ifndef PRACTICA_1_CUERPO_H
#define PRACTICA_1_CUERPO_H
class Cuerpo : public Malla3D{
protected:
    Esfera * panza= nullptr;
    SemiEsfera * bolsillo= nullptr;
    Cilindro * tronco= nullptr;
    Cola * cola= nullptr;
    Material Mcuerpo,Mblanco;


public:
    Cuerpo();

    void draw(float rotacion,int modo,char letra, bool tapa, bool TenemosCono, bool suave, bool plano,bool ra);
    void cambiarAmarillo(bool poneQuita);

};
#endif //PRACTICA_1_CUERPO_H
