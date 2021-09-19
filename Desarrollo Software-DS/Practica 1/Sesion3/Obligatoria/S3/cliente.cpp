#include<cliente.h>

using namespace std;
Cliente::Cliente(string n,int e)
{
    this->edad=e;
    this->nombre=n;
    this->trb=nullptr;
}

Trabajo * Cliente::crearTrabajo(float pres,string t,int i)
{
    
    trb = new Trabajo(pres,t,i);
    cout<<"El cliente "<<this->nombre<<" ha creado el trabajo con id "<<i<<" y presupuesto "<<trb->getPresupuesto()<<endl;
    return trb;
    
}


void Cliente::pagar(Tecnico * t){
    ManagerFilter * mf=new ManagerFilter(t);

    mf->operacionFiltrar();
    t->cobrar();
}
