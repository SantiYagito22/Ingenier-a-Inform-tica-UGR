#include "luz.h"

void Luz::activar() {

    glLightfv( id, GL_AMBIENT, this->colorAmbiente);
    glLightfv( id, GL_DIFFUSE, this->colorDifuso );
    glLightfv( id, GL_SPECULAR, this->colorEspecular );
    glLightfv( id, GL_POSITION, this->posicion );

    glEnable(id);

}

void Luz::desactivar()
{
    glDisable(id);
}