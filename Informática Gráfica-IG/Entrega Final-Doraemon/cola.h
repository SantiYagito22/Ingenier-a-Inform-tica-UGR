//
// Created by santiago on 3/12/20.
//
#include "malla.h"
#include "esfera.h"
#include "cilindro.h"
#include "objrevolucion.h"


#ifndef PRACTICA_1_COLA_H
#define PRACTICA_1_COLA_H
class Cola : public Malla3D{
protected:
    Cilindro * cola= nullptr;
    Esfera * bola= nullptr;
    Material negro,rojo;
public:

    Cola();

    void draw(float rotacion,int modo, char letra, bool tapa, bool TenemosCono, bool suave, bool plano,bool ra);
    void cambiarAmarillo(bool poneQuita);

};
#endif //PRACTICA_1_COLA_H
