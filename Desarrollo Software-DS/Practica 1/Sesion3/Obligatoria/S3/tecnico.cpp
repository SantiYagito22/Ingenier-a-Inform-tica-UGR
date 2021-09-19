#include<tecnico.h>

using namespace std;

Tecnico::Tecnico(string n,int e)
{
    this->nombre=n;
    this->edad=e; 
    trbRealizar=nullptr;  
}

void Tecnico::cogerTrabajo(int id,vector  <Trabajo *> trbs)
{
    for(unsigned int i=0; i<trbs.size();i++)
    {
        if(trbs[i]->getID()==id && !trbs[i]->getOcupado())
        {
            trbRealizar=trbs[i];
            trbs[i]->setOcupado(true);
            cout<<"El tecnico "<<this->nombre<<" ha obtenido el trabajo con id: "<<id<<endl;
        }
    }
}


void Tecnico::realizarTrabajo()
{
    cout<<"El tecnico " <<this->nombre <<" realiza el trabajo con id: "<<this->trbRealizar->getID()<<endl;
}

void Tecnico::cobrar()
{
    cout<<"El tecnico " <<this->nombre<<" ha cobrado el trabajo con id "<<this->trbRealizar->getID() <<" con una cantidad de "<<this->trbRealizar->getPresupuesto()<<endl;
}