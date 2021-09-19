import * as THREE from '../libs/three.module.js'
import * as TWEEN from '../libs/tween.esm.js'

class Recorrido extends THREE.Object3D {
  constructor() {
    super();
    
    
   
    
    // El material se usa desde varios métodos. Por eso se alamacena en un atributo
    this.material = new THREE.MeshPhongMaterial({color: 0x00FF00});
    
    
    
    this.cono = new THREE.Mesh ( new THREE.ConeBufferGeometry(1.0,2.0,30.0), this.material);
    this.conoTumbado=new THREE.Object3D();
    
    
    this.spline= new THREE.CatmullRomCurve3([new THREE.Vector3(-10,5,10),new THREE.Vector3(-8,4,8),new THREE.Vector3(-6,3,6),new THREE.Vector3(-4,2,4),new THREE.Vector3(-2,1,2),new THREE.Vector3(0,0,0)
    ,new THREE.Vector3(2,1,-2),new THREE.Vector3(4,2,-4),new THREE.Vector3(6,3,-6),new THREE.Vector3(8,4,-8),new THREE.Vector3(10,5,-10)
    ,new THREE.Vector3(10,-3,10),new THREE.Vector3(-10,0,-10),new THREE.Vector3(-10,5,10)]);

    var geometryLine = new THREE.Geometry();

    geometryLine.vertices=this.spline.getPoints(50);


    var materialRecorrido=new THREE.LineBasicMaterial({color:0x000000});
    var visibleSpline= new THREE.Line(geometryLine,materialRecorrido);


    this.cono.rotation.x=THREE.Math.degToRad(90);
    this.conoTumbado.add(this.cono);
    this.add(this.conoTumbado);
    this.add(visibleSpline);

    var origen1={p:0};
    var destino1={p:0.5};

    var bucle4sec= new TWEEN.Tween(origen1).to(destino1,4000).easing(TWEEN.Easing.Quadratic.InOut).onUpdate(()=>{
      var pos= this.spline.getPointAt(origen1.p);
      this.conoTumbado.position.copy(pos);
      var tangente= this.spline.getTangentAt(origen1.p);
      pos.add(tangente);
      this.conoTumbado.lookAt(pos);
    });

    var origen2={p:0.5};
    var destino2={p:1};

    var bucle8sec= new TWEEN.Tween(origen2).to(destino2,8000).easing(TWEEN.Easing.Quadratic.InOut).onUpdate(()=>{
      var pos= this.spline.getPointAt(origen2.p);
      this.conoTumbado.position.copy(pos);
      var tangente= this.spline.getTangentAt(origen2.p);
      pos.add(tangente);
      this.conoTumbado.lookAt(pos);
    });
    
    bucle4sec.chain(bucle8sec);
    bucle8sec.chain(bucle4sec);
    bucle4sec.start();
    
    
    // Al nodo  this, la grapadora, se le cuelgan como hijos la base y la parte móvil
    
  }
  
 
  
  update () {
    
    // Se actualiza el nodo  this.movil  con el valor de la variable rotacion de la GUI
    TWEEN.update();
  } 
}

export { Recorrido }
