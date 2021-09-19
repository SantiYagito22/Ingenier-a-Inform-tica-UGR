#include"parteTecnico.h"


parteTecnico::parteTecnico(int nt,int act,bool rc)
{
    this->notaTrabajo=nt;
    this->actitud=act;
    this->recomendacion=rc;
}


void parteTecnico::rellenarParteTecnico()
{   
    cout<<"\nVamos a rellenar el Parte del Tecnico"<<endl<<endl;
    int nT;
    do{
    cout<<"Introduzca una nota del trabajo efectuado por el tecnico(0-10):"<<endl;
    cin>>nT;
    }while(nT<0 || nT>10);
    
    int act;
    do{
    cout<<"Introduzca la actitud que ha tenido el tecnico(0-10):"<<endl;
    cin>>act;
    }while(act<0 || act>10); 
    
    string resp;
    string si="si";
    string Si="Si";
    string no="no";
    string No="No";
    bool rec;
    do{
    cout<<"¿Recomiendas al técnico?(Si o No):"<<endl;
    cin>>resp;
    }while(resp.compare(si) && resp.compare(Si) && resp.compare(no) && resp.compare(No));

    
    if(resp=="si" || resp=="Si")
    {
        
        rec=true;
    }
    else
    {
        rec=false;
    }

    
    this->notaTrabajo=nT;
    this->actitud=act;
    this->recomendacion=rec;
    
}

