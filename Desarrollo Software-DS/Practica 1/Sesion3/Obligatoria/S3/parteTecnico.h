#ifndef PARTETECNICO_H
#define PARTETECNICO_H

#include"iostream"

using namespace std;

class parteTecnico{

    //El cliente valorara la actitud y trabajo realizado por el tecnico, la aplicación le dara un bonus según estos valores

    private:
        int notaTrabajo;
        int actitud;    
        bool recomendacion;
       
    
    public:
    
    parteTecnico(int nt,int act,bool rc);
    
    void rellenarParteTecnico();
    

    int getnotaTrabajo(){return notaTrabajo;};
    int getActitud(){return actitud;};
    bool getRecomendacion(){return recomendacion;};
    

};

#endif