#include "ManagerFilter.h"

ManagerFilter::ManagerFilter(Tecnico * t)
{
    this->tec=t;
    cf=new CadenaFiltro();
    
    crearCadena();
    
}

void ManagerFilter::crearCadena(){
    
    cf->generar();
    
}    

void ManagerFilter::operacionFiltrar(){
    cf->filtrar(tec->getTrabajo());
    
}