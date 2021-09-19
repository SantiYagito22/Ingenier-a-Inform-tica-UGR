import * as THREE from '../libs/three.module.js'
 
class Cilindro extends THREE.Object3D {
  constructor(gui,titleGui) {
    super();
    
    // Se crea la parte de la interfaz que corresponde a la caja
    // Se crea primero porque otros métodos usan las variables que se definen para la interfaz
    this.createGUI(gui,titleGui);
    
    // Un Mesh se compone de geometría y material
    var cilindroGeom = new THREE.CylinderBufferGeometry(1.0,1.0,1.0,3.0);
    // Como material se crea uno a partir de un color
    var cilindroMat = new THREE.MeshNormalMaterial();
    cilindroMat.flatShading=true;
    cilindroMat.needsUpdate=true;
    // Ya podemos construir el Mesh
    this.cilindro = new THREE.Mesh (cilindroGeom, cilindroMat);
    // Y añadirlo como hijo del Object3D (el this)
    this.add (this.cilindro);
    // Las geometrías se crean centradas en el origen.
    // Como queremos que el sistema de referencia esté en la base,
    // subimos el Mesh de la caja la mitad de su altura
    
    this.cilindro.position.y = 0.5;
  
  }
  
  createGUI (gui,titleGui) {
    // Controles para el tamaño, la orientación y la posición de la caja
    this.guiControls = new function () {

      
      this.radioSup=1.0;
      this.radioInf=1.0;
      this.altura=1.0;
      this.subdivision=3.0;
      // Un botón para dejarlo todo en su posición inicial
      // Cuando se pulse se ejecutará esta función.
      this.reset = function () {
        this.radioSup=1.0;
        this.radioInf=1.0;
        this.altura=1.0;
        this.subdivision=3.0;
      }
    } 
    
    // Se crea una sección para los controles de la caja

    var that =this;

    var folder = gui.addFolder (titleGui);

    

    // Estas lineas son las que añaden los componentes de la interfaz
    // Las tres cifras indican un valor mínimo, un máximo y el incremento
    // El método   listen()   permite que si se cambia el valor de la variable en código, el deslizador de la interfaz se actualice
    folder.add (this.guiControls, 'radioSup', 1.0, 3.0, 0.1).name ('Radio superior: ').listen().onChange(function(value){
     that.cilindro.geometry=new THREE.CylinderBufferGeometry(value,that.guiControls.radioInf,that.guiControls.altura,that.guiControls.subdivision);
    });

    folder.add (this.guiControls, 'radioInf', 1.0, 3.0, 0.1).name ('Radio inferior: ').listen().onChange(function(value){
        that.cilindro.geometry=new THREE.CylinderBufferGeometry(that.guiControls.radioSup,value,that.guiControls.altura,that.guiControls.subdivision);
       });

    folder.add (this.guiControls, 'altura', 0.0, 4.0, 1.0).name ('Altura : ').listen().onChange(function(value){
        that.cilindro.geometry=new THREE.CylinderBufferGeometry(that.guiControls.radioSup,that.guiControls.radioInf,value,that.guiControls.subdivision);
       });

    folder.add (this.guiControls, 'subdivision', 3.0, 20.0, 1.0).name ('Subdivision : ').listen().onChange(function(value){
        that.cilindro.geometry=new THREE.CylinderBufferGeometry(that.guiControls.radioSup,that.guiControls.radioInf,that.guiControls.altura,value);
     });

    folder.add (this.guiControls, 'reset').name ('[ Reset ]').onChange(function(){
  
      that.cilindro.geometry=new THREE.ConeBufferGeometry(1.0,1.0,1.0,8.0);
    });

    
  }

  
  update () {
    // Con independencia de cómo se escriban las 3 siguientes líneas, el orden en el que se aplican las transformaciones es:
    // Primero, el escalado
    // Segundo, la rotación en Z
    // Después, la rotación en Y
    // Luego, la rotación en X
    // Y por último la traslación
     
    this.cilindro.rotation.x+=0.01;
    this.cilindro.rotation.y+=0.01;
    
  }

}
export { Cilindro };
