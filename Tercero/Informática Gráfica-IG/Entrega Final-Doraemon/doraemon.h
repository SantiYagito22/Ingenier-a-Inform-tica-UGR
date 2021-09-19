//
// Created by santiago on 3/12/20.
//
#include "malla.h"
#include "cabeza.h"
#include "collar.h"
#include "cuerpo.h"
#include "pierna.h"
#include "brazoDch.h"
#include "brazoIzq.h"

#ifndef PRACTICA_1_DORAEMON_H
#define PRACTICA_1_DORAEMON_H
class Doraemon : public Malla3D{
protected:
    Cabeza * cabeza= nullptr;
    Collar * collar= nullptr;
    Cuerpo * cuerpo= nullptr;
    Pierna * pierna= nullptr;
    BrazoDch * brazoDch= nullptr;
    BrazoIzq * brazoIzq= nullptr;
    float giroHelicoptero=0;
    float giroCabeza=0;
    float rotacionBrazo=0;
    float giroCola=0;

    float velocidadCabeza=1,velocidadHelicoptero=1,velocidadBrazo=1,velocidadCola=1;

    bool giraCabeza=true;
    bool saluda=true;
    bool movCola=true;

public:
    Doraemon();

    void draw(int modo,char color,bool tapa,bool TenemosCono,bool suave,bool plano,bool ra);

    void modificarGiroHelicoptero(float valor);

    void modificarGiroCabeza(float valor);

    void modificarGiroBrazo(float valor);

    void modificarGiroCola(float valor);

    void animacionDoraemon(bool cabeza,bool brazos);

    void aumentarVelocidad();

    void disminuirVelocidad();

    void cambiarColoresFalsos(bool volver);

    void cambiarAmarillo(bool poneQuita);
};

#endif //PRACTICA_1_DORAEMON_H
