//
// Created by santiago on 23/12/20.
//
#include "aux.h"

#ifndef PRACTICA_1_CAMARA_H
#define PRACTICA_1_CAMARA_H
class Camara{
private:
  Tupla3f eye;
  Tupla3f at;
  Tupla3f up;

  int tipo;



public:
    float left,right,near,far,top,bottom;

  Camara(Tupla3f e,Tupla3f a,Tupla3f u,int tip,float lft, float rgt , float nr , float fr,float tp,float bt);

  void rotarXExaminar(float  angle);
  void rotarYExaminar(float  angle);
  void rotarZExaminar(float  angle);

  void rotarXFirstPerson(float angle);
  void rotarYFirstPerson(float angle);
  void rotarZFirstPerson(float angle);

  void mover(float x,float y,float z);


  void zoom(float factor, float lft,float rgt,float tp, float bt);

  void setObserver();

  void setProyeccion();

  void setAt(Tupla3f aux_at);
};
#endif //PRACTICA_1_CAMARA_H
