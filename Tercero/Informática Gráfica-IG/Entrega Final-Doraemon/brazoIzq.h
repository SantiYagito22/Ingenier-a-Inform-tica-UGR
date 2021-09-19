//
// Created by santiago on 3/12/20.
//
#include "malla.h"
#include "esfera.h"
#include "cilindro.h"

#ifndef PRACTICA_1_BRAZOIZQ_H
#define PRACTICA_1_BRAZOIZQ_H

class BrazoIzq : public Malla3D{
protected:
    Cilindro * brazoizq=nullptr;
    Esfera * visagra= nullptr;
    Esfera * mano= nullptr;
    Material Mbrazo,Mblanco;

public:

    BrazoIzq();

    void draw(float rotacion,int modo,char letra, bool tapa, bool TenemosCono, bool suave, bool plano,bool ra);
    void cambiarAmarillo(bool poneQuita);
};
#endif //PRACTICA_1_BRAZOIZQ_H
