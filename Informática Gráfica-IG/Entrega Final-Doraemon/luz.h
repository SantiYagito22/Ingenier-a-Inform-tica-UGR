//
// Created by santiago on 19/11/20.
//
#include "aux.h"


#ifndef PRACTICA_1_LUZ_H
#define PRACTICA_1_LUZ_H

class Luz
{
protected:

    Tupla4f posicion;
    Tupla4f colorAmbiente;
    Tupla4f colorDifuso;
    Tupla4f colorEspecular;
    GLenum id;

public:
    void activar();

    void desactivar();
};
#endif //PRACTICA_1_LUZ_H
