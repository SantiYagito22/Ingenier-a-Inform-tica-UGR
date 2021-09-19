import 'package:flutter/material.dart';
import 'package:sosemado/Presupuesto.dart';
import 'tecnico.dart';
import 'trabajo.dart';
import 'cliente.dart';
import 'managerFilter.dart';
import 'parteTrabajo.dart';
import 'dart:math';

Tecnico t1 = new Tecnico("Fran", 20);
Cliente c1 = new Cliente("Santi", 29);

void main() {
  List<Trabajo> trabajosSistema = [];

  int cont = 0;

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

  runApp(MaterialApp(
    title: 'Sosemado',
    home: _PerfilTecnico(),
  ));
}

class _PerfilTecnico extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text("Perfil Técnico"),
      ),
      body: Center(
        child: Column(
          mainAxisAlignment: MainAxisAlignment.start,
          children: <Widget>[
            Text(
              '\nPerfil\n',
              style: TextStyle(
                  color: Colors.black,
                  fontSize: 25,
                  fontStyle: FontStyle.italic),
            ),
            new Image.asset('../imagen/tecnico.jpg'),
            Container(
              height: 40,
              alignment: Alignment.topLeft,
              padding: EdgeInsets.fromLTRB(10, 15, 10, 0),
              child: FittedBox(
                child: Text("Nombre: " + t1.getNombre()),
              ),
            ),
            Container(
              height: 40,
              alignment: Alignment.topLeft,
              padding: EdgeInsets.fromLTRB(10, 5, 10, 0),
              child: FittedBox(
                child: Text("Edad: " + t1.getEdad().toString()),
              ),
            ),
            if (t1.getTrabajo().getTipo() != "")
              Container(
                height: 40,
                alignment: Alignment.topLeft,
                padding: EdgeInsets.fromLTRB(10, 0, 5, 0),
                child: Text("Trabajo a realizar: " +
                    t1.getTrabajo().getTipo() +
                    " con presupuesto de " +
                    t1.getTrabajo().getPresupuesto().toString()),
              ),
            if (t1.getTrabajo().getTipo() == "")
              Container(
                height: 40,
                alignment: Alignment.topLeft,
                padding: EdgeInsets.fromLTRB(10, 0, 10, 0),
                child: FittedBox(
                  child: Text("Trabajo a realizar: Ninguno"),
                ),
              ),
            Column(
              mainAxisAlignment: MainAxisAlignment.spaceAround,
              mainAxisSize: MainAxisSize.max,
              children: <Widget>[
                Padding(
                  padding: EdgeInsets.only(top: 40),
                  child: MaterialButton(
                    elevation: 10.0,
                    minWidth: 200,
                    height: 50.0,
                    padding: EdgeInsets.fromLTRB(0, 10, 0, 0),
                    color: Colors.blue[200],
                    shape: RoundedRectangleBorder(
                        borderRadius: BorderRadius.circular(8.0)),
                    child: Text("Calculadora presupuesto"),
                    onPressed: () => Navigator.push(
                        context,
                        MaterialPageRoute(
                            builder: (context) => RutaCalculadora())),
                  ),
                ),
                Padding(
                  padding: EdgeInsets.only(top: 40),
                  child: MaterialButton(
                    elevation: 10.0,
                    minWidth: 200,
                    height: 50.0,
                    padding: EdgeInsets.fromLTRB(0, 10, 0, 0),
                    color: Colors.blue[200],
                    shape: RoundedRectangleBorder(
                        borderRadius: BorderRadius.circular(8.0)),
                    child: Text("Cobrar"),
                    onPressed: () => Navigator.push(context,
                        MaterialPageRoute(builder: (context) => RutaCobrar())),
                  ),
                )
              ],
            ),
          ],
        ),
      ),
    );
  }
}

