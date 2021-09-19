#include "../Comportamientos_Jugador/jugador.hpp"
#include "motorlib/util.h"

#include <iostream>
#include <cmath>
#include <set>
#include <stack>
#include <queue>


// Este es el método principal que debe contener los 4 Comportamientos_Jugador
// que se piden en la práctica. Tiene como entrada la información de los
// sensores y devuelve la acción a realizar.


Action ComportamientoJugador::think(Sensores sensores) {
	Action accion = actIDLE;


    actualizaContenido(sensores);
        actual.fila=sensores.posF;
        actual.columna=sensores.posC,
        actual.orientacion=sensores.sentido;
        destino.fila=sensores.destinoF;
        destino.columna=sensores.destinoC;

        //condiciones para saber si el agente tiene ya un bikini o unas zapatillas
    if(mapaResultado[actual.fila][actual.columna]=='K')
    {
        actual.bikyni=true;

    }
    if(mapaResultado[actual.fila][actual.columna]=='D')
    {
        actual.zapatillas=true;

    }


    //condicion con doble for para encontrar la posicion de la recarga en el mapa
    if(!recargaEncontrada && sensores.bateria<3000)
    {


    for(int i=0;i<mapaResultado.size();i++)
    {
        for(int j=0;j<mapaResultado.size();j++)
        {
            if(mapaResultado[i][j]=='X')
               {
                    recargaEncontrada=true;
                    filaRecarga=i;
                    columnaRecarga=j;
                    break;
               }
        }
    }

    }



    //Condidicones para el calculo de planes y para cuando te hace falta ir a la posición de recarga
    if(cdest.columna != sensores.destinoC or cdest.fila !=sensores.destinoF )
    {

        cdest.fila=sensores.destinoF;
        cdest.columna=sensores.destinoC;
        hayplan=false;
        if(sensores.bateria<250 && recargaEncontrada && sensores.vida>200  )
        {
            sensores.destinoF=filaRecarga;
            sensores.destinoC=columnaRecarga;

        }
    }
    destino.fila       = sensores.destinoF;
	destino.columna    = sensores.destinoC;



    if(cdest.columna != sensores.destinoC or cdest.fila !=sensores.destinoF )
    {
        cdest.fila=sensores.destinoF;
        cdest.columna=sensores.destinoC;
        hayplan=false;
    }

    if(!hayplan)
    {
        hayplan = pathFinding(sensores.nivel,actual,destino,plan);
         cout<<"Bateria: "<<sensores.bateria<<endl;
         cout<<"Tiempo: "<<sensores.vida<<endl;
    }


    Action sigAccion;


    unsigned char casillaSiguiente=CasillaSiguienteRuta(sensores);



    int sentSiguiente=sentidoSiguienteRuta(sensores);


    //Condiciones para recalcular el plan en el nivel 4 por si se va a pasar por un bosque,agua o precipicio
    if(casillaSiguiente=='B' && !actual.zapatillas && sentSiguiente==sensores.sentido && sensores.terreno[0]!='B' && sensores.nivel==4 && (mapaResultado[sensores.destinoF][sensores.destinoC]!='B' || mapaResultado[sensores.destinoF][sensores.destinoC]=='X') )
        hayplan=false;
    if(casillaSiguiente=='A' && !actual.bikyni && sentSiguiente==sensores.sentido && sensores.nivel && mapaResultado[sensores.destinoF][sensores.destinoC]!='A' && sensores.terreno[0]!='A' )
        hayplan=false;

    if(sensores.terreno[2]=='P' && sentSiguiente==sensores.sentido)
    {
        hayplan=false;
    }



    //Condiciones para seguir llevando a cabo el plan,recargar , si nos encontramos con un aldeano o nos chocamos con un muro
    if(hayplan and plan.size()>0  && !sensores.colision ){
        if(sentSiguiente!=sensores.sentido && sensores.superficie[2]=='a' ){
        accion=plan.front();
        plan.erase(plan.begin());
        }
        else if(sensores.superficie[2]=='a' && sentSiguiente==sensores.sentido) //si hay un aldenao
            sigAccion=actIDLE;
        else if(sensores.terreno[0]=='X' && cont<mapaResultado.size() && sensores.vida>150 && sensores.bateria<2700 )//si `pasamos por bateria de recarga
            {
                sigAccion=actIDLE;
                cont++;
            }

        else if(sensores.terreno[0]=='X' )
            {
                accion=plan.front();
                plan.erase(plan.begin());

            }

        else
        {
            accion=plan.front();
            plan.erase(plan.begin());
            cont=0;
        }
    }
    else if(sensores.colision) //si por el camino hay un muro
        hayplan=false;



  return accion;
}


    //Metodo que devuelve la casilla de la ruta siguiente  al agente.
    unsigned char ComportamientoJugador::CasillaSiguienteRuta(Sensores sensores)
    {
        unsigned char casilla;
        switch(sensores.sentido)
        {

        case 0:
            casilla=mapaResultado[sensores.posF-1][sensores.posC];
            break;
        case 1:
            casilla=mapaResultado[sensores.posF][sensores.posC+1];
            break;
        case 2:
            casilla=mapaResultado[sensores.posF+1][sensores.posC];
            break;
        case 3:
            casilla=mapaResultado[sensores.posF][sensores.posC-1];
            break;
        }
        return casilla;
    }

    //Metodo que devuelve el sentido que va a tener el agente despues de realizar una accion del plan
    int ComportamientoJugador::sentidoSiguienteRuta(Sensores sensores)
    {
        int sentidoSiguiente;
    if(sensores.sentido==1 && plan.front()==1)
    {

        sentidoSiguiente=0;
    }
    else if(sensores.sentido==1 && plan.front()==2)
    {
        sentidoSiguiente=2;
    }
    else if(sensores.sentido==1 && plan.front()==0)
    {

        sentidoSiguiente=1;
    }
    else if(sensores.sentido==0 && plan.front()==1)
    {

        sentidoSiguiente=3;

    }
    else if(sensores.sentido==0 && plan.front()==2)
    {

        sentidoSiguiente=1;

    }
    else if(sensores.sentido==0 && plan.front()==0)
    {

        sentidoSiguiente=0;

    }
    else if(sensores.sentido==2 && plan.front()==1)
    {

        sentidoSiguiente=1;

    }
    else if(sensores.sentido==2 && plan.front()==2)
    {
        ;
        sentidoSiguiente=3;

    }
    else if(sensores.sentido==2 && plan.front()==0)
    {

        sentidoSiguiente=2;

    }
    else if(sensores.sentido==3 && plan.front()==1)
    {

        sentidoSiguiente=2;

    }
    else if(sensores.sentido==3 && plan.front()==2)
    {

        sentidoSiguiente=0;

    }
    else if(sensores.sentido==3 && plan.front()==0)
    {

        sentidoSiguiente=3;

    }
     return sentidoSiguiente;
    }


