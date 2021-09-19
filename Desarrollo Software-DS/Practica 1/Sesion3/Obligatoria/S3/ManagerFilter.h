#ifndef MANAGERFILTER_H
#define MANAGERFILTER_H

#include<iostream>
#include"CadenaFiltro.h"
#include"tecnico.h"

class ManagerFilter{

    private:
    Tecnico * tec;
    CadenaFiltro * cf;

    public:

    ManagerFilter(Tecnico * t);

    void crearCadena();

    void operacionFiltrar();
};

#endif