import * as THREE from '../libs/three.module.js'
 
class Caja extends THREE.Object3D {
  constructor(gui,titleGui) {
    super();
    
    // Se crea la parte de la interfaz que corresponde a la caja
    // Se crea primero porque otros métodos usan las variables que se definen para la interfaz
    this.createGUI(gui,titleGui);
    
    // Un Mesh se compone de geometría y material
    var boxGeom = new THREE.BoxGeometry (1,1,1);
    // Como material se crea uno a partir de un color
    var boxMat = new THREE.MeshNormalMaterial();
    boxMat.flatShading=true;
    boxMat.needsUpdate=true;
    // Ya podemos construir el Mesh
    this.box = new THREE.Mesh (boxGeom, boxMat);
    // Y añadirlo como hijo del Object3D (el this)
    this.add (this.box);
    // Las geometrías se crean centradas en el origen.
    // Como queremos que el sistema de referencia esté en la base,
    // subimos el Mesh de la caja la mitad de su altura
    
    this.box.position.y = 0.5;
  
  }
  
  createGUI (gui,titleGui) {
    // Controles para el tamaño, la orientación y la posición de la caja
    this.guiControls = new function () {
      this.sizeXCubo = 1.0;
      this.sizeYCubo = 1.0;
      this.sizeZCubo = 1.0;
      
      this.rotXCubo = 1.0;
      this.rotYCubo = 1.0;
      this.rotZCubo = 1.0;

      this.posXCubo = 1.0;
      this.posYCubo = 1.0;
      this.posZCubo = 1.0;
      
      // Un botón para dejarlo todo en su posición inicial
      // Cuando se pulse se ejecutará esta función.
      this.reset = function () {
        this.sizeXCubo = 1.0;
        this.sizeYCubo = 1.0;
        this.sizeZCubo = 1.0;
        
      }
    } 
    
    // Se crea una sección para los controles de la caja
    var folder = gui.addFolder (titleGui);
    // Estas lineas son las que añaden los componentes de la interfaz
    // Las tres cifras indican un valor mínimo, un máximo y el incremento
    // El método   listen()   permite que si se cambia el valor de la variable en código, el deslizador de la interfaz se actualice
    folder.add (this.guiControls, 'sizeXCubo', 0.1, 5.0, 0.1).name ('Dimension X : ').listen();
    folder.add (this.guiControls, 'sizeYCubo', 0.1, 5.0, 0.1).name ('Dimension Y : ').listen();
    folder.add (this.guiControls, 'sizeZCubo', 0.1, 5.0, 0.1).name ('Dimension Z : ').listen();
    
    folder.add (this.guiControls, 'reset').name ('[ Reset ]');

    
  }
  
  update () {
    // Con independencia de cómo se escriban las 3 siguientes líneas, el orden en el que se aplican las transformaciones es:
    // Primero, el escalado
    // Segundo, la rotación en Z
    // Después, la rotación en Y
    // Luego, la rotación en X
    // Y por último la traslación
  
    this.scale.set (this.guiControls.sizeXCubo,this.guiControls.sizeYCubo,this.guiControls.sizeZCubo);
    this.box.rotation.x+=0.01;
    this.box.rotation.y+=0.01;
  }
}

export { Caja };
