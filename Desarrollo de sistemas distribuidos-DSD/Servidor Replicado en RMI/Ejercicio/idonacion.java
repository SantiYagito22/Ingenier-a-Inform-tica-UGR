//Define la Interfaz remota
import java.rmi.Remote;
import java.rmi.RemoteException;
import java.util.ArrayList;

public interface idonacion extends Remote {

    
public String registro(String usuario,String contraseña) throws RemoteException;
public boolean iniciarSesion(String usuario,String contraseña) throws RemoteException;
public int getEntidadesRegistradas() throws RemoteException;
public boolean comprobarRegistro(String usuario) throws RemoteException;
public void donar(String usuario,int cantidad) throws RemoteException;
public Boolean comprobarDonacion(String usuario) throws RemoteException;
public int getDineroReplica() throws RemoteException;
public int getDineroDonado(String usuario) throws RemoteException;
public int getTotal(String usuario, ArrayList<idonacion> replicas) throws RemoteException;
public void eliminarCuenta(String usuario) throws RemoteException;


}
