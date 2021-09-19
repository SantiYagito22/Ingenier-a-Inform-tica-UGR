//
// Created by santiago on 5/11/20.
//

#include "objrevolucion.h"
#include "malla.h"
#include "aux.h"


#ifndef PRACTICA_1_ESFERA_H
#define PRACTICA_1_ESFERA_H

class Esfera : public ObjRevolucion
{
public:
    Esfera(const int num_vert_perfil,const int num_instancias_perfil,const float radio,char rotacion,bool text);

};

#endif //PRACTICA_1_ESFERA_H
