package p1s2;

import java.util.ArrayList;

public abstract class FactoriaAbstracta {

	public abstract cliente crearCliente(String n, int e, String dni);
        
        public abstract tecnico crearTecnico(String n, int e, String dni,  ArrayList<trabajo> trabajos);

}