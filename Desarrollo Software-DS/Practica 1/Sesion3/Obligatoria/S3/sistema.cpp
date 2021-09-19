
#include<cliente.h>
#include"tecnico.h"
#include"trabajo.h"
#include<vector>
#include<stdlib.h>
#include<time.h>
using namespace std;

int main()
{

vector<Trabajo *> trabajosSistema;
int cont=0;

Tecnico * t1=new Tecnico("Santi",29);

Cliente * c1=new Cliente("Fran",20);

trabajosSistema.push_back(c1->crearTrabajo(100,"Arreglar lavajillas",cont));
cont++;
trabajosSistema.push_back(c1->crearTrabajo(300, "Obra", cont));
cont++;
trabajosSistema.push_back(c1->crearTrabajo(500, "Reparación cocina",cont));
cont++;

srand(time(NULL));
int num;

num = rand()%trabajosSistema.size();

t1->cogerTrabajo(num,trabajosSistema);

t1->realizarTrabajo();

c1->pagar(t1);



}