//Metodo que actualiza o pinta el mepa Resultado para la vision que tiene el agente en sensores
  void ComportamientoJugador::actualizaContenido(Sensores sensores){



    mapaResultado[sensores.posF][sensores.posC]=sensores.terreno[0];
    switch(sensores.sentido)
    {
        case 0: mapaResultado[sensores.posF-1][sensores.posC]=sensores.terreno[2];
                mapaResultado[sensores.posF-2][sensores.posC]=sensores.terreno[6];
                mapaResultado[sensores.posF-3][sensores.posC]=sensores.terreno[12];
                mapaResultado[sensores.posF-1][sensores.posC-1]=sensores.terreno[1];
                mapaResultado[sensores.posF-1][sensores.posC+1]=sensores.terreno[3];
                mapaResultado[sensores.posF-2][sensores.posC-2]=sensores.terreno[4];
                mapaResultado[sensores.posF-2][sensores.posC-1]=sensores.terreno[5];
                mapaResultado[sensores.posF-2][sensores.posC+1]=sensores.terreno[7];
                mapaResultado[sensores.posF-2][sensores.posC+2]=sensores.terreno[8];
                mapaResultado[sensores.posF-3][sensores.posC-3]=sensores.terreno[9];
                mapaResultado[sensores.posF-3][sensores.posC-2]=sensores.terreno[10];
                mapaResultado[sensores.posF-3][sensores.posC-1]=sensores.terreno[11];
                mapaResultado[sensores.posF-3][sensores.posC+1]=sensores.terreno[13];
                mapaResultado[sensores.posF-3][sensores.posC+2]=sensores.terreno[14];
                mapaResultado[sensores.posF-3][sensores.posC+3]=sensores.terreno[15];
            break;
        case 1: mapaResultado[sensores.posF-1][sensores.posC+1]=sensores.terreno[1];
                mapaResultado[sensores.posF][sensores.posC+1]=sensores.terreno[2];
                mapaResultado[sensores.posF+1][sensores.posC+1]=sensores.terreno[3];
                mapaResultado[sensores.posF][sensores.posC+2]=sensores.terreno[6];
                mapaResultado[sensores.posF-2][sensores.posC+2]=sensores.terreno[4];
                mapaResultado[sensores.posF-1][sensores.posC+2]=sensores.terreno[5];
                mapaResultado[sensores.posF+1][sensores.posC+2]=sensores.terreno[7];
                mapaResultado[sensores.posF+2][sensores.posC+2]=sensores.terreno[8];
                mapaResultado[sensores.posF][sensores.posC+3]=sensores.terreno[12];
                mapaResultado[sensores.posF-3][sensores.posC+3]=sensores.terreno[9];
                mapaResultado[sensores.posF-2][sensores.posC+3]=sensores.terreno[10];
                mapaResultado[sensores.posF-1][sensores.posC+3]=sensores.terreno[11];
                mapaResultado[sensores.posF+1][sensores.posC+3]=sensores.terreno[13];
                mapaResultado[sensores.posF+2][sensores.posC+3]=sensores.terreno[14];
                mapaResultado[sensores.posF+3][sensores.posC+3]=sensores.terreno[15];


            break;
        case 2: mapaResultado[sensores.posF+1][sensores.posC]=sensores.terreno[2];
                mapaResultado[sensores.posF+1][sensores.posC+1]=sensores.terreno[1];
                mapaResultado[sensores.posF+1][sensores.posC-1]=sensores.terreno[3];
                mapaResultado[sensores.posF+2][sensores.posC]=sensores.terreno[6];
                mapaResultado[sensores.posF+2][sensores.posC+2]=sensores.terreno[4];
                mapaResultado[sensores.posF+2][sensores.posC+1]=sensores.terreno[5];
                mapaResultado[sensores.posF+2][sensores.posC-1]=sensores.terreno[7];
                mapaResultado[sensores.posF+2][sensores.posC-2]=sensores.terreno[8];
                mapaResultado[sensores.posF+3][sensores.posC]=sensores.terreno[12];
                mapaResultado[sensores.posF+3][sensores.posC+3]=sensores.terreno[9];
                mapaResultado[sensores.posF+3][sensores.posC+2]=sensores.terreno[10];
                mapaResultado[sensores.posF+3][sensores.posC+1]=sensores.terreno[11];
                mapaResultado[sensores.posF+3][sensores.posC-1]=sensores.terreno[13];
                mapaResultado[sensores.posF+3][sensores.posC-2]=sensores.terreno[14];
                mapaResultado[sensores.posF+3][sensores.posC-3]=sensores.terreno[15];
            break;
        case 3: mapaResultado[sensores.posF][sensores.posC-1]=sensores.terreno[2];
                mapaResultado[sensores.posF+1][sensores.posC-1]=sensores.terreno[1];
                mapaResultado[sensores.posF-1][sensores.posC-1]=sensores.terreno[3];
                mapaResultado[sensores.posF][sensores.posC-2]=sensores.terreno[6];
                mapaResultado[sensores.posF+2][sensores.posC-2]=sensores.terreno[4];
                mapaResultado[sensores.posF+1][sensores.posC-2]=sensores.terreno[5];
                mapaResultado[sensores.posF-1][sensores.posC-2]=sensores.terreno[7];
                mapaResultado[sensores.posF-2][sensores.posC-2]=sensores.terreno[8];
                mapaResultado[sensores.posF][sensores.posC-3]=sensores.terreno[12];
                mapaResultado[sensores.posF+3][sensores.posC-3]=sensores.terreno[9];
                mapaResultado[sensores.posF+2][sensores.posC-3]=sensores.terreno[10];
                mapaResultado[sensores.posF+1][sensores.posC-3]=sensores.terreno[11];
                mapaResultado[sensores.posF-1][sensores.posC-3]=sensores.terreno[13];
                mapaResultado[sensores.posF-2][sensores.posC-3]=sensores.terreno[14];
                mapaResultado[sensores.posF-3][sensores.posC-3]=sensores.terreno[15];
            break;
    }

 }

