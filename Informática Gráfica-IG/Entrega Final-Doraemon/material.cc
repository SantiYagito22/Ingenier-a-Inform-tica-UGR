#include "material.h"

Material::Material(Tupla4f mdifuso, Tupla4f mespecular, Tupla4f mambiente, float brillo) {
    this->difuso=mdifuso;
    this->especular=mespecular;
    this->ambiente=mambiente;
    this->brillo=brillo;
}

Material::Material() {
}

void Material::aplicar() {
    glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT, ambiente);
    glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE, difuso ) ;
    glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, especular );
    glMaterialf( GL_FRONT_AND_BACK, GL_SHININESS, brillo );
}

void Material::setMaterial(Material mat) {
    this->difuso=mat.difuso;
    this->especular=mat.especular;
    this->ambiente=mat.ambiente;
    this->brillo=mat.brillo;
}

