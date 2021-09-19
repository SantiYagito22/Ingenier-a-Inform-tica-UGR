#include "cilindro.h"

Cilindro::Cilindro(const int num_vert_perfil, const int num_instancias_perf, const float altura, const float radio,const char rotacion,bool text) {
    std::vector<Tupla3f> perfilOriginal;


    if(rotacion=='Y')
    {
        for(int i=0; i<=num_vert_perfil;i++)
        {
            perfilOriginal.push_back(Tupla3f{radio,i*altura/num_vert_perfil,0.0});
            //std::cout<<perfilOriginal.at(i)(X)<<" "<<perfilOriginal.at(i)(Y)<<" " <<perfilOriginal.at(i)(Z)<<std::endl;
        }
    }
    else if (rotacion=='X')
    {

        for(int i=1; i<=num_vert_perfil+1;i++)
        {
            perfilOriginal.push_back(Tupla3f{i*radio/num_vert_perfil,altura,0.0});
            //std::cout<<perfilOriginal.at(i)(X)<<" "<<perfilOriginal.at(i)(Y)<<" " <<perfilOriginal.at(i)(Z)<<std::endl;
        }
    }
    else if(rotacion=='Z')
    {
        for(int i=1; i<=num_vert_perfil+1;i++)
        {
            perfilOriginal.push_back(Tupla3f{0.0,altura,i*radio/num_vert_perfil});
            //std::cout<<perfilOriginal.at(i)(X)<<" "<<perfilOriginal.at(i)(Y)<<" " <<perfilOriginal.at(i)(Z)<<std::endl;
        }
    }

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
