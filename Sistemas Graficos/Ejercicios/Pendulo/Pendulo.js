import * as THREE from '../libs/three.module.js'
import { ThreeBSP } from '../libs/ThreeBSP.js'

class Pendulo extends THREE.Object3D {
  constructor(gui, titleGui) {
    super();

    // Se crea la parte de la interfaz que corresponde a la grapadora
    // Se crea primero porque otros métodos usan las variables que se definen para la interfaz
    this.createGUI(gui, titleGui);

    // Un Mesh se compone de geometría y material



    this.pendulo = this.createPrimerPendulo();
    this.add(this.pendulo);

  }

  createPrimerPendulo() {

    var primerPendulo = new THREE.Object3D();
    // Como material se crea uno a partir de un color
    var cuadradoMedioMat = new THREE.MeshPhongMaterial({ color: 0xFF0000 });
    var cuadradoExtremosMat = new THREE.MeshPhongMaterial({ color: 0x00FF00 });
    var tornilloMat = new THREE.MeshPhongMaterial({ color: 0xEA899A });

    var tornillo= new THREE.Mesh(new THREE.CylinderBufferGeometry(0.5,0.5,0.5,8.0),tornilloMat);
    var cuadradoExtremo1 = new THREE.Mesh(new THREE.BoxGeometry(2, 2, 1.5), cuadradoExtremosMat);
    this.cuadradoExtremo2 = new THREE.Mesh(new THREE.BoxGeometry(2, 2, 1.5), cuadradoExtremosMat);
    this.cuadradoMedio = new THREE.Mesh(new THREE.BoxGeometry(2, 5, 1.5), cuadradoMedioMat);

    cuadradoExtremo1.rotation.z=this.guiControls.anguloPendulo;

    
    this.cuadradoMedio.position.y = -2.5;
    

    this.auxMedio= new THREE.Object3D();
    this.auxMedio.scale.y=this.guiControls.longitudMedio / 5.0;
    this.auxMedio.position.y=-1;
    this.auxMedio.add(this.cuadradoMedio);
    
    

    
    
    this.cuadradoExtremo2.position.y = -2;
    this.extr= new THREE.Object3D();
    this.extr.position.y=-(this.guiControls.longitudMedio)
    this.extr.add(this.cuadradoExtremo2);


    tornillo.rotation.x=90.0*Math.PI/180;
    tornillo.position.z=1.0;
    
    this.pendulo2= this.createSegundoPendulo();
    this.pendulo2.position.z=1.25;
    

    primerPendulo.add(cuadradoExtremo1);
    primerPendulo.add(tornillo);
    primerPendulo.add(this.auxMedio);
    primerPendulo.add(this.extr);
    primerPendulo.add(this.pendulo2);

    return primerPendulo;

  }


  createSegundoPendulo() {
    
    var segundoPendulo=new THREE.Object3D();
    var tornilloMat = new THREE.MeshPhongMaterial({ color: 0xFFFF00 });

    var tornillo= new THREE.Mesh(new THREE.CylinderBufferGeometry(0.25,0.25,0.25,8.0),tornilloMat);
    var cuadradoMat = new THREE.MeshPhongMaterial({ color: 0x0000FF });
    
    

    this.cuadrado2 = new THREE.Mesh(new THREE.BoxGeometry(1, 7, 1.0), cuadradoMat);
    this.cuadrado2.position.y=-3.5;

    tornillo.rotation.x=90.0*Math.PI/180;
    
    tornillo.position.z=0.5;
    
    this.pendulo2V= new THREE.Object3D();
    this.pendulo2V.position.y=+0.875;
    this.pendulo2V.add(this.cuadrado2);
    
    
    this.pendulo3V= new THREE.Object3D();
    this.pendulo3V.add(this.pendulo2V);
    this.pendulo3V.add(tornillo);

    this.pendulo4V= new THREE.Object3D();
    this.pendulo4V.position.y=-1.875;
    this.pendulo4V.add(this.pendulo3V);
    

    segundoPendulo.add(this.pendulo4V);
    
    
    return segundoPendulo;

  }



  createGUI(gui, titleGui) {
    // Controles para el tamaño, la orientación y la posición de la caja
    this.guiControls = new function () {
      this.anguloPendulo = 0;
      this.anguloPendulo2 = 0;
      this.longitudMedio = 5.0;
      this.longitudPendulo2=7.0;
      this.pos=0.0;
      this.longitudActual=5.0;
    }


    var that = this;
    // Se crea una sección para los controles de la caja
    var folder = gui.addFolder(titleGui);
    var folder2=gui.addFolder("Segundo Péndulo");
    // Estas lineas son las que añaden los componentes de la interfaz
    // Las tres cifras indican un valor mínimo, un máximo y el incremento
    // El método   listen()   permite que si se cambia el valor de la variable en código, el deslizador de la interfaz se actualice
    folder.add(this.guiControls, 'anguloPendulo', -0.8, 0.8, 0.1).name('Giro: ');
    folder.add(this.guiControls, 'longitudMedio', 5.0, 10.0, 0.1).name('Longitud: ').listen().onChange(function (value) {
      
      that.auxMedio.scale.y=value / 5.0;
      that.extr.position.y=-(value);
    });

    folder2.add(this.guiControls, 'longitudPendulo2', 7.0, 14.0, 0.5).name('Longitud: ').listen().onChange(function (value){
      that.pendulo2V.scale.y=value/7.0;
    });
    folder2.add(this.guiControls, 'pos', 0.0, 90.0, 0.1).name('Posicion (%): ');
    folder2.add(this.guiControls, 'anguloPendulo2', -0.8, 0.8, 0.1).name('Giro: ');



  }

  update() {
    // Con independencia de cómo se escriban las 3 siguientes líneas, el orden en el que se aplican las transformaciones es:
    // Primero, el escalado
    // Segundo, la rotación en Z
    // Después, la rotación en Y
    // Luego, la rotación en X
    // Y por último la traslación
    this.pendulo.rotation.z=this.guiControls.anguloPendulo;
    this.pendulo3V.rotation.z=this.guiControls.anguloPendulo2;
    this.pendulo2.position.y=-1*((this.guiControls.pos/100)*this.guiControls.longitudMedio );

  }
}

export { Pendulo };
