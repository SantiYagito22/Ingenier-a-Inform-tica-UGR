import * as THREE from '../libs/three.module.js'
import * as TWEEN from '../libs/tween.esm.js'
import { ThreeBSP } from '../libs/ThreeBSP.js'

class Comecocos extends THREE.Object3D {
  constructor() {
    super();
    
    
    //Material amarillo
    var materialCabeza=new THREE.MeshPhongMaterial({color: 0xFFFF00});
    
    //Voy a crear una esfera por revolucion, luego por cada frame hare que la revolucion sea menor para hacer el movimiento de la boca
    var esferaGeom =new THREE.SphereGeometry(2.0,50.0,50.0);//4.0,5.5);
    var cilindroGeom = new THREE.CylinderGeometry(0.3,0.3,10,30.0);
    var boxGeom = new THREE.BoxGeometry (2.5,0.5,10.0);

    cilindroGeom.rotateX(THREE.Math.degToRad(90));
    cilindroGeom.translate(-0.6,1,0);
    boxGeom.translate(1.0,0.0,0.0);
    // Ya podemos construir el Mesh
    var esferaBSP= new ThreeBSP(esferaGeom);
    var cajaBSP=new ThreeBSP(boxGeom);
    var cilindroBSP= new ThreeBSP(cilindroGeom);

    
    var comeParcial1= esferaBSP.subtract(cilindroBSP);
    var comeParcial2=comeParcial1.subtract(cajaBSP);
    // Y añadirlo como hijo del Object3D (el this)
    
    

    var comecocos=comeParcial2.toGeometry();
    var bufferGeometry= new THREE.BufferGeometry().fromGeometry(comecocos);
    this.result= new THREE.Mesh(bufferGeometry,materialCabeza);
    //this.result.rotateY(THREE.Math.degToRad(90));


    this.spline= new THREE.CatmullRomCurve3([new THREE.Vector3(0,0,0),new THREE.Vector3(-10,0,0),new THREE.Vector3(-10,0,10),new THREE.Vector3(10,0,10),new THREE.Vector3(10,0,5),new THREE.Vector3(0,0,5),new THREE.Vector3(0,0,0)]);
    var geometryLine = new THREE.Geometry();

    geometryLine.vertices=this.spline.getPoints(50);
    
    
    var materialRecorrido=new THREE.LineBasicMaterial({color:0x000000});
    var visibleSpline= new THREE.Line(geometryLine,materialRecorrido);
    


    this.add(visibleSpline);
    this.add(this.result);

    var origen1={p:0};
    var destino1={p:0.5};

    var that=this;
    var bucle6sec= new TWEEN.Tween(origen1).to(destino1,6000).easing(TWEEN.Easing.Quadratic.InOut).onUpdate(()=>{
      var pos= that.spline.getPointAt(origen1.p);
      that.result.position.copy(pos);
      var tangente= this.spline.getTangentAt(origen1.p);
      pos.add(tangente);
      //that.result.lookAt(pos);
    });

    var origen2={p:0.5};
    var destino2={p:1};
    
    var bucle4sec= new TWEEN.Tween(origen2).to(destino2,4000).easing(TWEEN.Easing.Quadratic.InOut).onUpdate(()=>{
      var pos= this.spline.getPointAt(origen2.p);
      that.result.position.copy(pos);
      var tangente= this.spline.getTangentAt(origen2.p);
      pos.add(tangente);
      //that.result.lookAt(pos);
    });

    var origen3={z:0};
    var destino3={z:Math.PI/4};

     
    var bucleboca= new TWEEN.Tween(origen3).to(destino3,1000).easing(TWEEN.Easing.Linear.None).onUpdate(()=>{
      let rotacionActual=origen3.z;
      that.result.rotation.z=origen3.z;
    }).repeat(Infinity).yoyo(true).start();


    
    bucle6sec.chain(bucle4sec);
    bucle4sec.chain(bucle6sec);
    bucle6sec.start();


   
  
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
    //folder.add (this.guiControls, 'radioCilindro', 0.25, 3.0, 0.1).name ('Radio : ').listen();
  
  }

  update () {
    // Con independencia de cómo se escriban las 3 siguientes líneas, el orden en el que se aplican las transformaciones es:
    // Primero, el escalado
    // Segundo, la rotación en Z
    // Después, la rotación en Y
    // Luego, la rotación en X
    // Y por último la traslación
    
    
    TWEEN.update();
  }

}
export { Comecocos };
