package p1s2;

public class clienteLite extends cliente {
    
    public static Boolean seguro_obra=false;
    
    public clienteLite(String n, int e, String dni) {
        super(n, e, dni);
    }
    
    @Override
     public void crearTrabajo(float of,String tipo,int num)
     {
           Boolean buscado=true; 
            for(int i=0 ;i<this.sistema.trabajosSistemas.size() && buscado ;i++)
           {
               if(this.sistema.trabajosSistemas.get(i).getnumeroTrabajo()==num)
               {
                   System.out.println("El trabajo ya existe en el sistema");
                   buscado=false;
               }
            }
            
            if(buscado==true){
                trabajo trb=new trabajo(of,tipo,num,this);
                System.out.println("El cliente LITE "+this.nombre+" ha creado el trabajo con id "+trb.num_trabajo);
                this.trabajosSubidos.add(trb);
                this.sistema.trabajosSistemas.add(trb);
                try {
                //Ponemos a "Dormir" el programa durante los s que queremos
                Thread.sleep(5*1000);
             } catch (Exception e) {
                System.out.println(e);
             }
            }
       
       }   
    
    
}