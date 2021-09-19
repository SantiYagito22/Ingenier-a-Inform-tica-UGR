//
// Created by santiago on 3/12/20.
//
#include "malla.h"
#include "objrevolucion.h"
#include "esfera.h"
#include "cilindro.h"

#ifndef PRACTICA_1_NARIZ_H
#define PRACTICA_1_NARIZ_H
class Nariz : public Malla3D{
protected:
    Cilindro * mostacho=nullptr;
    Esfera * narizRoja=nullptr;
    Material negro,rojo;
public:
    Nariz();

    void draw(int modo,char color,bool tapa,bool TenemosCono,bool suave,bool plano,bool ra);

    void cambiarAmarillo(bool poneQuita);
};
#endif //PRACTICA_1_NARIZ_H
