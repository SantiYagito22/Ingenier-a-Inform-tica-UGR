#ifndef TECNICO_H
#define TECNICO_H

#include<iostream>
#include"trabajo.h"
#include "parteTrabajo.h"
#include<string>
#include<vector>
using namespace std;

class Tecnico{

    private:
    string nombre;
    int edad;
    Trabajo * trbRealizar;

    public:
    Tecnico(string n,int e);

    
    
    void realizarTrabajo();
    
    string getNombre(){return nombre;};
    void setNombre(string n){nombre=n;};
    int getEdad(){return edad;};
    void setEdad(int e){edad=e;};
    Trabajo * getTrabajo(){return trbRealizar;};
    void cobrar();

    void cogerTrabajo(int id,vector<Trabajo *> trbs);
    
};

#endif