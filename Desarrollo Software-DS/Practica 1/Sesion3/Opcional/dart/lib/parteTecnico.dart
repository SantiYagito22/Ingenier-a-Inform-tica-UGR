import 'dart:io';
import 'dart:math';
import 'dart:async';

class parteTecnico {
  int notaTrabajo = 0;
  int actitud = 0;
  bool recomendacion = false;

  parteTecnico(int nt, int act, bool rc) {
    this.notaTrabajo = nt;
    this.actitud = act;
    this.recomendacion = rc;
  }

  int getnotaTrabajo() {
    return notaTrabajo;
  }

  int getActitud() {
    return actitud;
  }

  bool getRecomendacion() {
    return recomendacion;
  }

  void rellenarParteTecnico() {
    print("\nEl cliente ha rellenado el parte con los siguientes datos\n");

    Random random = new Random();

    this.notaTrabajo = random.nextInt(11);
    print("Ha valorado la nota del trabajo con un " + this.notaTrabajo.toString() + "\n");

    this.actitud = random.nextInt(11);
    print("Ha valorado la actitud con un " + this.actitud.toString() + "\n");

    int resp = random.nextInt(2);

    if (resp == 0) {
      this.recomendacion = false;
      print("No ha recomendado al técnico\n");
    } else {
      this.recomendacion = true;
      print("Ha recomendado al técnico");
    }
  }
}
