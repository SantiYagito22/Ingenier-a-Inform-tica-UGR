import * as THREE from '../libs/three.module.js'
import * as TWEEN from '../libs/tween.esm.js'

class Bola extends THREE.Object3D {
  constructor(gui, titleGui) {
    super();
    
    this.createGUI(gui, titleGui);
    this.radio = 4.0;

    var geoCono = new THREE.ConeGeometry(this.radio,5.0,32.0);
    var materialCono = new THREE.MeshNormalMaterial({opacity:0.35, transparent:true});
    this.cono = new THREE.Mesh(geoCono, materialCono);
    


    this.cono.scale.x= this.guiControls.escalado;
    this.cono.scale.z= this.guiControls.escalado;

    // Creamos la bola
    var geoBola = new THREE.SphereGeometry(0.5, 32.0, 32.0);
    var matBola = new THREE.MeshNormalMaterial();
    this.bola = new THREE.Mesh(geoBola, matBola);
    
    
  
    var origenTangente= {x: 0, z:0};
    var origenAltura= {y:-2.5};

    var destinoTangente = {x:2*Math.PI, z:2*Math.PI};
    var destinoAltura = {y:2.5};

    var that=this;

    var movimiento=new TWEEN.Tween(origenTangente)
    .to(destinoTangente,2000)
    .easing(TWEEN.Easing.Linear.None)
    .onUpdate(function(){
      var radioNuevo= ( ( 5 - (origenAltura.y + 2.5) ) * that.radio ) / 5;
      that.bola.position.x=Math.cos(origenTangente.x)*radioNuevo*that.guiControls.escalado;
      that.bola.position.z=Math.sin(origenTangente.x)*radioNuevo*that.guiControls.escalado;
    })
    .repeat(Infinity)
    .start();

    var movimientoAltura=new TWEEN.Tween(origenAltura)
    .to(destinoAltura,10000)
    .easing(TWEEN.Easing.Linear.None)
    .onUpdate(function(){
      that.bola.position.y=origenAltura.y;
    })
    .repeat(Infinity)
    .yoyo(true)
    .repeatDelay(500)
    .start();


    this.add(this.bola);
    this.add(this.cono);
  }



  createGUI(gui,titleGui) {
        // Controles para el tamaño, la orientación y la posición de la caja
        this.guiControls = new function () {
            this.escalado=1.0;
        }
        
      var that = this;
      // Se crea una sección para los controles de la caja
      var folder = gui.addFolder (titleGui);
      folder.add (this.guiControls, 'escalado', 0.5, 5.0, 0.5).name ('Escalado: ').listen().onChange(function(){
        that.cono.scale.x= that.guiControls.escalado;
        that.cono.scale.z= that.guiControls.escalado;
    });
        
  }

  update () {
  TWEEN.update();
    
   
  }
}

export { Bola };