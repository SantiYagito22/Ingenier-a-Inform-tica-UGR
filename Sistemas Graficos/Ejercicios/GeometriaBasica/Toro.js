import * as THREE from '../libs/three.module.js'
 
class Toro extends THREE.Object3D {
  constructor(gui,titleGui) {
    super();
    
    // Se crea la parte de la interfaz que corresponde a la caja
    // Se crea primero porque otros métodos usan las variables que se definen para la interfaz
    this.createGUI(gui,titleGui);
    
    // Un Mesh se compone de geometría y material
    var toroGeom = new THREE.TorusBufferGeometry(1.0,0.4,3.0,3.0);
    // Como material se crea uno a partir de un color
    var toroMat = new THREE.MeshNormalMaterial();
    toroMat.flatShading=true;
    toroMat.needsUpdate=true;
    // Ya podemos construir el Mesh
    this.toro = new THREE.Mesh (toroGeom, toroMat);
    // Y añadirlo como hijo del Object3D (el this)
    this.add (this.toro);
    // Las geometrías se crean centradas en el origen.
    // Como queremos que el sistema de referencia esté en la base,
    // subimos el Mesh de la caja la mitad de su altura
    
    this.toro.position.y = 0.5;
  
  }
  
  createGUI (gui,titleGui) {
    // Controles para el tamaño, la orientación y la posición de la caja
    this.guiControls = new function () {

      
      this.radioPrin=1.0;
      this.radioTubo=0.4;
      this.resToro=3.0;
      this.resTubo=3.0;
      // Un botón para dejarlo todo en su posición inicial
      // Cuando se pulse se ejecutará esta función.
      this.reset = function () {
        this.radioPrin=1.0;
        this.radioTubo=0.4;
        this.resToro=3.0;
        this.resTubo=3.0;
      }
    } 
    
    // Se crea una sección para los controles de la caja

    var that =this;

    var folder = gui.addFolder (titleGui);

    

    // Estas lineas son las que añaden los componentes de la interfaz
    // Las tres cifras indican un valor mínimo, un máximo y el incremento
    // El método   listen()   permite que si se cambia el valor de la variable en código, el deslizador de la interfaz se actualice
    folder.add (this.guiControls, 'radioPrin', 1.0, 3.0, 0.1).name ('Radio Principal: ').listen().onChange(function(value){
     that.toro.geometry=new THREE.TorusBufferGeometry(value,that.guiControls.radioTubo,that.guiControls.resToro,that.guiControls.resTubo);
    });

    folder.add (this.guiControls, 'radioTubo', 0.4, 3.0, 0.1).name ('Radio Tubo: ').listen().onChange(function(value){
        that.toro.geometry=new THREE.TorusBufferGeometry(that.guiControls.radioPrin,value,that.guiControls.resToro,that.guiControls.resTubo);
       });

    folder.add (this.guiControls, 'resToro', 3.0, 20.0, 1.0).name ('Resolucion Tubo : ').listen().onChange(function(value){
        that.toro.geometry=new THREE.TorusBufferGeometry(that.guiControls.radioPrin,that.guiControls.radioTubo,value,that.guiControls.resTubo);
       });

    folder.add (this.guiControls, 'resTubo', 3.0, 20.0, 1.0).name ('Resolucion Toro : ').listen().onChange(function(value){
        that.toro.geometry=new THREE.TorusBufferGeometry(that.guiControls.radioPrin,that.guiControls.radioTubo,that.guiControls.resToro,value);
     });

    folder.add (this.guiControls, 'reset').name ('[ Reset ]').onChange(function(){
  
      that.toro.geometry=new THREE.TorusBufferGeometry(1.0,0.4,3.0,3.0);
    });

    
  }

  
  update () {
    // Con independencia de cómo se escriban las 3 siguientes líneas, el orden en el que se aplican las transformaciones es:
    // Primero, el escalado
    // Segundo, la rotación en Z
    // Después, la rotación en Y
    // Luego, la rotación en X
    // Y por último la traslación
     
    this.toro.rotation.x+=0.01;
    this.toro.rotation.y+=0.01;
    
  }

}
export { Toro };
