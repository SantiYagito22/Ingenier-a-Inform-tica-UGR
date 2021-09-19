#ifndef COMPORTAMIENTOJUGADOR_H
#define COMPORTAMIENTOJUGADOR_H

#include "comportamientos/comportamiento.hpp"

#include <list>

struct estado {
  int fila;
  int columna;
  int orientacion;
  bool zapatillas; //variable para saber si el agente tiene zapatillas
  bool bikyni; //variable para saber si el agente tiene zapatillas
};

class ComportamientoJugador : public Comportamiento {
  public:
    ComportamientoJugador(unsigned int size) : Comportamiento(size) {
      // Inicializar Variables de Estado
      fil = col = 99;
      brujula = 0; // 0: Norte, 1:Este, 2:Sur, 3:Oeste
      destino.fila = -1;
      destino.columna = -1;
      destino.orientacion = -1;
      cdest=destino;
      actual.bikyni=false;
      actual.zapatillas=false;
      hayplan=false;
      cont=0;
      recargaEncontrada=false;
      filaRecarga=-1;
      columnaRecarga=-1;


    }
    ComportamientoJugador(std::vector< std::vector< unsigned char> > mapaR) : Comportamiento(mapaR) {
      // Inicializar Variables de Estado
      fil = col = 99;
      brujula = 0; // 0: Norte, 1:Este, 2:Sur, 3:Oeste
      destino.fila = -1;
      destino.columna = -1;
      destino.orientacion = -1;
      cdest=destino;
      actual.bikyni=false;
      actual.zapatillas=false;
      hayplan=false;
      cont=0;
      recargaEncontrada=false;
      filaRecarga=-1;
      columnaRecarga=-1;




    }
    ComportamientoJugador(const ComportamientoJugador & comport) : Comportamiento(comport){}
    ~ComportamientoJugador(){}

    Action think(Sensores sensores);
    int interact(Action accion, int valor);
    void VisualizaPlan(const estado &st, const list<Action> &plan);
    ComportamientoJugador * clone(){return new ComportamientoJugador(*this);}

  private:
    // Declarar Variables de Estado
    int fil, col, brujula;
    estado actual, destino,cdest;
    list<Action> plan;
    bool hayplan; //variable para saber si hay un plan en ejecucion
    Action ultimaAccion;
    bool recargaEncontrada;//Variable para saber si se ha encontrado la posicion de recarga
    int cont,filaRecarga,columnaRecarga;//Contador para la recarga y variables de posicion de la misma.



    // Métodos privados de la clase
    bool pathFinding(int level, const estado &origen, const estado &destino, list<Action> &plan);
    bool pathFinding_Profundidad(const estado &origen, const estado &destino, list<Action> &plan);
    bool pathFinding_Anchura(const estado &origen, const estado &destino, list<Action> &plan);
    bool pathFinding_CosteUniforme(const estado &origen, const estado &destino, list<Action> &plan);
    int devolverCoste(estado st,bool tieneBikyni,bool tieneZapatillas);//Metodo que te devuelve el coste de bateria que supone ir a una casilla para un estado.
    unsigned char CasillaSiguienteRuta(Sensores sensores);//Metodo que devuelve la casilla de la ruta siguiente  al agente.
    int sentidoSiguienteRuta(Sensores sensores);//Metodo que devuelve el sentido que va a tener el agente despues de realizar una accion del plan
    void actualizaContenido(Sensores sensores);//Metodo que actualiza o pinta el mepa Resultado para la vision que tiene el agente en sensores
    void PintaPlan(list<Action> plan);//
    bool HayObstaculoDelante(estado &st);

};

#endif
