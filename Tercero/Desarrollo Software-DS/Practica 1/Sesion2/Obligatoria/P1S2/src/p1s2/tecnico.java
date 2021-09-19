package p1s2;

import java.util.Random;
import java.util.*;

public abstract class tecnico extends Thread{

	public trabajo trbRealizar;
        String nombre;
        int edad;
        String DNI;
        ArrayList<trabajo> trabajos;
        
 
        
         public tecnico(String n,int e,String dni, ArrayList<trabajo> sist)
        {
            this.nombre=n;
            this.edad=e;
            this.DNI=dni;
            this.trabajos=sist;
            
        }
         
        public trabajo getTrabajo(){
            return this.trbRealizar;
        }
         
        
        
        @Override
        public abstract void run();
        
        
        
}