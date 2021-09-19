import 'dart:io';
import 'dart:math';
import 'dart:async';

class parteTrabajo {
  double dificultad = 0.0;
  double horas = 0.0;
  double gastosMateriales = 0.0;
  double gastosTransporte = 0.0;

  parteTrabajo(double df, double h, double gm, double gt) {
    this.dificultad = df;
    this.horas = h;
    this.gastosMateriales = gm;
    this.gastosTransporte = gt;
  }

  double getDificultad() {
    return dificultad;
  }

  double getHoras() {
    return horas;
  }

  double getGastosMateriales() {
    return gastosMateriales;
  }

  double getGastosTransporte() {
    return gastosTransporte;
  }
  
  
void rellenarParteTrabajo() {
  print("\nEl tecnico ha rellenado el parte con los siguientes datos\n");

  Random random = new Random();

  this.dificultad= random.nextDouble() * 11.0;
  print("Ha valorado la dificultad del trabajo con un " + this.dificultad.toString() +"\n");

  this.horas = random.nextDouble() * 50.0;
  print("La duración del trabajo ha sido de " + this.horas.toString() + "\n");

  this.gastosTransporte = random.nextDouble() * 100.0;
  print("Los gastos de transporte han sido de" + this.gastosTransporte.toString() + "\n");
  
  this.gastosMateriales = random.nextDouble() * 200.0;
  print("Los gastos de los materiales utilizados ha sido de " + this.gastosMateriales.toString() + "\n");
}

}

