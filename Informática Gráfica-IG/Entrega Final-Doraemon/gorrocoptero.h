//
// Created by santiago on 3/12/20.
//
#include "malla.h"
#include "objrevolucion.h"
#include "semiesfera.h"
#include "cubo.h"
#include "cilindro.h"
#include "esfera.h"

#ifndef PRACTICA_1_GORROCOPTERO_H
#define PRACTICA_1_GORROCOPTERO_H

class Gorrocoptero : public Malla3D{
protected:
    SemiEsfera * gorro= nullptr;
    Cubo * helices = nullptr ;
    Esfera * gorroBola=nullptr;
    Cilindro * gorroPalo=nullptr;
    Material oro;

public:
    Gorrocoptero();

    void draw(float giro,int modo,char color,bool tapa,bool TenemosCono,bool suave,bool plano,bool ra);

    void cambiarAmarillo(bool poneQuita);
};
#endif //PRACTICA_1_GORROCOPTERO_H
