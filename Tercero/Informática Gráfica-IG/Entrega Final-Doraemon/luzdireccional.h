//
// Created by santiago on 19/11/20.
//
#include "luz.h"


#ifndef PRACTICA_1_LUZDIRECCIONAL_H
#define PRACTICA_1_LUZDIRECCIONAL_H

class LuzDireccional : public Luz{
protected:
    float alpha;
    float beta;

public:
    LuzDireccional(Tupla2f direccion,GLenum idLuzOpenGL,Tupla4f colorAmbiente,Tupla4f colorEspecular,Tupla4f colorDifuso);

    // Cambiar ángulo:
    void variarAnguloAlpha ( float incremento ) ;
    void variarAnguloBeta ( float incremento ) ;

};

#endif //PRACTICA_1_LUZDIRECCIONAL_H
