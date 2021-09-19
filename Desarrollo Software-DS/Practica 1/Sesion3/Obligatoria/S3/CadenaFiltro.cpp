#include"CadenaFiltro.h"


CadenaFiltro::CadenaFiltro(){
    cadena.clear();
}

void CadenaFiltro::filtrar(Trabajo *  t){
    cadena[0]->filtrar(t);
    cadena[1]->filtrar(t);
}

void CadenaFiltro::generar(){

    /*
    FiltroParteTecnico * parte = new FiltroParteTecnico();
  
    cadena.push_back((Filtro *)  parte);

    FiltroParteTrabajo * parte2 = new FiltroParteTrabajo();
    
    cadena.push_back((Filtro *)  parte2);
    */

    Filtro * p1=  new FiltroParteTecnico();

    cadena.push_back(p1);

    Filtro * p2 = new FiltroParteTrabajo();
    
    cadena.push_back(p2);

}