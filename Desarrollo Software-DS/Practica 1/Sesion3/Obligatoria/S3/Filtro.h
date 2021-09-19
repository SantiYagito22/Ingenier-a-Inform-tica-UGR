#ifndef FILTRO_H
#define FILTRO_H

#include "iostream"
#include"trabajo.h"


class Filtro{

    public:
        
    virtual void filtrar(Trabajo * t)=0;
        
};
#endif