//
// Created by santiago on 3/12/20.
//
#include "malla.h"
#include "objrevolucion.h"
#include "esfera.h"
#include "cilindro.h"

#ifndef PRACTICA_1_BRAZODCH_H
#define PRACTICA_1_BRAZODCH_H
class BrazoDch : public Malla3D{
protected:
    Cilindro * brazodch=nullptr;
    Esfera * visagra= nullptr;
    Esfera * mano= nullptr;
    Material Mbrazo,Mblanco;

public:

    BrazoDch();

    void draw(float rotacion,int modo,char letra, bool tapa, bool TenemosCono, bool suave, bool plano,bool ra);
    void cambiarAmarillo(bool poneQuita);
};
#endif //PRACTICA_1_BRAZODCH_H
