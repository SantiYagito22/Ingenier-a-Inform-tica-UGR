#include "doraemon.h"

Doraemon::Doraemon() {

    cabeza=new Cabeza();
    collar=new Collar();
    cuerpo=new Cuerpo();
    pierna=new Pierna();
    brazoDch=new BrazoDch();
    brazoIzq=new BrazoIzq();
}

void Doraemon::modificarGiroHelicoptero(float valor) {
        giroHelicoptero=giroHelicoptero+valor;
}

void Doraemon::modificarGiroCabeza(float valor) {
    if(valor<0 && giroCabeza>-50)
        giroCabeza+=valor;
    else if(valor>0 && giroCabeza<50)
        giroCabeza+=valor;
}

void Doraemon::modificarGiroBrazo(float valor) {
    if(valor<0 && rotacionBrazo>-50)
        rotacionBrazo+=valor;
    else if(valor>0 && rotacionBrazo<50)
        rotacionBrazo+=valor;

}

void Doraemon::modificarGiroCola(float valor) {
    if(valor<0 && giroCola>-30)
        giroCola+=valor;
    else if(valor>0 && giroCola<30)
        giroCola+=valor;

}


void Doraemon::draw(int modo,char color,bool tapa,bool TenemosCono,bool suave,bool plano,bool ra) {

    glPushMatrix();
    glTranslatef(0.0,3.5*25,0.0);
    glRotatef(giroCabeza, 0.0, 1.0, 0.0); //Movimiento cabeza[-50,50]
    cabeza->draw(giroHelicoptero,modo,color,tapa,TenemosCono,suave,plano,ra);
    glPopMatrix();


    collar->draw(modo,color,tapa,TenemosCono,suave,plano,ra);



    glPushMatrix();
    glTranslatef(0.0,-5.0*25,0.0);
    cuerpo->draw(giroCola,modo,color,tapa,TenemosCono,suave,plano,ra);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(1.25*25,-7.0*25,0.75*25);
    pierna->draw(modo,color,tapa,TenemosCono,suave,plano,ra);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.25*25,-7.0*25,0.75*25);
    pierna->draw(modo,color,tapa,TenemosCono,suave,plano,ra);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(2*25,-1.5*25,0.0);
    brazoDch->draw(rotacionBrazo,modo,color,tapa,TenemosCono,suave,plano,ra);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-2*25,-1.5*25,0.0);
    brazoIzq->draw(rotacionBrazo,modo,color,tapa,TenemosCono,suave,plano,ra);
    glPopMatrix();


}

void Doraemon::animacionDoraemon(bool cabeza,bool brazos) {

    if(cabeza)
    {
        if(giroCabeza>=50)
            giraCabeza = false;

        if(giroCabeza<=-50)
            giraCabeza=true;

        if(giraCabeza)
            modificarGiroCabeza(velocidadCabeza*1.0);
        else
            modificarGiroCabeza(velocidadCabeza*-1.0);
    }
    else
        giroCabeza=0;



   modificarGiroHelicoptero(velocidadHelicoptero*25.0);

   if(brazos)
   {
       if(rotacionBrazo>=50)
           saluda=false;
       if(rotacionBrazo<=-50)
           saluda=true;

       if(saluda)
           modificarGiroBrazo(velocidadBrazo*2.5);
       else
           modificarGiroBrazo(velocidadBrazo*-2.5);
   }
   else
       rotacionBrazo=-50;



   if(giroCola>=30)
       movCola=false;
   if(giroCola<=-30)
       movCola=true;

    if(movCola)
        modificarGiroCola(velocidadCola*1.0);
    else
        modificarGiroCola(velocidadCola*-1.0);


}

void Doraemon::disminuirVelocidad() {
    if((velocidadCabeza-1)>=1 )
        velocidadCabeza-=1;
    else if((velocidadCabeza-0.2)>=0 && velocidadCabeza<=1)
        velocidadCabeza-=0.2;
        else
             printf("Velocidad de la cabeza no disminuye  mas\n");

    if((velocidadHelicoptero-0.72)>=0)
       velocidadHelicoptero-=0.72;
    else if((velocidadHelicoptero-0.72)<=0)
        velocidadHelicoptero=0;

    if(velocidadHelicoptero==0)
        printf("Velocidad  del gorrocoptero no disminuye  mas\n");

    if((velocidadCola-1)>=1)
        velocidadCola-=1;
    else if((velocidadCola-0.2)>=0 && velocidadCola<=1)
        velocidadCola-=0.2;
    if(velocidadCola==0)
        printf("Velocidad de la cola no disminuye  mas\n");

    if((velocidadBrazo-2)>=2)
        velocidadBrazo-=2;
    else if((velocidadBrazo-0.25)>=0 && velocidadBrazo<=2)
        velocidadBrazo-=0.25;
    if(velocidadBrazo==0)
        printf("Velocidad de los brazos no disminuye  mas\n");
}

void Doraemon::aumentarVelocidad() {
    if((velocidadCabeza+1)<=10)
        velocidadCabeza+=1;
    else
        printf("Velocidad de la cabeza no aumenta mas\n");
    if((velocidadHelicoptero+0.72)<=3.6)
    {
        velocidadHelicoptero+=0.72;
    }
    else
        printf("Velocidad del gorrocoptero no aumenta mas\n");

    if((velocidadCola+1)<=10)
        velocidadCola+=1;
    else
        printf("Velocidad de la cola no aumenta mas\n");

    if((velocidadBrazo+2)<=25)
        velocidadBrazo+=2;
    else
        printf("Velocidad brazo no aumenta mas\n");

}

void Doraemon::cambiarAmarillo(bool poneQuita) {

    cabeza->cambiarAmarillo(poneQuita);
    collar->cambiarAmarillo(poneQuita);
    cuerpo->cambiarAmarillo(poneQuita);
    pierna->cambiarAmarillo(poneQuita);
    brazoDch->cambiarAmarillo(poneQuita);
    brazoIzq->cambiarAmarillo(poneQuita);
}