// Llama al algoritmo de busqueda que se usará en cada comportamiento del agente
// Level representa el comportamiento en el que fue iniciado el agente.
bool ComportamientoJugador::pathFinding (int level, const estado &origen, const estado &destino, list<Action> &plan){
	switch (level){
		case 1: cout << "Busqueda en profundad\n";
			      return pathFinding_Profundidad(origen,destino,plan);
						break;
		case 2: cout << "Busqueda en Anchura\n";
			      return pathFinding_Anchura(origen,destino,plan);
						break;
		case 3: cout << "Busqueda Costo Uniforme\n";
                return pathFinding_CosteUniforme(origen,destino,plan);
						break;
		case 4: cout << "Busqueda para el reto\n";
                return pathFinding_CosteUniforme(origen,destino,plan);
						break;
	}
	cout << "Comportamiento sin implementar\n";
	return false;
}


//---------------------- Implementación de la busqueda en profundidad ---------------------------

// Dado el código en carácter de una casilla del mapa dice si se puede
// pasar por ella sin riegos de morir o chocar.
bool EsObstaculo(unsigned char casilla){
	if (casilla=='P' or casilla=='M')
		return true;
	else
	  return false;
}


// Comprueba si la casilla que hay delante es un obstaculo. Si es un
// obstaculo devuelve true. Si no es un obstaculo, devuelve false y
// modifica st con la posición de la casilla del avance.
bool ComportamientoJugador::HayObstaculoDelante(estado &st){
	int fil=st.fila, col=st.columna;

  // calculo cual es la casilla de delante del agente
	switch (st.orientacion) {
		case 0: fil--; break;
		case 1: col++; break;
		case 2: fil++; break;
		case 3: col--; break;
	}

	// Compruebo que no me salgo fuera del rango del mapa
	if (fil<0 or fil>=mapaResultado.size()) return true;
	if (col<0 or col>=mapaResultado[0].size()) return true;

	// Miro si en esa casilla hay un obstaculo infranqueable
	if (!EsObstaculo(mapaResultado[fil][col])){
		// No hay obstaculo, actualizo el parámetro st poniendo la casilla de delante.
    st.fila = fil;
		st.columna = col;
		return false;
	}
	else{
	  return true;
	}
}



