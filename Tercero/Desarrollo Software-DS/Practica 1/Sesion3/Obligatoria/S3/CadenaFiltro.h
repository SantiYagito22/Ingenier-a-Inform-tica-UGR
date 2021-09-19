#ifndef CADENAFILTRO_H
#define CADENAFILTRO_H

#include<iostream>
#include<vector>
#include"Filtro.h"
#include"FiltroParteTecnico.h" 
#include"FiltroParteTrabajo.h"

using namespace std;

class CadenaFiltro{
    
    private:
        vector<Filtro *> cadena;

    public:

    CadenaFiltro();

    void filtrar(Trabajo * t);

    void generar(); //meter filtros en la cadena

};
#endif