//
// Created by santiago on 3/11/20.
//
#include "objrevolucion.h"
#include "malla.h"
#include "aux.h"

#ifndef PRACTICA_1_CILINDRO_H
#define PRACTICA_1_CILINDRO_H
class Cilindro : public ObjRevolucion
{
public:
    Cilindro(const int num_vert_perfil,const int num_instancias_perf,const float altura,const float radio,const char rotacion,bool text);
};
#endif //PRACTICA_1_CILINDRO_H
