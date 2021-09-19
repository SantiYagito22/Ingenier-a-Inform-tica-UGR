import * as THREE from '../libs/three.module.js'
import { ThreeBSP } from '../libs/ThreeBSP.js'

class Taza extends THREE.Object3D {
  constructor() {
    super();
    
  
    // Un Mesh se compone de geometría y material
    
    // Como material se crea uno a partir de un color
    var tazaMat =  new THREE.MeshNormalMaterial();
    tazaMat.flatShading=false;
    tazaMat.needsUpdate=true;
   
    // Y añadirlo como hijo del Object3D (el this)
    var cilindro= new THREE.CylinderGeometry(2.0,2.0,4.0,30.0);
    cilindro.translate(0.0,-0.5,0.0);
    var cilindro2=new THREE.CylinderGeometry(1.8,1.8,4.0,30.0);
    var toroGeom = new THREE.TorusGeometry(1,0.25,20.0,30.0);
    toroGeom.translate(2.0,-0.2,0.0);

    var cilindrobsp=new ThreeBSP(cilindro);
    var cilindrobsp2=new ThreeBSP(cilindro2);
    var torusbsp=new ThreeBSP(toroGeom);

    var partialResult= cilindrobsp.union(torusbsp);
    var totalResult=partialResult.subtract(cilindrobsp2);

    var geometry= totalResult.toGeometry();
    var bufferGeometry= new THREE.BufferGeometry().fromGeometry(geometry);
    var result= new THREE.Mesh(bufferGeometry,tazaMat);

    this.add(result);
    

    
    // Las geometrías se crean centradas en el origen.
    // Como queremos que el sistema de referencia esté en la base,
    // subimos el Mesh de la caja la mitad de su altura
    


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

export { Taza };
