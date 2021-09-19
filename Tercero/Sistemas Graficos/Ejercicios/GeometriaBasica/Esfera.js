import * as THREE from '../libs/three.module.js'
 
class Esfera extends THREE.Object3D {
  constructor(gui,titleGui) {
    super();
    
    // Se crea la parte de la interfaz que corresponde a la caja
    // Se crea primero porque otros métodos usan las variables que se definen para la interfaz
    this.createGUI(gui,titleGui);
    
    // Un Mesh se compone de geometría y material
    var esferaGeom = new THREE.SphereBufferGeometry(1.0,3.0,2.0);
    // Como material se crea uno a partir de un color
    var esferaMat = new THREE.MeshNormalMaterial();
    esferaMat.flatShading=true;
    esferaMat.needsUpdate=true;
    // Ya podemos construir el Mesh
    this.esfera = new THREE.Mesh (esferaGeom, esferaMat);
    // Y añadirlo como hijo del Object3D (el this)
    this.add (this.esfera);
    // Las geometrías se crean centradas en el origen.
    // Como queremos que el sistema de referencia esté en la base,
    // subimos el Mesh de la caja la mitad de su altura
    
    this.esfera.position.y = 0.5;
  
  }
  
  createGUI (gui,titleGui) {
    // Controles para el tamaño, la orientación y la posición de la caja
    this.guiControls = new function () {

      
      this.radio=1.0;
      this.resEcuador=3.0;
      this.resMeridiano=2.0;
      // Un botón para dejarlo todo en su posición inicial
      // Cuando se pulse se ejecutará esta función.
      this.reset = function () {
        this.radio=1.0;
        this.resEcuador=3.0;
        this.resMeridiano=2.0;
      }
    } 
    
    // Se crea una sección para los controles de la caja

    var that =this;

    var folder = gui.addFolder (titleGui);

    

    // Estas lineas son las que añaden los componentes de la interfaz
    // Las tres cifras indican un valor mínimo, un máximo y el incremento
    // El método   listen()   permite que si se cambia el valor de la variable en código, el deslizador de la interfaz se actualice
    folder.add (this.guiControls, 'radio', 1.0, 3.0, 0.1).name ('Radio : ').listen().onChange(function(value){
     that.esfera.geometry=new THREE.SphereBufferGeometry(value,that.guiControls.resEcuador,that.guiControls.resMeridiano);
    });

    folder.add (this.guiControls, 'resEcuador', 3.0, 20.0, 1.0).name ('Res.Ecuador : ').listen().onChange(function(value){
        that.esfera.geometry=new THREE.SphereBufferGeometry(that.guiControls.radio,value,that.guiControls.resMeridiano);
       });

    folder.add (this.guiControls, 'resMeridiano', 2.0, 20.0, 1.0).name ('Res.Meridiano : ').listen().onChange(function(value){
      that.esfera.geometry=new THREE.SphereBufferGeometry(that.guiControls.radio,that.guiControls.resEcuador,value);
     });

    folder.add (this.guiControls, 'reset').name ('[ Reset ]').onChange(function(){
  
      that.esfera.geometry=new THREE.SphereBufferGeometry(1.0,3.0,2.0);
    });

    
  }

  
  update () {
    // Con independencia de cómo se escriban las 3 siguientes líneas, el orden en el que se aplican las transformaciones es:
    // Primero, el escalado
    // Segundo, la rotación en Z
    // Después, la rotación en Y
    // Luego, la rotación en X
    // Y por último la traslación
    this.esfera.rotation.x+=0.01;
    this.esfera.rotation.y+=0.01;
  }

}
export { Esfera };
