import * as THREE from '../libs/three.module.js'

class Reloj extends THREE.Object3D {
  constructor(gui,titleGui) {
    super();
    
    // Se crea la parte de la interfaz que corresponde a la grapadora
    // Se crea primero porque otros métodos usan las variables que se definen para la interfaz
    this.createGUI(gui,titleGui);
    
    // El material se usa desde varios métodos. Por eso se alamacena en un atributo
    this.material = new THREE.MeshPhongMaterial({color: 0x00FF00});
    this.material2=new THREE.MeshPhongMaterial({color: 0xFF0000});
    
    
    var esfera = new THREE.Mesh (new THREE.SphereBufferGeometry(1.0), this.material);
    
    this.esfera2= new THREE.Mesh (new THREE.SphereBufferGeometry(1.0), this.material2);
    

    esfera.position.z=10;
    this.esfera2.position.z=7.5;
    for(var i=0;i<12;i+=1)
    {
      var nuevaEsfera= esfera.clone();
      var nueva= new THREE.Object3D();
      nueva.rotation.y=THREE.Math.degToRad(30*i);
      nueva.add(nuevaEsfera);
      this.add(nueva);
    }
    this.nuevaEsfera2= new THREE.Object3D();
    this.nuevaEsfera2.add(this.esfera2);
    this.tiempoAnterior= Date.now();
    this.add(this.nuevaEsfera2);
    
    // Al nodo  this, la grapadora, se le cuelgan como hijos la base y la parte móvil
    
  }
  
 
  
  
  createGUI (gui,titleGui) {
    // Controles para el movimiento de la parte móvil
    this.guiControls = new function () {
      this.velocidad=1.0;
    } 
    
    // Se crea una sección para los controles de la caja
    var folder = gui.addFolder (titleGui);
    // Estas lineas son las que añaden los componentes de la interfaz
    // Las tres cifras indican un valor mínimo, un máximo y el incremento
    folder.add (this.guiControls, 'velocidad', -10, 10, 0.1).name ('Velocidad (marcas/s) : ');
  }
  
 
  update () {
    // Se actualiza el nodo  this.movil  con el valor de la variable rotacion de la GUI
    var tiempoActual= Date.now();
    var segundosTranscurridos= (tiempoActual-this.tiempoAnterior)/1000;
    this.nuevaEsfera2.rotation.y+=this.guiControls.velocidad*segundosTranscurridos;
    this.tiempoAnterior=tiempoActual;
  } 
}

export { Reloj }
