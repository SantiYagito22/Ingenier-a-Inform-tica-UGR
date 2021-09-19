//
// Created by santiago on 22/11/20.
//
#include "aux.h"

#ifndef PRACTICA_1_MATERIAL_H
#define PRACTICA_1_MATERIAL_H
class Material {
private:
    Tupla4f difuso;
    Tupla4f especular;
    Tupla4f ambiente;
    float brillo;

public:

    Material();

    Material(Tupla4f mdifuso,Tupla4f mespecular,Tupla4f mambiente,float brillo);

    void aplicar();

    void setMaterial(Material mat);
};
#endif //PRACTICA_1_MATERIAL_H
