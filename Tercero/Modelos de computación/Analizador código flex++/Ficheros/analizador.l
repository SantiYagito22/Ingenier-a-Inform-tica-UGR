/*Para compilar y ejecutar
1-flex++ analizador.l 
2-g++ lex.yy.cc -o prog 
3-./prog escena.cc */

/*-Seccion de Declaraciones-*/

%option noyywrap

%{

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

ifstream fichero;
vector<int> operaciones; /*[0]->suma [1]->resta [2]->multiplicaciones [3]->divisiones [4]->modulos [5]->comparacion [6]->condicion [7]->Bucles [8]->Funciones*/
void escribir_datos (vector<int> datos); /*Función para mostrar los datos obtenidos por el terminal*/
%}
/*Aqui definiremos las macros para definir todas las operaciones que vamos a contabilizar*/
SUMA    "+"|"++"|"+="        
RESTA   "-"|"--"|"-="
MULTIPLICACION  "*"|"*="
DIVISION    "/"|"/="
CONDICIONAL "if"|"switch"
BUCLE   "for"|"while"  
COMPARACION "<"|">"|"=="|"!="|"<="|">="

/*Tambien tenemos macros definidas para las posibles variables del codigo, los tipos para los cast y los cierres de parentesis y corchetes*/
VARIABLE   [A-Za-z0-9"_""."]
TIPO   "float"|"int"|"double"|"char"|"bool"|"string"|"long"
CIERRES     ")"|"]"

%x comment


%%
    /*-Seccion de Reglas-*/

"//"(.*)                        /*---En estas 2 líneas quitamos los comentarios tanto con "//" como con "/*"---*/
"/*"    BEGIN(comment);         /*---Para quitar los comentarios que empiezan con '/*' hemos tenido que usar start conditions---*/
<comment>[^*]*   
<comment>"*"+[^*/]*      
<comment>"*"+"/"    BEGIN(INITIAL);  

\".*\"                      /*Con esta regla hemos omitido todos las frases entre comillas del codigo, como pueden ser rutas o frases para la salida por terminal*/

{VARIABLE}+{CIERRES}*" "*{SUMA}" "*{VARIABLE}+|{VARIABLE}+{SUMA}         {operaciones[0]++;}    /*Con esta regla omitimos todas las sumas definidas en el macro SUMA y sumamos en uno al contador de suma*/
{VARIABLE}+{CIERRES}*" "*{RESTA}" "*{VARIABLE}+|{VARIABLE}+{RESTA}[^">"]    {operaciones[1]++;} /*Con esta regla omitimos todas las restas definidas en el macro RESTA y sumamos en uno al contador de resta*/
{VARIABLE}+{CIERRES}*" "*{MULTIPLICACION}" "*[-]*{VARIABLE}+     {operaciones[2]++;}     /*Con esta regla omitimos todas las multiplicacion definidas en el macro MULTIPLICACION y sumamos en uno al contador de multiplicador*/
{VARIABLE}+{CIERRES}*" "*{DIVISION}" "*[-]*{VARIABLE}+    {operaciones[3]++;} /*Con esta regla omitimos todas las divisiones definidas en el macro DIVISION y sumamos en uno al contador de division*/
{VARIABLE}+{CIERRES}*" "*"%"" "*{VARIABLE}+      {operaciones[4]++;}    /*Con esta regla omitimos todos los modulos  definidos como % y sumamos en uno al contador de modulo*/
{VARIABLE}+{CIERRES}*" "*{COMPARACION}" "*[-]*{VARIABLE}+    {operaciones[5]++;} /*Con esta regla omitimos todas las comparaciones  definidas en el macro COMPARACION y sumamos en uno al contador de comparaciones*/
{CONDICIONAL}" "*"("   {operaciones[6]++;}  /*Con esta regla omitimos todas las condiciones definidas en el macro CONDICIONAL y sumamos en uno al contador de condiciones*/
{BUCLE}" "*"("    {operaciones[7]++;}   /*Con esta regla omitimos todos bucles definidos en el macro BUCLE y sumamos en uno al contador de bucles*/
"::"{VARIABLE}+"("  /*Con esta regla omitimos todas las declaraciones de metodos*/
{TIPO}" "*"("   /*Con esta regla omitimos todos los tipos de datos definidos en el macro TIPO, para evitar problemas con casteos*/
("."|"->")*{VARIABLE}+"("    {operaciones[8]++;} /*Con esta regla omitimos todas las llamadas a funciones, recononiendolas al encontrar un . o -> seguido de cualquier palabra perteneciente al macro VARIABLE y sumamos en uno al contador de llamadas a funciones */

[^ \n\t]   /*Con estas dos reglas omitiremos todo lo restante que haya quedado en el codigo*/
[ \n\t]   


%%
    /*-Seccion Procedimientos del Usuario-*/

/*En el main, primero tendremos una seccion de abrir el archivo para ver si falla o no.
    Una vez que este correcto, inicializamos el vector de operaciones a 0 
    Y ya despues utilizamos yyFlexLexer para el fichero, usamos en ese flujo la funcion yylex() para realizar el proceso y terminamos escribiendo los datos, pasandole el vector*/
int main(int argc, char *argv[])
{
    
    if (argc == 2){
        fichero.open(argv[1]);
        if (!fichero.is_open()){
            cout<<"Error de lectura"<<endl;
            exit(1);
        }
    }
    else{
        exit(1);
    }
    
    operaciones.resize(9);
    for(int i=0; i<operaciones.size();i++){
        operaciones[i] = 0;
    }

    yyFlexLexer flujo(&fichero, 0);
    flujo.yylex();
    escribir_datos(operaciones);
    return 0;
}

/*Funcion para mostrar los datos recogidos en el terminal */
void escribir_datos(vector<int> datos){

    cout << "Numero de sumas: " << datos[0] << endl;
    cout << "Numero de restas: " << datos[1] << endl;
    cout << "Numero de multiplicaciones: " << datos[2] << endl;
    cout << "Numero de divisiones: " << datos[3] << endl;
    cout << "Numero de modulos: " << datos[4] << endl;
    cout << "Numero de comparaciones: " << datos[5] << endl;
    cout << "Numero de condicionales: " << datos[6] << endl;
    cout << "Numero de bucles: " << datos[7] << endl;
    cout << "Numero de llamadas a funciones: " << datos[8] << endl;
}
