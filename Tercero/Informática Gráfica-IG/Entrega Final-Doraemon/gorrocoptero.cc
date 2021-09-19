#include "gorrocoptero.h"

Gorrocoptero::Gorrocoptero() {
    gorro=new SemiEsfera(20,40,25,'Y',false);
    gorroBola=new Esfera(20,40,5,'Y',false);
    gorroPalo=new Cilindro(2,50,25,50,'Y',false);
    helices=new Cubo(50.0);
    oro=Material({0.75164,0.60648,0.22648,0.5},{0.628281,0.555802,0.366065,0.5},{0.24725,0.1995,0.0745,0.5},0.4);

    gorroPalo->inicializarColores();
    gorro->inicializarColores();
    gorroBola->inicializarColores();
    helices->inicializarColores();

    gorro->cambiarColores({229.0/255.0,173.0/255.0,4.0/255.0}) ;
    gorroBola->cambiarColores({229.0/255.0,173.0/255.0,4.0/255.0});
    gorroPalo->cambiarColores({229.0/255.0,173.0/255.0,4.0/255.0});
    helices->cambiarColores({229.0/255.0,173.0/255.0,4.0/255.0});

    gorro->setMaterial(oro);
    gorroBola->setMaterial(oro);
    gorroPalo->setMaterial(oro);
    helices->setMaterial(oro);

    gorro->setColorFalso({0.0,1.0,0.0});
    gorroBola->setColorFalso({0.0,1.0,0.0});
    gorroPalo->setColorFalso({0.0,1.0,0.0});
    helices->setColorFalso({0.0,1.0,0.0});

    gorro->setColorAux({229.0/255.0,173.0/255.0,4.0/255.0});
    gorroBola->setColorAux({229.0/255.0,173.0/255.0,4.0/255.0});
    gorroPalo->setColorAux({229.0/255.0,173.0/255.0,4.0/255.0});
    helices->setColorAux({229.0/255.0,173.0/255.0,4.0/255.0});

    gorro->setMaterialAux(oro);
    gorroBola->setMaterialAux(oro);
    gorroPalo->setMaterialAux(oro);
    helices->setMaterialAux(oro);


}


void Gorrocoptero::draw(float giro,int modo,char color,bool tapa,bool TenemosCono,bool suave,bool plano,bool ra) {
    glPushMatrix();
    glTranslatef(0.0,-1.8*25,0.0);
    glRotatef(180.0,1.0,0.0,0.0);
    glScalef(0.5,0.5,0.5);
    gorro->drawObj(modo,color,tapa,false,suave,plano,ra);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0,-1.6*25,0.0);
    glScalef(0.1,1.5,0.1);
    gorroPalo->drawObj(modo,color,tapa,false,suave,plano,ra);
    glPopMatrix();


    glPushMatrix();

    glRotatef(giro,0.0,1.0,0.0); //movimiento helice[-360,360]
    gorroBola->drawObj(modo,color,tapa,false,suave,plano,ra);


    glPushMatrix();
    glRotatef(90.0,1.0,0.0,0.0);
    glScalef(0.05,0.8,0.02);
    helices->draw(modo,color,suave,plano,ra);
    glPopMatrix();


    glPopMatrix();
}

void Gorrocoptero::cambiarAmarillo(bool poneQuita) {
    gorro->cambiarAmarillo(poneQuita);
    gorroPalo->cambiarAmarillo(poneQuita);
    gorroBola->cambiarAmarillo(poneQuita);
    helices->cambiarAmarillo(poneQuita);
}