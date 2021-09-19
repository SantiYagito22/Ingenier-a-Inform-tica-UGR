package p1s2;

import java.util.ArrayList;

public class FactoriaLite extends FactoriaAbstracta {

    @Override
    public clienteLite crearCliente(String n, int e, String dni) {
        return new clienteLite(n,e,dni);
    }

    @Override
    public tecnico crearTecnico(String n, int e, String dni, ArrayList<trabajo> trabajos) {
        return new tecnicoLite(n,e,dni,trabajos);
    }

        

}