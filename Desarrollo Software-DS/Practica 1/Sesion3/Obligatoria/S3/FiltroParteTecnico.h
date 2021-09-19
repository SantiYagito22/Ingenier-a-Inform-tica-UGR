#ifndef FILTROPARTETECNICO_H
#define FILTROPARTETECNICO_H

#include"Filtro.h"
#include"parteTecnico.h"

class FiltroParteTecnico : public Filtro{

private:
    parteTecnico * pt;


public:

    FiltroParteTecnico();

    virtual void filtrar(Trabajo * t);

};

#endif