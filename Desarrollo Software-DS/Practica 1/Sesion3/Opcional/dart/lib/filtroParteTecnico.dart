import 'parteTecnico.dart';
import 'filtro.dart';
import 'trabajo.dart';


class FiltroParteTecnico extends Filtro {
  parteTecnico pt = new parteTecnico(0, 0, false);

  FiltroParteTecnico()
  {
    pt.rellenarParteTecnico();
  }

  void filtrar(Trabajo t)
  {
     if(pt.getnotaTrabajo()<5){
        t.setPresupuesto(t.getPresupuesto()-30);
    }
    else if(pt.getnotaTrabajo()>=5 && pt.getnotaTrabajo()<8)
        t.setPresupuesto(t.getPresupuesto()+10);
    else
       t.setPresupuesto(t.getPresupuesto()+20);

    if(pt.getActitud()<5){
        t.setPresupuesto(t.getPresupuesto()-30);
    }
    else if(pt.getActitud()>5 && pt.getActitud()<8)
        t.setPresupuesto(t.getPresupuesto()+10);
    else
        t.setPresupuesto(t.getPresupuesto()+20);

    
    if(pt.getRecomendacion()==true){
        t.setPresupuesto(t.getPresupuesto()+(t.getPresupuesto()*0.02));
        
    }
    else 
        t.setPresupuesto(t.getPresupuesto()-(t.getPresupuesto()*0.02));
  }
}
