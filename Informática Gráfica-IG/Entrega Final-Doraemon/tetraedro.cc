#include "aux.h"
#include "malla.h"
#include "tetraedro.h"

Tetraedro::Tetraedro()
{

   //inicializar la tabla de vértices



Tupla3f v1 ={0,-11.410875,-lado};//Vertice 1
Tupla3f v2 ={0.0,45.6435,0.0}; //Vertice 2
Tupla3f v3 ={lado,-11.410875,lado}; //Vertice 3
Tupla3f v4 ={-lado,-11.410875,lado}; //Vertice 4

v.push_back(v1);
v.push_back(v2);
v.push_back(v3);
v.push_back(v4);


Tupla3f cp1={1,0,1},cp2={1,0,1},cp3={1,0,1},cp4={1,0,1};
cPuntos={cp1,cp2,cp3,cp4};



Tupla3f cl1={0,0,0},cl2={0,0,0},cl3={0,0,0},cl4={0,0,0};
cLineas={cl1,cl2,cl3,cl4};

Tupla3f cs1={0.75,0.75,0.75},cs2={0.75,0.75,0.75},cs3={0.75,0.75,0.75},cs4={0.75,0.75,0.75};
cSolido={cs1,cs2,cs3,cs4};

Tupla3f cR1={1,0,0},cR2={1,0,0},cR3={1,0,0},cR4={1,0,0};
cPares={cR1,cR2,cR3,cR4};

Tupla3f cV1={0,0.5019,0},cV2={0,0.5019,0},cV3={0,0.5019,0},cV4={0,0.5019,0};
cImpares={cV1,cV2,cV3,cV4};



   // inicializar la tabla de caras o triángulos:
   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)

   Tupla3i t1={3,2,1};
   Tupla3i t2={2,0,1};
   Tupla3i t3={3,1,0};
   Tupla3i t4={3,0,2};

   f.push_back(t1);
   f.push_back(t2);
   f.push_back(t3);
   f.push_back(t4);


    calcular_normales();
    calcularCentroObjeto();

}





