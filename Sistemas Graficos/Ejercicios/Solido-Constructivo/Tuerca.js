import * as THREE from '../libs/three.module.js'
import { ThreeBSP } from '../libs/ThreeBSP.js'

class Tuerca extends THREE.Object3D {
  constructor() {
    super();
    
  
    // Un Mesh se compone de geometría y material
    
    // Como material se crea uno a partir de un color
    var tuercaMat =  new THREE.MeshNormalMaterial();
    tuercaMat.flatShading=false;
    tuercaMat.needsUpdate=true;
   
    // Y añadirlo como hijo del Object3D (el this)
    var cilindro= new THREE.CylinderGeometry(1.0,1.0,0.2,50.0);
    var cilindroFuera=new THREE.CylinderGeometry(2.0,2.0,0.20,6.0);
    this.shapeCirculo=new THREE.Shape();
    this.shapeCirculo.moveTo(0,0.1);
    this.shapeCirculo.quadraticCurveTo(-0.1,0.1,-0.1,0);
    this.shapeCirculo.quadraticCurveTo(-0.1,-0.1,0,-0.1);
    this.shapeCirculo.quadraticCurveTo(0.1,-0.1,0.1,0);
    this.shapeCirculo.quadraticCurveTo(0.1,0.1,0,0.1);

    this.pts=[];
    for(var i=0;i<360*20;i+=1)
    {
      this.pts.push(new THREE.Vector3(1.0*Math.cos(i*Math.PI/180), 0.0008*i, 1.0*Math.sin(i*Math.PI/180)));
    }
    var path=new THREE.CatmullRomCurve3(this.pts);

    const intrusionesCirculo = {
        steps: 300,
        depth: 0.0001,
        bevelEnabled: true,
        bevelThickness: 0.1,
        bevelSize: 0.1,
        bevelOffset: 0,
        extrudePath: path ,
        bevelSegments:30
      };

    var geomMuelle=new THREE.ExtrudeGeometry(this.shapeCirculo,intrusionesCirculo);
    geomMuelle.translate(0.0,-0.5,0.0);
    geomMuelle.scale(1.0,0.2,1.0);

    var muellebsp=new ThreeBSP(geomMuelle);
    
    var cilindroDentrobsp=new ThreeBSP(cilindro);
      
    var cilindroFuerabsp=new ThreeBSP(cilindroFuera);

    var partialResult= cilindroDentrobsp.subtract(muellebsp);
    var totalResult= cilindroFuerabsp.subtract(partialResult);

    var geometry= totalResult.toGeometry();
    var bufferGeometry= new THREE.BufferGeometry().fromGeometry(geometry);
    var result= new THREE.Mesh(bufferGeometry,tuercaMat);
    result.scale.set(1.0,2.0,1.0);
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

export { Tuerca };
