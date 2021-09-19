const MAXIMO= 255;


struct operandoBasico{
    double a;
    double b;
};


struct Num {
    double numeros<>;
};

struct Ope {
    char operandos<>;
};

struct vec {
    double v<>;
};



program CALCULADORA{
    version CV1 {
        double SUMAR (operandoBasico) = 1;
        double RESTAR (operandoBasico) = 2;
        calculadora_res DIVISION (operandoBasico) = 3;
        double MULTIPLICAR (operandoBasico) = 4 ; 
    } =1;

    version CV2 {
        double Combinada(Num,Ope) = 5 ;
    } =2;

    version CV3 {
        vec SUMAVECTOR(vec,vec) = 6;
        vec RESTAVECTOR(vec,vec) = 7;
        vec MULTIPLICARVECTOR(vec,vec) = 8;
        vec DIVIDIRVECTOR(vec,vec) = 9;
        double ESCALAR(vec,vec) = 10;
    } = 3;


    version CV4 {
        vec ECUACIONCUADRATICA(double,double,double) = 11 ;
    } = 4 ;
} =0x20000011;