class RutaCalculadora extends StatelessWidget {
  final controladorHoras = TextEditingController();
  final controladorPrecioHora = TextEditingController();
  final controladorMaterial = TextEditingController();
  final controladorComplejidad = TextEditingController();
  final controladorDesplazamiento = TextEditingController();
  final controladorPersonalExtra = TextEditingController();
  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text("Calculadora presupuesto"),
      ),
      body: Center(
        child: Column(
          mainAxisAlignment: MainAxisAlignment.spaceEvenly,
          children: <Widget>[
            Text(
              'Rellene todos los datos',
              style: TextStyle(
                  color: Colors.black,
                  fontSize: 25,
                  fontStyle: FontStyle.italic),
            ),
            Padding(
              padding: EdgeInsets.only(left: 20, right: 20),
              child: TextField(
                controller: controladorHoras,
                decoration: InputDecoration(
                    border: OutlineInputBorder(),
                    hintText: 'Introduzca la duración total'),
              ),
            ),
            Padding(
              padding: EdgeInsets.only(left: 20, right: 20),
              child: TextField(
                controller: controladorPrecioHora,
                decoration: InputDecoration(
                    border: OutlineInputBorder(),
                    hintText: 'Introduzca el precio/hora'),
              ),
            ),
            Padding(
              padding: EdgeInsets.only(left: 20, right: 20),
              child: TextField(
                controller: controladorComplejidad,
                decoration: InputDecoration(
                    border: OutlineInputBorder(),
                    hintText: 'Introduzca la complejidad del trabajo'),
              ),
            ),
            Padding(
              padding: EdgeInsets.only(left: 20, right: 20),
              child: TextField(
                controller: controladorMaterial,
                decoration: InputDecoration(
                    border: OutlineInputBorder(),
                    hintText: 'Introduzca los gastos materiales'),
              ),
            ),
            Padding(
              padding: EdgeInsets.only(left: 20, right: 20),
              child: TextField(
                controller: controladorDesplazamiento,
                decoration: InputDecoration(
                    border: OutlineInputBorder(),
                    hintText: 'Introduzca los gastos de transporte'),
              ),
            ),
            Padding(
              padding: EdgeInsets.only(left: 20, right: 20),
              child: TextField(
                controller: controladorPersonalExtra,
                decoration: InputDecoration(
                    border: OutlineInputBorder(),
                    hintText: 'Introduzca los gatos por personal extra'),
              ),
            ),
            MaterialButton(
              child: Text("Calcular"),
              color: Colors.blue[200],
              shape: RoundedRectangleBorder(
                  borderRadius: BorderRadius.circular(8.0)),
              onPressed: () {
                return showDialog(
                  context: context,
                  builder: (context) {
                    t1.getPresupuesto().setDuracion(double.parse(controladorHoras.text));
                    t1.getPresupuesto().setPrecioHora(
                        double.parse(controladorPrecioHora.text));
                    t1.getPresupuesto().setComplejidad(
                        double.parse(controladorComplejidad.text));
                    t1.getPresupuesto().setMaterial(double.parse(controladorMaterial.text));
                    t1.getPresupuesto().setDesplazamiento(
                        double.parse(controladorDesplazamiento.text));
                    t1.getPresupuesto().setGastosPersonalExtra(
                        double.parse(controladorPersonalExtra.text));
                    Presupuesto pC = t1.asistentePresupuesto();

                    return AlertDialog(
                      content: Column(
                        mainAxisAlignment: MainAxisAlignment.spaceEvenly,
                        children: <Widget>[
                          Padding(
                            padding: EdgeInsets.only(left: 3, right: 3),
                            child: Text(
                              "Recomendaciones",
                              style: TextStyle(
                                  color: Colors.black,
                                  fontSize: 25,
                                  fontStyle: FontStyle.italic),
                            ),
                          ),
                          Padding(
                            padding: EdgeInsets.only(left: 3, right: 3),
                            child: Text("El precio/hora recomendado es " +
                                pC.getPrecioHora().toString()),
                          ),
                          Padding(
                            padding: EdgeInsets.only(left: 3, right: 3),
                            child: Text("Los gastos materiales deben ser de " +
                                pC.getMaterial().toString()),
                          ),
                          Padding(
                            padding: EdgeInsets.only(left: 3, right: 3),
                            child: Text(
                                "Los gastos de transporte deben ser de " +
                                    pC.getDesplazamiento().toString()),
                          ),
                          Padding(
                            padding: EdgeInsets.only(left: 3, right: 3),
                            child: Text(
                                "Los gastos de personal extra deben ser de " +
                                    pC.getPersonalExtra().toString()),
                          ),
                          Padding(
                            padding: EdgeInsets.only(left: 3, right: 3),
                            child: Text(
                                "El presupuesto total recomendado es de " +
                                    pC.total().toString()),
                          ),
                          FloatingActionButton(
                            onPressed: () {
                              Navigator.of(context, rootNavigator: true).pop();
                            },
                            child: const Icon(Icons.check),
                          ),
                        ],
                      ),
                    );
                  },
                );
              },
            ),
          ],
        ),
      ),
    );
  }
}

