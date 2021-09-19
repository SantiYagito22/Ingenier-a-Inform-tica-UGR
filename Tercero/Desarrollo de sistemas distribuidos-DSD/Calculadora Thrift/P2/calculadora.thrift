struct operacionBasica{
1: double a =0 ,
2: double b =0,
}

struct operacionVectores{
1: list<double> v1
2: list<double> v2
}

exception operacionInvalida {
1: string tipo
2: string why
}

struct segundoGrado{
1: double a
2: double b
3: double c
}

struct combinada{
1: list<double> nums
2: list<string> op

}

service Calculator{
double suma(1:operacionBasica oB),
double resta(1:operacionBasica oB),
double multiplicacion(1:operacionBasica oB),
double division(1:operacionBasica oB) throws (1:operacionInvalida oI),
list<double> sumaVectores(1:operacionVectores oV) throws (1:operacionInvalida oI),
list<double> restaVectores(1:operacionVectores oV) throws (1:operacionInvalida oI),
list<double> multiplicacionVectores(1:operacionVectores oV) throws (1:operacionInvalida oI),
list<double> divisionVectores(1:operacionVectores oV) throws (1:operacionInvalida oI),
list<double> ecuacionCuadratica(1:segundoGrado sg) throws (1:operacionInvalida oI),
double operacionCombinada(1:combinada cb) throws (1:operacionInvalida oI),
}
