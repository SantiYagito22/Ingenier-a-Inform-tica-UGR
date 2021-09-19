//
// Created by santiago on 30/11/20.
//
#include "objrevolucion.h"
#include "malla.h"
#include "aux.h"

#ifndef PRACTICA_1_SEMIESFERA_H
#define PRACTICA_1_SEMIESFERA_H
class SemiEsfera : public ObjRevolucion
{
public:
    SemiEsfera(const int num_vert_perfil,const int num_instancias_perfil,const float radio,char rotacion,bool text);

};

#endif //PRACTICA_1_SEMIESFERA_H
