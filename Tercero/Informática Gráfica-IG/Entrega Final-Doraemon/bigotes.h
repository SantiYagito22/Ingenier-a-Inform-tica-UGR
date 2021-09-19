//
// Created by santiago on 3/12/20.
//
#include "malla.h"
#include "objrevolucion.h"
#include "cilindro.h"

#ifndef PRACTICA_1_BIGOTES_H
#define PRACTICA_1_BIGOTES_H
class Bigotes : public Malla3D{
protected:
    Cilindro * bigote=nullptr;
    Material negro;
public:
    Bigotes();

    void draw(int modo,char letra,bool tapa,bool TenemosCono,bool suave,bool plano,bool ra);

    void cambiarAmarillo(bool poneQuita);
};
#endif //PRACTICA_1_BIGOTES_H
