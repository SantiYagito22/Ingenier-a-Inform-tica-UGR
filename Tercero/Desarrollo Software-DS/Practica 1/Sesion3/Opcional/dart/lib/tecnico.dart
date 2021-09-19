import 'trabajo.dart';


class Tecnico {
  String nombre = "";
  int edad = 0;
  Trabajo trbRealizar = new Trabajo(0, "", 0);

  Tecnico(String n, int e) {
    this.nombre = n;
    this.edad = e;
  }

  String getNombre(){return nombre;}
  void setNombre(String n){nombre=n;}
  int getEdad(){return edad;}
  void setEdad(int e){edad=e;}
  Trabajo getTrabajo(){return trbRealizar;}

  void cogerTrabajo(int id, List<Trabajo> trbs) {
    for (var i = 0; i < trbs.length; i++) {
      if (trbs[i].getID() == id && !trbs[i].getOcupado()) {
        trbRealizar = trbs[i];
        trbs[i].setOcupado(true);
        print("El tecnico "+this.nombre+" ha obtenido el trabajo con id: "+id.toString()+"\n");
      }
    }
  }

void realizarTrabajo()
{
    print("El tecnico "+ this.nombre +" realiza el trabajo con id: "+this.trbRealizar.getID().toString()+"\n");
}


void cobrar()
{
    print("El tecnico " +this.nombre+" ha cobrado el trabajo con id "+this.trbRealizar.getID().toString() +" con una cantidad de "+this.trbRealizar.getPresupuesto().toString());
}

}