//Nodo utilizado para anchura y  profundidad
struct nodo{
	estado st;
	list<Action> secuencia;
};



//Functor utilizado para el anterior nodo
struct ComparaEstados{
	bool operator()(const estado &a, const estado &n) const{
		if ((a.fila > n.fila) or (a.fila == n.fila and a.columna > n.columna) or
	      (a.fila == n.fila and a.columna == n.columna and a.orientacion > n.orientacion))
            //or (a.fila== n.fila and a.columna==n.columna and a.orientacion==n.orientacion and a.batery>n.batery)
			return true;
		else
			return false;

	}
};


// Implementación de la búsqueda en profundidad.
// Entran los puntos origen y destino y devuelve la
// secuencia de acciones en plan, una lista de acciones.
bool ComportamientoJugador::pathFinding_Profundidad(const estado &origen, const estado &destino, list<Action> &plan) {
	//Borro la lista
	cout << "Calculando plan\n";
	plan.clear();
	set<estado,ComparaEstados> generados; // Lista de Cerrados
	stack<nodo> pila;											// Lista de Abiertos

  nodo current;
	current.st = origen;
	current.secuencia.empty();

	pila.push(current);

  while (!pila.empty() and (current.st.fila!=destino.fila or current.st.columna != destino.columna)){

		pila.pop();
		generados.insert(current.st);

		// Generar descendiente de girar a la derecha
		nodo hijoTurnR = current;
		hijoTurnR.st.orientacion = (hijoTurnR.st.orientacion+1)%4;
		if (generados.find(hijoTurnR.st) == generados.end()){
			hijoTurnR.secuencia.push_back(actTURN_R);
			pila.push(hijoTurnR);

		}

		// Generar descendiente de girar a la izquierda
		nodo hijoTurnL = current;
		hijoTurnL.st.orientacion = (hijoTurnL.st.orientacion+3)%4;
		if (generados.find(hijoTurnL.st) == generados.end()){
			hijoTurnL.secuencia.push_back(actTURN_L);
			pila.push(hijoTurnL);
		}

		// Generar descendiente de avanzar
		nodo hijoForward = current;
		if (!HayObstaculoDelante(hijoForward.st)){
			if (generados.find(hijoForward.st) == generados.end()){
				hijoForward.secuencia.push_back(actFORWARD);
				pila.push(hijoForward);
			}
		}

		// Tomo el siguiente valor de la pila
		if (!pila.empty()){
			current = pila.top();
		}
	}

  cout << "Terminada la busqueda\n";

	if (current.st.fila == destino.fila and current.st.columna == destino.columna){
		cout << "Cargando el plan\n";
		plan = current.secuencia;
		cout << "Longitud del plan: " << plan.size() << endl;
		PintaPlan(plan);
		// ver el plan en el mapa
		VisualizaPlan(origen, plan);
		return true;
	}
	else {
		cout << "No encontrado plan\n";
	}


	return false;
}

