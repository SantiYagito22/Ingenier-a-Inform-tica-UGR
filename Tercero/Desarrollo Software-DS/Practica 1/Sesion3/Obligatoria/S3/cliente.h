#ifndef CLIENTE_H
#define CLIENTE_H

#include<iostream>
#include"trabajo.h"
#include"parteTecnico.h"
#include"tecnico.h"
#include"ManagerFilter.h"
#include <string>
using namespace std;


class Cliente{

    private:
    string nombre;
    int edad;
    Trabajo * trb;
    public:

    Cliente(string n,int e);
        
    Trabajo * crearTrabajo(float pres,string t, int i);

    void pagar(Tecnico * t);
    

    string getNombre(){return nombre;};
    void setNombre(string n){nombre=n;};
    int getEdad(){return edad;};
    void setEdad(int e){edad=e;};
    
    


    
};

#endif