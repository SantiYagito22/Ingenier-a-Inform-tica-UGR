#ifndef PARTETRABAJO_H
#define PARTETRABAJO_H

#include"iostream"

class parteTrabajo{

    private:
        float dificultad;
        float horas;
        float gastosMateriales;
        float gastosTransporte;
    
    public:
    
    parteTrabajo(float df,float h, float gm, float gt);

    void rellenarParteTrabajo();

    float getDificultad(){return dificultad;};
    float getHoras(){return horas;};
    float getGastosMateriales(){return gastosMateriales;};
    float getGastosTransporte(){return gastosTransporte;};

};
#endif