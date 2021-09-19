//
// Created by santiago on 19/11/20.
//
#include "luz.h"

#ifndef PRACTICA_1_LUZPOSICIONAL_H
#define PRACTICA_1_LUZPOSICIONAL_H

class LuzPosicional : public Luz {
public :
    LuzPosicional(Tupla3f posicion,GLenum idLuzOpenGL,Tupla4f colorAmbiente,Tupla4f colorEspecular,Tupla4f colorDifuso);

    void animarLuz();

    float movimientoLuz=0;
    bool cambia=false;
};

#endif //PRACTICA_1_LUZPOSICIONAL_H
