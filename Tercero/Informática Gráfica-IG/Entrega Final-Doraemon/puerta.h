//
// Created by santiago on 12/1/21.
//
#include "malla.h"
#include "cubo.h"
#include "cilindro.h"

#ifndef PLANTILLA_PRACTICASA_PUERTA_H
#define PLANTILLA_PRACTICASA_PUERTA_H
class Puerta : public Malla3D
{
protected:
    Cubo * puerta= nullptr;
    Cilindro * pomo= nullptr;
    Material rosa,gris;

public:
    Puerta();

    void draw(int modo,char color,bool tapa,bool TenemosCono,bool suave,bool plano,bool ra);

    void cambiarAmarillo(bool poneQuita);
};

#endif //PLANTILLA_PRACTICASA_PUERTA_H
