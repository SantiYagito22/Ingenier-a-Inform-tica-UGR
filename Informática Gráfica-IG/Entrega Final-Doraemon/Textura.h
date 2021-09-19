//
// Created by santiago on 14/12/20.
//

#include "aux.h"
#include "jpg_imagen.hpp"

#ifndef PRACTICA_1_TEXTURA_H
#define PRACTICA_1_TEXTURA_H
class Textura {
    GLuint textura_id=0;
    std::vector<unsigned char> data;
    int width,height;


public:

    Textura(std::string archivo);
    void activar();

};
#endif //PRACTICA_1_TEXTURA_H
