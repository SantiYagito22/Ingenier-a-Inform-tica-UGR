import * as THREE from '../libs/three.module.js'
 
class Diamante extends THREE.Object3D {
  constructor() {
    super();
    
    // Se crea la parte de la interfaz que corresponde a la caja
    // Se crea primero porque otros métodos usan las variables que se definen para la interfaz
    
    
    // Un Mesh se compone de geometría y material
    
    // Como material se crea uno a partir de un color
    var diamanteMat =  new THREE.MeshPhongMaterial({color: 0xFF0000});
   
    // Ya podemos construir el Mesh
    this.shapeDiamante=new THREE.Shape();
    this.shapeDiamante.moveTo(0,-1);
    this.shapeDiamante.lineTo(1,0);
    this.shapeDiamante.lineTo(0,1);
    this.shapeDiamante.lineTo(-1,0);
    this.shapeDiamante.lineTo(0,-1);

    const intrusionesDiamante = {
      steps: 1,
      depth: 0.5,
      bevelEnabled: true,
      bevelThickness: 0.2,
      bevelSize: 0.2,
      bevelOffset: 0,
      bevelSegments:3
    };

    var geomDiamante=new THREE.ExtrudeGeometry(this.shapeDiamante,intrusionesDiamante);
    this.diamond=new THREE.Mesh(geomDiamante,diamanteMat);

    // Y añadirlo como hijo del Object3D (el this)
    this.add (this.diamond);

  }
  
  createGUI (gui,titleGui) {
    // Controles para el tamaño, la orientación y la posición de la caja
    this.guiControls = new function () {
     
      // Un botón para dejarlo todo en su posición inicial
      // Cuando se pulse se ejecutará esta función.
      this.reset = function () {
       
      }
    } 
   
    // Se crea una sección para los controles de la caja
    var folder = gui.addFolder (titleGui);
    // Estas lineas son las que añaden los componentes de la interfaz
    // Las tres cifras indican un valor mínimo, un máximo y el incremento
    // El método   listen()   permite que si se cambia el valor de la variable en código, el deslizador de la interfaz se actualice
   
  

  
  }
  
  update () {
    // Con independencia de cómo se escriban las 3 siguientes líneas, el orden en el que se aplican las transformaciones es:
    // Primero, el escalado
    // Segundo, la rotación en Z
    // Después, la rotación en Y
    // Luego, la rotación en X
    // Y por último la traslación
   
  }
}

export { Diamante };
