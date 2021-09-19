package p1s2;

import java.util.*;

public abstract class  cliente {

        String nombre;
        int edad;
        String DNI;
	    ArrayList<trabajo> trabajosSubidos=new ArrayList<>();
        Sistema sistema;
        
        public cliente(String n,int e,String dni)
        {
            this.nombre=n;
            this.edad=e;
            this.DNI=dni;
            
        }
        
       public abstract void crearTrabajo(float of,String tipo,int num);
        
            
       public void editarTrabajo(int num,String tipo,float of )
       {
           Boolean buscado=true; 
           for(int i=0 ;i<this.sistema.trabajosSistemas.size() && buscado ;i++)
           {
               if(this.sistema.trabajosSistemas.get(i).getnumeroTrabajo()==num)
               {
                   this.trabajosSubidos.get(i).setOferta(of);
                   this.trabajosSubidos.get(i).setTipo(tipo);
                   buscado=false;
               }
           }
       }
       
       void cancelarTrabajo(int num){
            Boolean buscado=true; 
           for(int i=0 ;i<this.trabajosSubidos.size() && buscado ;i++)
           {
               if(trabajosSubidos.get(i).getnumeroTrabajo()==num){
                 this.trabajosSubidos.remove(i);
                 buscado=false;
               }
               
           }
           buscado=true;
           
           for(int i=0 ;i<this.sistema.trabajosSistemas.size() && buscado ;i++)
           {
               if(this.sistema.trabajosSistemas.get(i).getnumeroTrabajo()==num)
               {
                   this.sistema.trabajosSistemas.remove(i);
                   buscado=false;
               }
           }
       }

}