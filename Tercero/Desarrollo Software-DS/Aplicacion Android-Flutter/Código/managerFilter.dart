import 'cadenaFiltro.dart';
import 'tecnico.dart';

class ManagerFilter{
  Tecnico  tec= new Tecnico("", 0);
  CadenaFiltro cf= new CadenaFiltro();

  ManagerFilter(Tecnico t){
    this.tec=t;
    this.cf=new CadenaFiltro();
    
    crearCadena(t);
  }

  void crearCadena(Tecnico t){
      cf.generar(t);
  }

  void operacionFiltrar(){
      cf.filtrar(tec.getTrabajo());
  }



}