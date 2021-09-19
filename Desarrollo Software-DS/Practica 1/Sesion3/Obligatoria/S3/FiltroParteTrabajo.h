#ifndef FILTROPARTETRABAJO_H
#define FILTROPARTETRABAJO_H
#include"Filtro.h"
#include"parteTrabajo.h"

class FiltroParteTrabajo : public Filtro{

private:
    parteTrabajo * pt;


public:

    FiltroParteTrabajo();

    virtual void filtrar(Trabajo * t);

};
#endif