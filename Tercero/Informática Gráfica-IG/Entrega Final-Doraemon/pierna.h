//
// Created by santiago on 3/12/20.
//
#include "malla.h"
#include "objrevolucion.h"
#include "cilindro.h"

#ifndef PRACTICA_1_PIERNA_H
#define PRACTICA_1_PIERNA_H
class Pierna : public Malla3D{
protected:
    Cilindro * pierna=nullptr;
    Cilindro * pie=nullptr;
    Material Mpierna,Mblanco;
public:
    Pierna();

    void draw(int modo,char letra, bool tapa, bool TenemosCono, bool suave, bool plano,bool ra);
    void cambiarAmarillo(bool poneQuita);

};
#endif //PRACTICA_1_PIERNA_H
