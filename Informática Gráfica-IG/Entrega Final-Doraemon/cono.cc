#include "cono.h"


Cono::Cono(const int num_vert_perfil, const int num_instancias_perf, const float altura, const float radio,char rotacion,bool text) {


    std::vector<Tupla3f> perfilOriginal;

    int j=0.1;
    for(int i=num_vert_perfil; i>=0 ; i-- )
    {
        perfilOriginal.push_back(Tupla3f{radio*i/num_vert_perfil+0.01,altura*j/num_vert_perfil,0.0});
        j++;
    }
    /*
    for(int j=0; j<=num_vert_perfil;j++)
    {
        std::cout<<perfilOriginal.at(j)(X)<<" "<<perfilOriginal.at(j)(Y)<<" " <<perfilOriginal.at(j)(Z)<<std::endl;
    }
    */

    bool tieneTapas=false;
    for(int i=0; i<perfilOriginal.size();i++)
    {
        if(rotacion=='Y' && (fabs(perfilOriginal.at(0)(X))< std::numeric_limits<float>::epsilon() && fabs(perfilOriginal.at(0)(Z))< std::numeric_limits<float>::epsilon()))
            tieneTapas=true;
        else if(rotacion=='X' && (fabs(perfilOriginal.at(0)(Y))< std::numeric_limits<float>::epsilon() && fabs(perfilOriginal.at(0)(Z))< std::numeric_limits<float>::epsilon()))
            tieneTapas=true;
        else if(rotacion=='Z' && (fabs(perfilOriginal.at(0)(X))< std::numeric_limits<float>::epsilon() && fabs(perfilOriginal.at(0)(Y))< std::numeric_limits<float>::epsilon()))
            tieneTapas=true;
    }


    crearMalla(perfilOriginal,num_instancias_perf,tieneTapas,rotacion,text);
    calcular_normales();


}