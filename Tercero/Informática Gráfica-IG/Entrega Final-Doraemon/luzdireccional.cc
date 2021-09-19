#include "luzdireccional.h"

LuzDireccional::LuzDireccional(Tupla2f direccion, GLenum idLuzOpenGL, Tupla4f Ambiente, Tupla4f Especular,Tupla4f Difuso) {

    alpha=direccion(X)*M_PI/180;
    beta=direccion(Y)*M_PI/180;
    this->posicion={sin(alpha)*cos(beta),sin(alpha)*sin(beta),cos(alpha),0.0};
    id=idLuzOpenGL;
    colorAmbiente=Ambiente;
    colorEspecular=Especular;
    colorDifuso=Difuso;
}

void LuzDireccional::variarAnguloAlpha(float incremento) {
    alpha+=incremento*(M_PI/180);

    if(alpha >2*M_PI)
    {
        alpha-=360;
    }
    if(alpha <-(2*M_PI))
    {
        alpha+=360;
    }


    posicion(X)=sin(alpha)*cos(beta);
    posicion(Y)=sin(alpha)*sin(beta);
    posicion(Z)=cos(alpha);

}

void LuzDireccional::variarAnguloBeta(float incremento) {
    beta+=incremento*(M_PI/180);

    if(beta >2*M_PI)
    {
        beta-=360;
    }
    if(beta <-(2*M_PI))
    {
        beta+=360;
    }

    posicion(X)=sin(alpha)*cos(beta);
    posicion(Y)=sin(alpha)*sin(beta);
    posicion(Z)=cos(alpha);
}
