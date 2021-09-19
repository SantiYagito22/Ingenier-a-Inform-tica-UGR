#ifndef TRABAJO_H
#define TRABAJO_H

#include<iostream>
#include <string>
using namespace std;

class cliente;

class Trabajo{

   private:
    float presupuesto;
    string tipo;
    int id;
    bool ocupado;
    

   public:

   Trabajo(float p, string tip, int i);

    float getPresupuesto(){return presupuesto;};
    void setPresupuesto(float p){presupuesto=p;};

    string getTipo(){return tipo;};
    void setTipo(string t){tipo=t;};

    int getID(){return id;};
    void setID(int i){id=i;};

    bool getOcupado(){return ocupado;};
    void setOcupado(bool oc){ocupado=oc;};

};

#endif