import 'dart:math';
import 'trabajo.dart';
import 'cliente.dart';
import 'tecnico.dart';

void main() {
  List<Trabajo> trabajosSistema = [];

  int cont = 0;
  Tecnico t1 = new Tecnico("Fran", 20);
  Cliente c1 = new Cliente("Santi", 29);

  trabajosSistema.add(c1.crearTrabajo(100, "Arreglar lavajillas", cont));
  cont++;
  trabajosSistema.add(c1.crearTrabajo(300, "Obra", cont));
  cont++;
  trabajosSistema.add(c1.crearTrabajo(500, "Reparacion cocina", cont));
  cont++;

  Random random = new Random();
  int selec = random.nextInt(3);
  t1.cogerTrabajo(selec, trabajosSistema);
  t1.realizarTrabajo();
  c1.pagar(t1);
}
