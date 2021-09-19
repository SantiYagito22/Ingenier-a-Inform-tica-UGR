#include"parteTrabajo.h"
using namespace std;

parteTrabajo::parteTrabajo(float df,float h, float gm, float gt){
    this->dificultad=df;
    this->horas=h;
    this->gastosMateriales=gm;
    this->gastosTransporte=gt;
}

void parteTrabajo::rellenarParteTrabajo(){
    cout<<"\nVamos a rellenar el Parte del Trabajo"<<endl<<endl;
    float dif;
    do{
    cout<<"Introduzca la dificultad del trabajo(0-10):"<<endl;
    cin>>dif;
    }while(dif<0 || dif>10);

    float h;
    do{
    cout<<"Introduzca cuantas horas ha durado la reparación(No acepta negativo):"<<endl;
    cin>>h;
    }while(h<0 );

    float gM;
    do{
    cout<<"Introduzca los gastos materiales(No acepta negativo): "<<endl;
    cin>>gM;
    }while(gM<0 );

    float gt;
    do{
    cout<<"Introduzca los gastos de transporte (No acepta negativo): "<<endl;
    cin>>gt;
    }while(gt<0);


    this->dificultad=dif;
    this->horas=h;
    this->gastosMateriales=gM;
    this->gastosTransporte=gt;
}

