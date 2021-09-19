
//Código del cliente
import java.net.MalformedURLException;
import java.rmi.registry.LocateRegistry;
import java.rmi.*;
import java.rmi.registry.Registry;
import java.util.Scanner;
import java.util.ArrayList;

public class cliente {

    public static void main(String[] args) {

        int numReplica = 0; // Número de replica en el que se ha registrado el cliente, inicialmente esta a 0, es decir, no pertenece a ninguno
        boolean identificado = false;
        String nombreUsuario, contraseña;

        Scanner entradaTeclado = new Scanner(System.in);

        // Crea e instala el gestor de seguridad
        if (System.getSecurityManager() == null) {
            System.setSecurityManager(new SecurityManager());
        }

        try {

            
            Registry mireg = LocateRegistry.getRegistry("127.0.0.1",1099);
            ArrayList<idonacion> replicas=new ArrayList<idonacion>();

            for(int i=1;i<4;i++)
            {
                // Crea el stub para el cliente especificando el nombre de la replica
                String nombreReplica="mmireplica"+i;
                idonacion replica = (idonacion) mireg.lookup(nombreReplica);
                replicas.add(replica);
            }
            
           
            System.out.println("¡Bienvenido!, antes de empezar a donar debe registrarse en el sistema\n");

            do{
            System.out.println("Eliga una opción: \n 1-Iniciar Sesión\n 2-Registrarse\n");

            
            int opcion = 0;
            do {
                System.out.print("Opcion: ");
                opcion = entradaTeclado.nextInt();
                if (opcion != 1 && opcion != 2) {
                    System.out.println("\nOpcion introducida incorrecta, pruebe con 1 para iniciar sesion o 2 para registrase\n");
                }

            } while (opcion != 1 && opcion != 2);

            
                
            System.out.print("\nIntroduzca su nombre de usuario: ");
            nombreUsuario = entradaTeclado.next();
            System.out.print("\nIntroduzca su contraseña: ");
            contraseña = entradaTeclado.next();


            if(opcion==2)
            {

                boolean sePuedeRegistrar=true;


                for(int i=0;i<replicas.size() && sePuedeRegistrar;i++)
                {
                    if(replicas.get(i).comprobarRegistro(nombreUsuario) )
                    {
                        sePuedeRegistrar=false;
                        System.out.println("\nEl usuario "+nombreUsuario+" ya se encuentra registrado en el servidor replica 1 \n");
                    }
                }
              
                if(sePuedeRegistrar)
                {
                    int minimo=100;
                    for(int i=0;i<replicas.size();i++)
                    {
                        if(replicas.get(i).getEntidadesRegistradas()<minimo)
                        {
                            numReplica=i;
                            minimo=replicas.get(i).getEntidadesRegistradas();
                        }
                            
                    }
                    
                    System.out.println(replicas.get(numReplica).registro(nombreUsuario, contraseña));
                    identificado=true;
                     
                }
                
            }


            
            if(opcion==1)
            {
               

                for(int i=0;i<replicas.size() ;i++)
                {
                    if(replicas.get(i).iniciarSesion(nombreUsuario,contraseña))
                    {
                        numReplica=i;
                        System.out.println("\nInicio de sesión completado \n");
                        identificado=true;
                    }
                }
                if(!identificado)
                    System.out.println("\nNo se encuentra registrado en el sistema o el nombre de usuario y contraseña son incorrectos\n");   

            }
            
            }while(!identificado);
            
            
            boolean salir=false;

            System.out.println("\nHola "+nombreUsuario+"!!!!, bienvenido a nuestro sistema de donaciones.\n");   

            
            
            while(!salir)
            {

                int accion=0;
                
                do{
                System.out.println("\n Nuestras acciones: \n 1-Donar\n 2-Consultar total\n 3-Eliminar Cuenta\n 4-Consultar dinero donado\n 5-Cerrar Sesion\n");
                System.out.print("\nIntroduzca que acción quieres realizar: ");
                accion=entradaTeclado.nextInt();

                if(accion!=1 && accion!=2 && accion!=3 && accion!=4  && accion!=5)
                    System.out.println("\nOpcion introducida incorrecta, pruebe con 1, 2, 3, 4 o 5\n");

                }while(accion!=1 && accion!=2 && accion!=3 && accion!=4 && accion!=5 );

                if(accion==1)
                {   
                    int cantidad=0;
                    do{
                        System.out.print("\nIntroduzca la cantidad a donar: ");
                        cantidad=entradaTeclado.nextInt();
                        if(cantidad<=0)
                        {
                            System.out.println("\nNo puedes donar una cantidad igual a 0 negativa!!!\n");
                        }
                    }while(cantidad<=0);
                    

                    replicas.get(numReplica).donar(nombreUsuario,cantidad);
                    System.out.println("\nHas donado "+cantidad+"€, ¡muchas gracias!\n");
                    
                }
                else if(accion==2)
                {
                    int total=0;
                    
                    total=replicas.get(numReplica).getTotal(nombreUsuario,replicas);
                   

                    if(total==-1)
                    {
                        System.out.println("\nLo sentimos, no puedes consultar el total donado sin haber realizado antes una DONACION\n");
                    }
                    else{
                        System.out.println("\nLa cantidad total donada a nuestro sistema de donaciones es de "+total+"€\n");
                    }
                }
                
                else if(accion==3)
                {
                    
                    replicas.get(numReplica).eliminarCuenta(nombreUsuario);
                    salir=true;
                    System.out.println("\nSe ha eliminado la cuenta con éxito, gracias por confiar en nosotros\n");

                }
                else if(accion==4)
                {
                    int nr=numReplica+1;
                    System.out.println("\nEl dinero que has donado a la replica "+nr+" es de "+replicas.get(numReplica).getDineroDonado(nombreUsuario)+"€\n");
                        
                }
                else if(accion==5)
                {
                    System.out.println("\nMuchas gracias por visitarnos, ¡hasta luego!\n");
                    salir=true;
                }
                
            }
            
          
        } catch (NotBoundException | RemoteException e) {
            System.err.println("Exception del sistema: " + e);
        }

        System.exit(0);
    }
}
