
//Código del servidor 
import java.net.MalformedURLException;
import java.rmi.*;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.*;

public class servidorDonacion {
    public static void main(String[] args) {

        // Crea e instala el gestor de seguridad
        if (System.getSecurityManager() == null) {
            System.setSecurityManager(new SecurityManager());
        }

        try {
            // Lanzamos la primera replica del servidor
            //Registry reg=LocateRegistry.createRegistry(1099);
            int numeroReplica=Integer.parseInt(args[0]);
            idonacion replica = new donacion(numeroReplica);
            String nombre="mmireplica"+args[0];
            Naming.rebind(nombre, replica);

            

            System.out.println("Replica "+args[0]+ " online");


            System.out.println("Servidor RemoteException ");

        }catch (Exception e) {
            System.err.println("Exception:");
            e.printStackTrace();
            }
    }

}
