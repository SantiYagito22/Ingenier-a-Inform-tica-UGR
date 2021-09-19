import 'filtro.dart';
import 'trabajo.dart';
import 'filtroParteTecnico.dart';
import 'filtroParteTrabajo.dart';

class CadenaFiltro{

List<Filtro> cadena = [];

CadenaFiltro(){
  cadena.clear();
}

void filtrar(Trabajo t){
  cadena[0].filtrar(t);
  cadena[1].filtrar(t);
}

void generar(){
  Filtro  p1=  new FiltroParteTecnico();

  cadena.add(p1);

  Filtro  p2 = new FiltroParteTrabajo();
    
  cadena.add(p2);
}



}