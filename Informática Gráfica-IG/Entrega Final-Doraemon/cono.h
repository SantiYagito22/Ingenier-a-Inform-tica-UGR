//
// Created by santiago on 5/11/20.
//

#include "objrevolucion.h"
#include "malla.h"
#include "aux.h"

#ifndef PRACTICA_1_CONO_H
#define PRACTICA_1_CONO_H
class Cono : public ObjRevolucion
{
public:
    Cono(const int num_vert_perfil,const int num_instancias_perf,const float altura,const float radio,char rotacion,bool text);
};

#endif //PRACTICA_1_CONO_H
