//
// Created by santiago on 3/12/20.
//
#include "malla.h"
#include "objrevolucion.h"
#include "esfera.h"
#include "semiesfera.h"

#ifndef PRACTICA_1_BOCA_H
#define PRACTICA_1_BOCA_H
class Boca : public Malla3D{
protected:
    SemiEsfera * boca= nullptr;
    Esfera * lengua=nullptr;
    Material rojo,leng;

public:
    Boca();

    void draw(int modo,char letra,bool tapa,bool TenemosCono,bool suave,bool plano,bool ra);

    void cambiarAmarillo(bool poneQuita);
};
#endif //PRACTICA_1_BOCA_H
