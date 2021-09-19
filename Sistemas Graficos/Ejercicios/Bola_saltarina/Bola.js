import * as THREE from '../libs/three.module.js'
import * as TWEEN from '../libs/tween.esm.js'
class Bola extends THREE.Object3D {
  constructor(gui,titleGui) {
    super();
    
    // Se crea la parte de la interfaz que corresponde a la caja
    // Se crea primero porque otros métodos usan las variables que se definen para la interfaz
    this.createGUI(gui,titleGui);
    
    // Un Mesh se compone de geometría y material
    var cilindroGeom = new THREE.CylinderBufferGeometry(5.0,5.0,10.0,30.0);
    
    // Como material se crea uno a partir de un color
    var cilindroMat = new THREE.MeshNormalMaterial({transparent:true,opacity:0.4});
    var esferaMat = new THREE.MeshNormalMaterial();
    this.esfera = new THREE.Mesh (new THREE.SphereBufferGeometry(1.0,50.0,50.0), esferaMat);
    cilindroMat.flatShading=true;
    cilindroMat.needsUpdate=true;
    // Ya podemos construir el Mesh
    this.cilindro = new THREE.Mesh (cilindroGeom, cilindroMat);
    // Y añadirlo como hijo del Object3D (el this)
    this.add (this.cilindro);
    this.add(this.esfera);

    var origenTangente={x:0,z:0};
    var origenAltura={y:-4.5};

    var destinoTangente={x:2*Math.PI,z:2*Math.PI};
    var destinoAltura={y:4.5};

    var that=this;

    var movimientoLado=new TWEEN.Tween(origenTangente)
    .to(destinoTangente,6000)
    .easing(TWEEN.Easing.Linear.None)
    .onUpdate(function(){
      that.esfera.position.x=Math.cos(origenTangente.x)*5.0*that.guiControls.radioCilindro;
      that.esfera.position.z=Math.sin(origenTangente.z)*5.0*that.guiControls.radioCilindro;
    }).repeat(Infinity).start();
    
    var movimientoAltura=new TWEEN.Tween(origenAltura)
    .to(destinoAltura,500)
    .easing(TWEEN.Easing.Linear.None)
    .onUpdate(function(){
      that.esfera.position.y=origenAltura.y;
    }).repeat(Infinity).yoyo(true).start();

  
  }
  
  createGUI (gui,titleGui) {
    // Controles para el tamaño, la orientación y la posición de la caja
    this.guiControls = new function () {
      this.radioCilindro=1.0;
      // Un botón para dejarlo todo en su posición inicial
      // Cuando se pulse se ejecutará esta función.
      this.reset = function () {
       this.radioCilindro=1.0;
      }
    }
    // Se crea una sección para los controles de la caja
    

    var folder = gui.addFolder (titleGui);
    folder.add (this.guiControls, 'radioCilindro', 0.25, 3.0, 0.1).name ('Radio : ').listen();
  
  }

  update () {
    // Con independencia de cómo se escriban las 3 siguientes líneas, el orden en el que se aplican las transformaciones es:
    // Primero, el escalado
    // Segundo, la rotación en Z
    // Después, la rotación en Y
    // Luego, la rotación en X
    // Y por último la traslación
    
    this.cilindro.scale.set(this.guiControls.radioCilindro,1,this.guiControls.radioCilindro);
    TWEEN.update();
  }

}
export { Bola };
