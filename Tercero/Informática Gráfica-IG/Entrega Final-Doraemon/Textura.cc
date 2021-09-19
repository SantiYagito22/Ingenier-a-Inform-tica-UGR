#include "Textura.h"


Textura::Textura(std::string archivo) {
   jpg::Imagen * pimg=NULL;

   pimg=new jpg::Imagen(archivo);
   width=pimg->tamX(); //num columnas (unsigned)
   height=pimg->tamY(); //num filas(unsigned)

    unsigned char* aux;
    for(int i=0; i<height;i++)
    {
        for(int j=0;j<width;j++)
        {

            aux=pimg->leerPixel(j,height-1-i);
            data.push_back(*(aux));
            data.push_back(*(aux+1));
            data.push_back(*(aux+2));


        }
    }

}

void Textura::activar() {
    glEnable(GL_TEXTURE_2D);
    if (textura_id == 0) {
        glGenTextures(1, & textura_id);
        glBindTexture(GL_TEXTURE_2D, textura_id);
        //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        gluBuild2DMipmaps(GL_TEXTURE_2D,GL_RGB, width, height,GL_RGB, GL_UNSIGNED_BYTE, data.data());
    }

    glBindTexture(GL_TEXTURE_2D, textura_id);

    //glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    //glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SINGLE_COLOR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);



}