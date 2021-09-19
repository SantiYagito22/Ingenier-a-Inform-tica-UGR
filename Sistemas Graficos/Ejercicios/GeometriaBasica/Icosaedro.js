import * as THREE from '../libs/three.module.js'
 
class Icosaedro extends THREE.Object3D {
  constructor(gui,titleGui) {
    super();
    
    // Se crea la parte de la interfaz que corresponde a la caja
    // Se crea primero porque otros métodos usan las variables que se definen para la interfaz
    this.createGUI(gui,titleGui);
    
    // Un Mesh se compone de geometría y material
    var IcosGeom = new THREE.IcosahedronGeometry();
    // Como material se crea uno a partir de un color
    var IcosMat = new THREE.MeshNormalMaterial();
    IcosMat.flatShading=true;
    IcosMat.needsUpdate=true;
    // Ya podemos construir el Mesh
    this.Icos = new THREE.Mesh (IcosGeom, IcosMat);
    // Y añadirlo como hijo del Object3D (el this)
    this.add (this.Icos);
    // Las geometrías se crean centradas en el origen.
    // Como queremos que el sistema de referencia esté en la base,
    // subimos el Mesh de la caja la mitad de su altura
    
    this.Icos.position.y = 0.5;
  
  }
  
  createGUI (gui,titleGui) {
    // Controles para el tamaño, la orientación y la posición de la caja
    this.guiControls = new function () {

      
      this.radio=1.0;
      this.subdivision=0.0;
      // Un botón para dejarlo todo en su posición inicial
      // Cuando se pulse se ejecutará esta función.
      this.reset = function () {
        this.radio=1.0;
        this.subdivision=0.0;
      }
    } 
    
    // Se crea una sección para los controles de la caja

    var that =this;

    var folder = gui.addFolder (titleGui);

    

    // Estas lineas son las que añaden los componentes de la interfaz
    // Las tres cifras indican un valor mínimo, un máximo y el incremento
    // El método   listen()   permite que si se cambia el valor de la variable en código, el deslizador de la interfaz se actualice
    folder.add (this.guiControls, 'radio', 1.0, 5.5, 0.1).name ('Radio : ').listen().onChange(function(value){
     that.Icos.geometry=new THREE.IcosahedronGeometry(value,that.guiControls.subdivision);
    });

    
    folder.add (this.guiControls, 'subdivision', 0.0, 5.0, 1.0).name ('Subdivision : ').listen().onChange(function(value){
      that.Icos.geometry=new THREE.IcosahedronGeometry(that.guiControls.radio,value);
     });;

    folder.add (this.guiControls, 'reset').name ('[ Reset ]').onChange(function(){
  
      that.Icos.geometry=new THREE.IcosahedronGeometry(1.0,0.0);

    });

    
  }
  
  update () {
    // Con independencia de cómo se escriban las 3 siguientes líneas, el orden en el que se aplican las transformaciones es:
    // Primero, el escalado
    // Segundo, la rotación en Z
    // Después, la rotación en Y
    // Luego, la rotación en X
    // Y por último la traslación
    this.Icos.rotation.x+=0.01;
    this.Icos.rotation.y+=0.01;
  }
}

export { Icosaedro };