class RutaCobrar extends StatelessWidget {
   final controladorHorasTrabajo = TextEditingController();
   final controladorDificultad = TextEditingController();
   final controladorTransporteTrabajo = TextEditingController();
   final controladorMaterialTrabajo = TextEditingController();
  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text("Parte Trabajo"),
      ),
      body: Center(
         child: Column(
          mainAxisAlignment: MainAxisAlignment.spaceEvenly,
          children: <Widget>[
             Text(
              'Rellene todos los datos',
              style: TextStyle(
                  color: Colors.black,
                  fontSize: 25,
                  fontStyle: FontStyle.italic),
            ),
            Padding(
              padding: EdgeInsets.only(left: 20, right: 20),
              child: TextField(
                controller: controladorHorasTrabajo,
                decoration: InputDecoration(
                    border: OutlineInputBorder(),
                    hintText: 'Introduzca la duración del trabajo'),
              ),
            ),
            Padding(
              padding: EdgeInsets.only(left: 20, right: 20),
              child: TextField(
                controller: controladorDificultad,
                decoration: InputDecoration(
                    border: OutlineInputBorder(),
                    hintText: 'Introduzca la dificultad del trabajo'),
              ),
            ),
            Padding(
              padding: EdgeInsets.only(left: 20, right: 20),
              child: TextField(
                controller: controladorMaterialTrabajo,
                decoration: InputDecoration(
                    border: OutlineInputBorder(),
                    hintText: 'Gastos de material del trabajo'),
              ),
            ),
            Padding(
              padding: EdgeInsets.only(left: 20, right: 20),
              child: TextField(
                controller: controladorTransporteTrabajo,
                decoration: InputDecoration(
                    border: OutlineInputBorder(),
                    hintText: 'Gastos de transporte del trabajo'),
              ),
            ),
            MaterialButton(
            child: Text("Calcular"),
            color: Colors.blue[200],
            shape: RoundedRectangleBorder(
            borderRadius: BorderRadius.circular(8.0)),
            onPressed: () {
              return showDialog(
                context: context,
                builder: (context) {
                  parteTrabajo pt=new parteTrabajo(double.parse(controladorDificultad.text), double.parse(controladorHorasTrabajo.text), double.parse(controladorMaterialTrabajo.text), double.parse(controladorTransporteTrabajo.text));
                  t1.setParte(pt);
                  c1.pagar(t1);
                return AlertDialog(
                    content: Column(
                      mainAxisAlignment: MainAxisAlignment.spaceEvenly,
                      mainAxisSize: MainAxisSize.min,
                    children: <Widget>[
                    Padding(
                      padding: EdgeInsets.only(left: 20, right: 20,bottom: 20),
                      child: Text(t1.cobrar()),
                    ),
                    FloatingActionButton(
                            onPressed: () {
                              Navigator.of(context, rootNavigator: true).pop();
                            },
                            child: const Icon(Icons.check),
                            ),
                          ],
                        ),
                 );
                },
              );
            },
            ),
          ],
         ),
      ),
    );
  }
}
