package p1s2;

import static java.lang.System.exit;
import java.util.ArrayList;
import java.util.Random;


public class Sistema {
    
     public static ArrayList<trabajo> trabajosSistemas=new ArrayList<>();
     public static ArrayList<cliente> clientesSistemas=new ArrayList<>();
     public static ArrayList<tecnico> tecnicosSistemas=new ArrayList<>();
     public static FactoriaAbstracta factoria;
     public static ArrayList<String> nombresPosibles=new ArrayList(){{add("Santiago"); add("Fran"); add("Raul");add("Cristian"); add("Angel");add("PEPE");}};
     public static ArrayList<String> DNIPosibles=new ArrayList(){{add("111111X");add("22222Z");add("3333333P");add("4444444S");add("77777V");add("88888Z");}};
     public static ArrayList<String> TrabajosPosibles=new ArrayList(){{add("Obra");add("Reparacion");add("Fontanero");add("Averia");add("Mantenimiento");add("Pintar");}};
     public static int numClientesTecnicos;
             
     public static int generarNumAleatorio()
     {
          Random ram=new Random();
          int numeroRandom=ram.nextInt(5)+1 ;
          System.out.println(numeroRandom);
          return numeroRandom;
     }
     
    
     
     
     public static void generarSistema()
     {
        
        numClientesTecnicos=generarNumAleatorio();
      
         Random ram=new Random();
         int edadRandom;
         //Vamos a  hacer que unos pocos clientes y tecnicos sean premium, el resto seran lites
         
         factoria=(FactoriaAbstracta) new FactoriaLite();
         
         for(int i=0 ;i<numClientesTecnicos/2;i++)
         {
             edadRandom=ram.nextInt(80)+18;
             
                clientesSistemas.add(factoria.crearCliente(nombresPosibles.get(i),edadRandom,DNIPosibles.get(i)));
                clientesSistemas.get(i).crearTrabajo(5000, TrabajosPosibles.get(i), i);
                 
         }
         
          factoria=(FactoriaAbstracta) new FactoriaPremium();
         
          for(int i=numClientesTecnicos/2 ;i<numClientesTecnicos;i++)
         {
             edadRandom=ram.nextInt(80)+18;
            
                clientesSistemas.add(factoria.crearCliente(nombresPosibles.get(i),edadRandom,DNIPosibles.get(i)));
                clientesSistemas.get(i).crearTrabajo(5000, TrabajosPosibles.get(i), i);
                //tecnicosSistemas.add(factoria.crearTecnico(nombresPosibles.get(i), edadRandom, DNIPosibles.get(i), this));   
         }
          
         System.out.println("\n");
        factoria=(FactoriaAbstracta) new FactoriaLite();
         
        for(int i=0 ;i<numClientesTecnicos/2;i++)
        {
            edadRandom=ram.nextInt(80)+18;
            tecnicosSistemas.add(factoria.crearTecnico(nombresPosibles.get(i), edadRandom, DNIPosibles.get(i), trabajosSistemas));  
        }
        
        factoria=(FactoriaAbstracta) new FactoriaPremium();
        for(int i=numClientesTecnicos/2 ;i<numClientesTecnicos;i++)
        {
            edadRandom=ram.nextInt(80)+18;
            tecnicosSistemas.add(factoria.crearTecnico(nombresPosibles.get(i), edadRandom, DNIPosibles.get(i), trabajosSistemas));  
        }
        
          System.out.println("\n");
     }
     
     public static void simulacion()
     {
         generarSistema();
         for(int i=0;i<numClientesTecnicos;i++)
         {
             ((Thread)Sistema.tecnicosSistemas.get(i)).start();
         }
         try{
             Thread.sleep(20*1000);
         } catch(Exception e){
             System.out.println(e);
         }
         
     }
     
     public static void main(String []args)
     {
         simulacion();
         for(int i=0;i<trabajosSistemas.size();i++)
         {
             trabajosSistemas.get(i).ResultadoFinal();
             
         }
             
     }
             
             
}