// Implementación de la búsqueda en anchura.
// Entran los puntos origen y destino y devuelve la
// secuencia de acciones en plan, una lista de acciones.

bool ComportamientoJugador::pathFinding_Anchura(const estado &origen, const estado &destino, list<Action> &plan)
{
    cout << "Calculando plan\n";
	plan.clear();
	set<estado,ComparaEstados> generados; // Lista de Cerrados
	queue<nodo> cola;											// Lista de Abiertos

  nodo current;
	current.st = origen;
	current.secuencia.empty();

	cola.push(current);

  while (!cola.empty() and (current.st.fila!=destino.fila or current.st.columna != destino.columna)){

		cola.pop();
		generados.insert(current.st);

		// Generar descendiente de girar a la derecha
		nodo hijoTurnR = current;
		hijoTurnR.st.orientacion = (hijoTurnR.st.orientacion+1)%4;
		if (generados.find(hijoTurnR.st) == generados.end()){
			hijoTurnR.secuencia.push_back(actTURN_R);
			cola.push(hijoTurnR);

		}

		// Generar descendiente de girar a la izquierda
		nodo hijoTurnL = current;
		hijoTurnL.st.orientacion = (hijoTurnL.st.orientacion+3)%4;
		if (generados.find(hijoTurnL.st) == generados.end()){
			hijoTurnL.secuencia.push_back(actTURN_L);
			cola.push(hijoTurnL);
		}

		// Generar descendiente de avanzar
		nodo hijoForward = current;
		if (!HayObstaculoDelante(hijoForward.st)){
			if (generados.find(hijoForward.st) == generados.end()){
				hijoForward.secuencia.push_back(actFORWARD);
				cola.push(hijoForward);
			}
		}

		// Tomo el siguiente valor de la pila
		if (!cola.empty()){
			current = cola.front();
		}
	}

  cout << "Terminada la busqueda\n";

	if (current.st.fila == destino.fila and current.st.columna == destino.columna){
		cout << "Cargando el plan\n";
		plan = current.secuencia;
		cout << "Longitud del plan: " << plan.size() << endl;
		PintaPlan(plan);
		// ver el plan en el mapa
		VisualizaPlan(origen, plan);
		return true;
	}
	else {
		cout << "No encontrado plan\n";
	}


	return false;



}




