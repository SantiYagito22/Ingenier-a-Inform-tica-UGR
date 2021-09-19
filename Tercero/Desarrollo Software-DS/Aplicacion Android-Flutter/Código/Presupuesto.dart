class Presupuesto {
  double duracion = 0.0;
  double material = 0.0;
  double complejidad = 0.0;
  double desplazamiento = 0.0;
  double gastosPersonalExtra = 0.0;
  double precioHora = 0.0;

  Presupuesto(double d, double m, double c, double des, double gp, double ph) {
    this.duracion = d;
    this.material = m;
    this.complejidad = c;
    this.desplazamiento = des;
    this.gastosPersonalExtra = gp;
    this.precioHora = ph;
  }

  double getDuracion() {
    return duracion;
  }

  double getMaterial() {
    return material;
  }

  double getComplejidad() {
    return complejidad;
  }

  double getDesplazamiento() {
    return desplazamiento;
  }

  double getPersonalExtra() {
    return gastosPersonalExtra;
  }

   double getPrecioHora() {
    return precioHora;
  }

  void setDuracion(double d) {
    duracion = d;
  }

  void setMaterial(double m) {
    material = m;
  }

  void setComplejidad(double c) {
    complejidad = c;
  }

  void setDesplazamiento(double ds) {
    desplazamiento = ds;
  }

  void setGastosPersonalExtra(double p) {
    gastosPersonalExtra = p;
  }

  void setPrecioHora(double ph) {
    precioHora = ph;
  }

  double total() {
    

    return this.duracion*this.precioHora +this.material +this.complejidad*10 + this.desplazamiento + this.gastosPersonalExtra;
  }
}
