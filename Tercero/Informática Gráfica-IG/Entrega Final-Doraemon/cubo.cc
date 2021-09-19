#include "aux.h"
#include "malla.h"
#include "cubo.h"

Cubo::Cubo(float lado)
{
   // inicializar la tabla de vértices

   Tupla3f v1={-lado,-lado,lado},  v2={lado,-lado,lado}, v3={-lado,-lado,-lado},v4={lado,-lado,-lado},v5={-lado,lado,lado},v6={lado,lado,lado},v7={-lado,lado,-lado},v8={lado,lado,-lado};
   v={v1,v2,v3,v4,v5,v6,v7,v8};

   //inicializar  tabla de colores
   Tupla3f cp1={1,1,0}, cp2={1,1,0}, cp3={1,1,0}, cp4={1,1,0}, cp5={1,1,0}, cp6={1,1,0}, cp7={1,1,0}, cp8={1,1,0};
   cPuntos={cp1,cp2,cp3,cp4,cp5,cp6,cp7,cp8};

   Tupla3f cl1={0,1,0}, cl2={0,1,0}, cl3={0,1,0}, cl4={0,1,0}, cl5={0,1,0}, cl6={0,1,0}, cl7={0,1,0}, cl8={0,1,0};
   cLineas={cl1,cl2,cl3,cl4,cl5,cl6,cl7,cl8};

   Tupla3f cs1={0,0,1},cs2={0,0,1},cs3={0,0,1},cs4={0,0,1},cs5={0,0,1},cs6={0,0,1},cs7={0,0,1},cs8={0,0,1};
   cSolido={cs1,cs2,cs3,cs4,cs5,cs6,cs7,cs8};

    Tupla3f cR1={1,0,0},cR2={1,0,0},cR3={1,0,0},cR4={1,0,0},cR5={1,0,0},cR6={1,0,0},cR7={1,0,0},cR8={1,0,0};
    cPares={cR1,cR2,cR3,cR4,cR5,cR6,cR7,cR8};

    Tupla3f cV1={0,0.5019,0},cV2={0,0.5019,0},cV3={0,0.5019,0},cV4={0,0.5019,0},cV5={0,0.5019,0},cV6={0,0.5019,0},cV7={0,0.5019,0},cV8={0,0.5019,0};
    cImpares={cV1,cV2,cV3,cV4,cV5,cV6,cV7,cV8};



   // inicializar la tabla de caras o triángulos:
   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)


   Tupla3i t1={0,4,6},t2={0,6,2},t3={0,2,3},t4={0,3,1},t5={2,6,7},t6={2,7,3},t7={0,5,4},t8={0,1,5},t9={4,7,6},t10={4,5,7},t11={1,3,7},t12={1,7,5};
   f={t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12};

    calcular_normales();
    calcularCentroObjeto();




}

