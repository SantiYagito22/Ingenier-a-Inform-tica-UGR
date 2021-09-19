//Implementa la Interfaz remota
import java.rmi.*;
import java.rmi.server.UnicastRemoteObject;
import java.util.ArrayList;
import java.net.MalformedURLException;
import java.rmi.registry.Registry;
import java.rmi.registry.LocateRegistry;

public class donacion extends UnicastRemoteObject implements idonacion {


private int numeroReplica;   
private ArrayList<String> usuariosRegistrados = new ArrayList<String>();
private ArrayList<String> contraseñasRegistradas = new ArrayList<String>();
private ArrayList<Integer> dineroDonado = new ArrayList<Integer>();
private int cantidadRecibida=0;

public donacion( int numReplica ) throws RemoteException {
    this.numeroReplica=numReplica;
}



@Override
public boolean comprobarRegistro(String usuario) throws RemoteException{

    for(int i=0;i<usuariosRegistrados.size();i++)
    {
        if(usuariosRegistrados.get(i).equals(usuario))
        {
            return true;
            
        }
       
    }
    return false;
}

@Override
public String registro(String usuario,String contraseña) throws RemoteException{
    
    usuariosRegistrados.add(usuario);
    contraseñasRegistradas.add(contraseña);
    dineroDonado.add(0);

    return "\nSe ha registrado el usuario "+usuario+" en el servidor replica "+numeroReplica+"\n";

}

@Override
public boolean iniciarSesion(String usuario,String contraseña) throws RemoteException{
    
    for(int i=0;i<usuariosRegistrados.size();i++)
    {
        if(usuariosRegistrados.get(i).equals(usuario) && contraseñasRegistradas.get(i).equals(contraseña))
            return true;
    }
    return false;
}

@Override 
public int getEntidadesRegistradas() throws RemoteException{

    return usuariosRegistrados.size();
}



public int getId(String usuario) throws RemoteException{

    

    for(int i=0 ;i<usuariosRegistrados.size();i++)
    {
        if(usuariosRegistrados.get(i).equals(usuario))
        {

            return i;
        }
    }

    return -1;
}

@Override
public int getDineroDonado(String usuario) throws RemoteException{

    int i=getId(usuario);
    return dineroDonado.get(i);

}


@Override
public void donar(String usuario, int cantidad) throws RemoteException{

    
    int i=getId(usuario);
    dineroDonado.set(i,cantidad+dineroDonado.get(i));
    System.out.println("La replica "+numeroReplica+" ha recibido una donacion de "+cantidad+"€ del usuario "+usuario);
    this.cantidadRecibida+=cantidad;

}

@Override
public Boolean comprobarDonacion(String usuario) throws RemoteException{
    
    int i=getId(usuario);
    if(dineroDonado.get(i)>0)
        return true;
    else 
        return false;
}

@Override
public int getDineroReplica() throws RemoteException{
    return this.cantidadRecibida;
}

@Override
public int getTotal(String usuario,ArrayList<idonacion> replicas) throws RemoteException{

    int total=0;
    if(comprobarDonacion(usuario)){
        
        for(int i=0;i<replicas.size();i++)
        {
            total+=replicas.get(i).getDineroReplica();
        }
    }
    else{
        return -1;
    }

    return total;
}

@Override
public void eliminarCuenta(String usuario) throws RemoteException{
    int i=getId(usuario);
    this.usuariosRegistrados.remove(i);
    this.contraseñasRegistradas.remove(i);
    this.dineroDonado.remove(i);

    
}


}