//Nuevo nodo utilizado para el coste uniforme
struct nodoCoste
{
    estado st;
    int coste;
    list<Action> secuencia;
};

//Metodo que te devuelve el coste de bateria que supone ir a una casilla para un estado.
int ComportamientoJugador::devolverCoste(estado st,bool tieneBikyni,bool tieneZapatillas)
{
    if(mapaResultado[st.fila][st.columna]=='A' and tieneBikyni==false)
        return 100;
    else if(mapaResultado[st.fila][st.columna]=='A' and tieneBikyni==true)
        return 10;
    else if(mapaResultado[st.fila][st.columna]=='B' and tieneZapatillas==false)
        return 50;
    else if(mapaResultado[st.fila][st.columna]=='B' and tieneZapatillas==true)
        return 5;
    else if(mapaResultado[st.fila][st.columna]=='T')
        return 2;
    else if (mapaResultado[st.fila][st.columna]=='P')
    {
        return 100;
    }
    else
        return 1;
}


//Nuevo functor utilizado para el nuevo nodo creado para coste uniforme, utilizado para la lista de cerrados
struct ComparaNodos{

bool operator()(nodoCoste const & n1,nodoCoste const & n2)
{
    if ((n1.st.fila > n2.st.fila) or (n1.st.fila == n2.st.fila and n1.st.columna > n2.st.columna) or
	      (n1.st.fila == n2.st.fila and n1.st.columna == n2.st.columna and n1.st.orientacion > n2.st.orientacion)
            or (n1.st.fila== n2.st.fila and n1.st.columna==n2.st.columna and n1.st.orientacion==n2.st.orientacion and n1.st.bikyni>n2.st.bikyni)
        or (n1.st.fila== n2.st.fila and n1.st.columna==n2.st.columna and n1.st.orientacion==n2.st.orientacion and n1.st.bikyni==n2.st.bikyni and n1.st.zapatillas>n2.st.zapatillas))
			return true;
		else
			return false;
}
};

//Functor utilizado para la cola de prioridad de la lista de abiertos del coste uniforme
struct ComparaNodosCoste{
    bool operator()(nodoCoste const & n1,nodoCoste const & n2)
    {
        if(n1.coste>n2.coste)

            return true;
        else
            return false;
    }
};

