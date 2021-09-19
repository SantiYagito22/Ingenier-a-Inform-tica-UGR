#include "luzposicional.h"
#include <stdlib.h>
LuzPosicional::LuzPosicional(Tupla3f posicion, GLenum idLuzOpenGL, Tupla4f Ambiente, Tupla4f Especular, Tupla4f Difuso) {

    this->posicion={posicion(X),posicion(Y),posicion(Z),1.0};
    id=idLuzOpenGL;
    this->colorAmbiente=Ambiente;
    this->colorEspecular=Especular;
    this->colorDifuso=Difuso;
}

void LuzPosicional::animarLuz() {

    if(!cambia)
    {
        posicion={posicion(X)+1,posicion(Y),posicion(Z),1.0};
        movimientoLuz++;
    }
    if(cambia)
    {
        posicion={posicion(X)-1,posicion(Y),posicion(Z),1.0};
        movimientoLuz--;
    }
    if(movimientoLuz==300)
        cambia=true;
    if(movimientoLuz==-300)
        cambia=false;

}