
import 'trabajo.dart';
import 'managerFilter.dart';
import 'tecnico.dart';

class Cliente {
  int edad = 0;
  String nombre = "";
  Trabajo trb = new Trabajo(0.0, "", 0);

  Cliente(String n, int e) {
    this.nombre = n;
    this.edad = e;
  }

  Trabajo crearTrabajo(double pres, String t, int i) {
    trb = new Trabajo(pres, t, i);
    print("El cliente " +
        this.nombre +
        " ha creado el trabajo con id " +
        i.toString() +
        " y presupuesto " +
        pres.toString() +
        "\n");
    return trb;
  }

  void pagar(Tecnico t) {
    ManagerFilter mf = new ManagerFilter(t);

    mf.operacionFiltrar();


  }
}
