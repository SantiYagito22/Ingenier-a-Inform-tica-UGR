import 'package:sosemado/parteTecnico.dart';

import 'trabajo.dart';
import 'Presupuesto.dart';
import 'parteTrabajo.dart';

class Tecnico {
  String nombre = "";
  int edad = 0;
  Trabajo trbRealizar = new Trabajo(0, "", 0);
  Presupuesto presupuesto=new Presupuesto(0.0, 0.0, 0.0, 0.0, 0.0,0.0);
  parteTrabajo pT=new parteTrabajo(0, 0, 0, 0);

  Tecnico(String n, int e) {
    this.nombre = n;
    this.edad = e;
    
  }

  String getNombre(){return nombre;}
  void setNombre(String n){nombre=n;}
  int getEdad(){return edad;}
  void setEdad(int e){edad=e;}
  void setParte(parteTrabajo p){pT=p;}
  parteTrabajo getParte(){return pT;}
  Trabajo getTrabajo(){return trbRealizar;}
  Presupuesto getPresupuesto(){return presupuesto;}
  

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


String cobrar()
{
   return "El tecnico " +this.nombre+" ha cobrado el trabajo con id "+this.trbRealizar.getID().toString() +" con una cantidad de "+this.trbRealizar.getPresupuesto().toString();
}

Presupuesto asistentePresupuesto()
{
 double precioHoraRecom=0.0,materialRecom=0.0,desplazamientoRecom=0.0,personalRecom=0.0;
  
 double total=presupuesto.total();
 

  if(presupuesto.getDuracion()*presupuesto.getPrecioHora()>total*0.2)
    precioHoraRecom=(total*0.2)/presupuesto.getDuracion();
  else
    precioHoraRecom=presupuesto.getPrecioHora();
 


  if(presupuesto.getMaterial()>=total/2)
    materialRecom=3*presupuesto.getMaterial()/4;
  else if(presupuesto.getMaterial()<=total*0.1)
    materialRecom= presupuesto.getMaterial() + presupuesto.getMaterial()/2;
  else
    materialRecom=presupuesto.getMaterial();


  if(presupuesto.getDesplazamiento()>=total/2)
    desplazamientoRecom=3*presupuesto.getDesplazamiento()/4;
  else if(presupuesto.getDesplazamiento()<=total*0.1)
    desplazamientoRecom= presupuesto.getDesplazamiento() + presupuesto.getDesplazamiento()/2;
  else
    desplazamientoRecom= presupuesto.getDesplazamiento();


  if(presupuesto.getPersonalExtra()>=total*0.75)
    personalRecom=presupuesto.getPersonalExtra()*3/4;
  else
    personalRecom=presupuesto.getPersonalExtra();

  
  Presupuesto recomendado=new Presupuesto(presupuesto.getDuracion(), materialRecom, presupuesto.getComplejidad(), desplazamientoRecom, personalRecom, precioHoraRecom);
  return recomendado;

}




}


