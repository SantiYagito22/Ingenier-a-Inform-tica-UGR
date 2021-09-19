//
// Created by santiago on 3/12/20.
//
#include "malla.h"
#include "esfera.h"
#include "objrevolucion.h"

#ifndef PRACTICA_1_OJOS_H
#define PRACTICA_1_OJOS_H
class Ojos : public Malla3D{
protected:
    Esfera * ojo=nullptr;
    Esfera * pupila=nullptr;
    Material Mblanco,negro;
public:
    Ojos();

    void draw(int modo, char letra, bool tapa, bool TenemosCono, bool suave, bool plano,bool ra);
    void cambiarAmarillo(bool poneQuita);
};
#endif //PRACTICA_1_OJOS_H
