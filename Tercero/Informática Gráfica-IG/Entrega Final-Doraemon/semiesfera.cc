#include "semiesfera.h"

SemiEsfera::SemiEsfera(const int num_vert_perfil, const int num_instancias_perfil, const float radio, char rotacion,bool text) {
    std::vector <Tupla3f> perfilOriginal;

    for (int i = 1; i < num_vert_perfil / 2; i++) {

        perfilOriginal.push_back(Tupla3f{radio * cos(((PI * i) / num_vert_perfil) + 3 * PI / 2),
                                         radio * sin(((PI * i) / num_vert_perfil) + 3 * PI / 2), 0.0});
        //std::cout<<perfilOriginal.at(i)(X)<<" "<<perfilOriginal.at(i)(Y)<<" " <<perfilOriginal.at(i)(Z)<<std::endl;
    }

    bool tieneTapas = false;
    for (int i = 0; i < perfilOriginal.size(); i++) {
        if (rotacion == 'Y' && (fabs(perfilOriginal.at(0)(X)) < std::numeric_limits<float>::epsilon() &&
                                fabs(perfilOriginal.at(0)(Z)) < std::numeric_limits<float>::epsilon()))
            tieneTapas = true;
        else if (rotacion == 'X' && (fabs(perfilOriginal.at(0)(Y)) < std::numeric_limits<float>::epsilon() &&
                                     fabs(perfilOriginal.at(0)(Z)) < std::numeric_limits<float>::epsilon()))
            tieneTapas = true;
        else if (rotacion == 'Z' && (fabs(perfilOriginal.at(0)(X)) < std::numeric_limits<float>::epsilon() &&
                                     fabs(perfilOriginal.at(0)(Y)) < std::numeric_limits<float>::epsilon()))
            tieneTapas = true;
    }


    crearMalla(perfilOriginal, num_instancias_perfil, tieneTapas, rotacion,text);
    calcular_normales();
}

