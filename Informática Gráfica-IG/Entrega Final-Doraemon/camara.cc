#include "camara.h"

Camara::Camara(Tupla3f e, Tupla3f a, Tupla3f u, int tip, float lft, float rgt, float nr, float fr,float tp,float bt) {
    eye=e;
    at=a;
    up=u;
    tipo=tip;
    left=lft;
    right=rgt;
    near=nr;
    far=fr;
    top=tp;
    bottom=bt;
}

void Camara::rotarXFirstPerson(float angle) {
    at(X)=at(X)+angle;
}

void Camara::rotarYFirstPerson(float angle) {
    at(Y)=at(Y)+angle;
}

void Camara::rotarZFirstPerson(float angle) {
    at(Z)=at(Z)+angle;
}

void Camara::setObserver() {
    gluLookAt(eye(X),eye(Y),eye(Z),at(X),at(Y),at(Z),up(X),up(Y),up(Z));
}

void Camara::setProyeccion() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if(tipo==0)
        glFrustum(left,right,bottom,top,near,far);
    else
        glOrtho(left,right,bottom,top,near,far);
}

void Camara::zoom(float factor, float lft,float rgt,float tp, float bt) {
    left=lft*factor;
    right=rgt*factor;
    top=tp*factor;
    bottom=bt*factor;
    setProyeccion();
}

void Camara::rotarXExaminar(float angle) {
    eye=eye-at;
    Tupla3f vistaOriginal=eye;
    eye(Y)=vistaOriginal(Y)*cosf(angle)-vistaOriginal(Z)*sinf(angle);
    eye(Z)=vistaOriginal(Y)*sinf(angle)+vistaOriginal(Z)*cosf(angle);
    eye=eye+at;
}



void Camara::rotarYExaminar(float angle) {
    eye=eye-at;
    Tupla3f vistaOriginal=eye;
    eye(X)=vistaOriginal(X)*cosf(angle)+vistaOriginal(Z)*sinf(angle);
    eye(Z)=vistaOriginal(X)*-1*sinf(angle)+vistaOriginal(Z)*cosf(angle);
    eye=eye+at;
}

void Camara::rotarZExaminar(float angle) {
    eye=eye-at;
    Tupla3f vistaOriginal=eye;
    eye(X)=vistaOriginal(X)*cosf(angle)-vistaOriginal(Z)*sinf(angle);
    eye(Y)=vistaOriginal(X)*sinf(angle)+vistaOriginal(Z)*cosf(angle);
    eye=eye+at;
}

void Camara::setAt(Tupla3f aux_at) {

    at=aux_at;
}