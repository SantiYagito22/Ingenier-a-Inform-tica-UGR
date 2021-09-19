//
// Created by santiago on 3/12/20.
//
#include "malla.h"
#include "objrevolucion.h"
#include "cilindro.h"
#include "esfera.h"
#ifndef PRACTICA_1_COLLAR_H
#define PRACTICA_1_COLLAR_H
class Collar : public Malla3D{
protected:
    Cilindro * hueco= nullptr;
    Cilindro * collar= nullptr;
    Esfera * cascabel= nullptr;
    Cilindro * cascabelSaliente= nullptr;
    Material rojo,oro,negro;

public:
    Collar();

    void draw(int modo,char letra,bool tapa,bool TenemosCono,bool suave,bool plano,bool ra);

    void cambiarAmarillo(bool poneQuita);

};
#endif //PRACTICA_1_COLLAR_H
