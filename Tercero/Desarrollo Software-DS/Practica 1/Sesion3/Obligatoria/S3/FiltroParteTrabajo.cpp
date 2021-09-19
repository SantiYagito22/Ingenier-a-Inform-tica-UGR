#include "FiltroParteTrabajo.h"

FiltroParteTrabajo::FiltroParteTrabajo()
{
    pt = new parteTrabajo(0,0,0,0);
    pt->rellenarParteTrabajo();
}

void FiltroParteTrabajo::filtrar(Trabajo * t)
{
  
    if(pt->getDificultad()<5){
        t->setPresupuesto(t->getPresupuesto()-30);
    }
    else if(pt->getDificultad()>5 && pt->getDificultad()<8)
       t->setPresupuesto(t->getPresupuesto()+10);
    else
        t->setPresupuesto(t->getPresupuesto()+20);

    if(pt->getHoras()>4)
    t->setPresupuesto(t->getPresupuesto()+(5*pt->getHoras()));
    
    t->setPresupuesto(t->getPresupuesto()+pt->getGastosMateriales());
    t->setPresupuesto(t->getPresupuesto()+pt->getGastosTransporte());
    
}