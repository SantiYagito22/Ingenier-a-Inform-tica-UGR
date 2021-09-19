import * as THREE from '../libs/three.module.js'
 
class Corazon extends THREE.Object3D {
  constructor() {
    super();
    
    // Se crea la parte de la interfaz que corresponde a la caja
    // Se crea primero porque otros métodos usan las variables que se definen para la interfaz
    
    
    // Un Mesh se compone de geometría y material
    
    // Como material se crea uno a partir de un color
    var corazonMat =  new THREE.MeshPhongMaterial({color: 0xFF0000});
   
    // Ya podemos construir el Mesh
    this.shapeCorazon=new THREE.Shape();
    this.shapeCorazon.moveTo(0,-0.5);
    this.shapeCorazon.quadraticCurveTo(-1,1.25,-2,0);
    this.shapeCorazon.quadraticCurveTo(-2.5,-0.5,-1.5,-1.5);
    this.shapeCorazon.lineTo(0,-3.5);
    this.shapeCorazon.lineTo(1.5,-1.5);
    this.shapeCorazon.quadraticCurveTo(2.5,-0.5,2,0);
    this.shapeCorazon.quadraticCurveTo(1,1.25,0,-0.5);
    
    this.pts=[];
    for(var i=0;i<360;i+=1)
    {
      this.pts.push(new THREE.Vector3(1*Math.cos(i*Math.PI/180), 0.05*i, 1*Math.sin(i*Math.PI/180)));
    }
    
    var path=new THREE.CatmullRomCurve3(this.pts);
    

    const intrusionesCorazon = {
      steps: 50,
      depth: 1.0,
      bevelEnabled: true,
      bevelThickness: 0.5,
      bevelSize: 0.5,
      bevelOffset: 0,
      extrudePath: path ,
      bevelSegments:50
    };

    var geomCorazon=new THREE.ExtrudeGeometry(this.shapeCorazon,intrusionesCorazon);
    this.heart=new THREE.Mesh(geomCorazon,corazonMat);

    // Y añadirlo como hijo del Object3D (el this)
    this.add (this.heart);
   

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

export { Corazon };