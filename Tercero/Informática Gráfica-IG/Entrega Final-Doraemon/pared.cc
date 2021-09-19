#include "pared.h"

Pared::Pared(float l) {

    Tupla3f v1={-l,-l,0},v2={-l,l,0},v3={l,-l,0},v4={l,l,0};
    v={v1,v2,v3,v4};

    Tupla3i f1={0,2,1},f2={1,2,3};
    f={f1,f2};


    calcular_normales();



    ct.resize(v.size());
    ct[0]={0,0};
    ct[1]={0,1};
    ct[2]={1,0};
    ct[3]={1,1};



}