bool ComportamientoJugador::pathFinding_CosteUniforme(const estado &origen, const estado &destino, list<Action> &plan)
{
    cout << "Calculando plan\n";
	plan.clear();
	set<nodoCoste,ComparaNodos> generados; // Lista de Cerrados
	priority_queue<nodoCoste,vector<nodoCoste>,ComparaNodosCoste> cola;											// Lista de Abiertos

  nodoCoste current;
	current.st = origen;
	current.secuencia.empty();
	current.coste=0;

	cola.push(current);

  while (!cola.empty() and (current.st.fila!=destino.fila or current.st.columna != destino.columna)){

		cola.pop();
         if(mapaResultado[current.st.fila][current.st.columna]=='K')
        {
        current.st.bikyni=true;

        }
        if(mapaResultado[current.st.fila][current.st.columna]=='D')
        {
        current.st.zapatillas=true;

        }
		generados.insert(current);

		// Generar descendiente de girar a la derecha
		nodoCoste hijoTurnR = current;
		hijoTurnR.st.orientacion = (hijoTurnR.st.orientacion+1)%4;
		if (generados.find(hijoTurnR) == generados.end()){
			hijoTurnR.secuencia.push_back(actTURN_R);
			hijoTurnR.coste+=devolverCoste(current.st,current.st.bikyni,current.st.zapatillas);
			cola.push(hijoTurnR);

		}

		// Generar descendiente de girar a la izquierda

		nodoCoste hijoTurnL = current;
		hijoTurnL.st.orientacion = (hijoTurnL.st.orientacion+3)%4;
		if (generados.find(hijoTurnL) == generados.end()){
			hijoTurnL.secuencia.push_back(actTURN_L);
			hijoTurnL.coste+=devolverCoste(current.st,current.st.bikyni,current.st.zapatillas);
			cola.push(hijoTurnL);
		}

		// Generar descendiente de avanzar
		nodoCoste hijoForward = current;
		if (!HayObstaculoDelante(hijoForward.st)){
			if (generados.find(hijoForward) == generados.end()){
				hijoForward.secuencia.push_back(actFORWARD);
				hijoForward.coste+=devolverCoste(current.st,current.st.bikyni,current.st.zapatillas);
				cola.push(hijoForward);
			}
		}

		// Tomo el siguiente valor de la pila
		if (!cola.empty()){
			current = cola.top();
		}
	}

  cout << "Terminada la busqueda\n";

	if (current.st.fila == destino.fila and current.st.columna == destino.columna){
		cout << "Cargando el plan\n";
		plan = current.secuencia;
		cout << "Longitud del plan: " << plan.size() << endl;
		PintaPlan(plan);
		// ver el plan en el mapa
		VisualizaPlan(origen, plan);
		return true;
	}
	else {
		cout << "No encontrado plan\n";
	}


	return false;


}





// Sacar por la términal la secuencia del plan obtenido
void ComportamientoJugador::PintaPlan(list<Action> plan) {
	auto it = plan.begin();
	while (it!=plan.end()){
		if (*it == actFORWARD){
			cout << "A ";
		}
		else if (*it == actTURN_R){
			cout << "D ";
		}
		else if (*it == actTURN_L){
			cout << "I ";
		}
		else {
			cout << "- ";
		}
		it++;
	}
	cout << endl;
}



void AnularMatriz(vector<vector<unsigned char> > &m){
	for (int i=0; i<m[0].size(); i++){
		for (int j=0; j<m.size(); j++){
			m[i][j]=0;
		}
	}
}


// Pinta sobre el mapa del juego el plan obtenido
void ComportamientoJugador::VisualizaPlan(const estado &st, const list<Action> &plan){
  AnularMatriz(mapaConPlan);
	estado cst = st;

	auto it = plan.begin();
	while (it!=plan.end()){
		if (*it == actFORWARD){
			switch (cst.orientacion) {
				case 0: cst.fila--; break;
				case 1: cst.columna++; break;
				case 2: cst.fila++; break;
				case 3: cst.columna--; break;
			}
			mapaConPlan[cst.fila][cst.columna]=1;
		}
		else if (*it == actTURN_R){
			cst.orientacion = (cst.orientacion+1)%4;
		}
		else {
			cst.orientacion = (cst.orientacion+3)%4;
		}
		it++;
	}
}



int ComportamientoJugador::interact(Action accion, int valor){
  return false;
}
