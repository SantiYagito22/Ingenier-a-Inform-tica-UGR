

class Trabajo {
  double presupuesto = 0.0;
  String tipo = "";
  int id=0;
  bool ocupado = false;

  Trabajo(double p, String tip, int i) {
    this.presupuesto = p;
    this.tipo = tip;
    this.id = i;
  }

  double getPresupuesto(){return presupuesto;}
  void setPresupuesto(double p){presupuesto=p;}

  String getTipo(){return tipo;}
  void setTipo(String t){tipo=t;}

  int getID(){return id;}
  void setID(int i){id=i;}

  bool getOcupado(){return ocupado;}
  void setOcupado(bool oc){ocupado=oc;}


}
