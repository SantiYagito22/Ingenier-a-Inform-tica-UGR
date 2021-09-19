import * as THREE from '../libs/three.module.js'
 
class Peon extends THREE.Object3D {
  constructor(gui,titleGui) {
    super();
    
    // Se crea la parte de la interfaz que corresponde a la caja
    // Se crea primero porque otros métodos usan las variables que se definen para la interfaz
    this.createGUI(gui,titleGui);
    
    // Un Mesh se compone de geometría y material
    
    // Como material se crea uno a partir de un color
    var peonMat =  new THREE.MeshNormalMaterial();
    peonMat.flatShading=false;
    peonMat.needsUpdate=true;
    this.points=[];
    this.points.push(new THREE.Vector3(0.0, -1.4, 0.0));
    this.points.push(new THREE.Vector3(1.0, -1.4, 0.0));
    this.points.push(new THREE.Vector3(1.0, -1.1, 0.0));
    this.points.push(new THREE.Vector3(1.0, -1.1, 0.0));
    this.points.push(new THREE.Vector3(0.5, -0.7, 0.0));
    this.points.push(new THREE.Vector3(0.4, -0.4, 0.0));
    this.points.push(new THREE.Vector3(0.4, 0.5, 0.0));
    this.points.push(new THREE.Vector3(0.5, 0.6, 0.0));
    this.points.push(new THREE.Vector3(0.3, 0.6, 0.0));
    this.points.push(new THREE.Vector3(0.5, 0.8, 0.0));
    this.points.push(new THREE.Vector3(0.55, 1.0, 0.0));
    this.points.push(new THREE.Vector3(0.5, 1.2, 0.0));
    this.points.push(new THREE.Vector3(0.3, 1.4, 0.0));
    this.points.push(new THREE.Vector3(0.0, 1.4, 0.0));
    // Ya podemos construir el Mesh
    this.peonCamb = new THREE.Mesh (new THREE.LatheGeometry(this.points,3.0,0,60*Math.PI/180), peonMat);
    this.peonComp = new THREE.Mesh (new THREE.LatheGeometry(this.points,3.0,0,2*Math.PI), peonMat);
    this.peonPerf = new THREE.Mesh (new THREE.LatheGeometry(this.points,20.0,0,2*Math.PI/180), peonMat);

    // Y añadirlo como hijo del Object3D (el this)
    this.add (this.peonCamb);
    this.add(this.peonComp);
    this.add(this.peonPerf);

    // Las geometrías se crean centradas en el origen.
    // Como queremos que el sistema de referencia esté en la base,
    // subimos el Mesh de la caja la mitad de su altura
    this.peonCamb.position.y = 0.5;

    this.peonComp.position.x=7;
    this.peonComp.position.y=0.5;

    this.peonPerf.position.x=-3.0;
    this.peonPerf.position.y=0.5;


  }
  
  createGUI (gui,titleGui) {
    // Controles para el tamaño, la orientación y la posición de la caja
    this.guiControls = new function () {
     this.resolucion=3.0;
      this.angulo=60*Math.PI/180;
      // Un botón para dejarlo todo en su posición inicial
      // Cuando se pulse se ejecutará esta función.
      this.reset = function () {
        this.resolucion=3.0;
        this.angulo=60*Math.PI/180;
      }
    } 
    var that =this;
    // Se crea una sección para los controles de la caja
    var folder = gui.addFolder (titleGui);
    // Estas lineas son las que añaden los componentes de la interfaz
    // Las tres cifras indican un valor mínimo, un máximo y el incremento
    // El método   listen()   permite que si se cambia el valor de la variable en código, el deslizador de la interfaz se actualice
    folder.add (this.guiControls, 'resolucion', 3.0, 20.0, 1.0).name ('Resolucion: ').listen().onChange(function(value){
      that.peonCamb.geometry= new THREE.LatheGeometry(that.points,value,0,that.guiControls.angulo);
      that.peonComp.geometry= new THREE.LatheGeometry(that.points,value,0,2*Math.PI);
     });

     folder.add (this.guiControls, 'angulo', 0.01, 6.3, 0.01).name ('Ángulo: ').listen().onChange(function(value){
      that.peonCamb.geometry= new THREE.LatheGeometry(that.points,that.guiControls.resolucion,0,value);
     });
    
     folder.add (this.guiControls, 'reset').name ('[ Reset ]').onChange(function(){
  
      that.peonCamb.geometry= new THREE.LatheGeometry(that.points,3.0,0,60*Math.PI/180);
      that.peonComp.geometry= new THREE.LatheGeometry(that.points,3.0,0,2*Math.PI);
    });
    
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

export { Peon };
