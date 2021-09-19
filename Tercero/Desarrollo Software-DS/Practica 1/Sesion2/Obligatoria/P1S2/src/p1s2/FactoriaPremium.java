package p1s2;

import java.util.ArrayList;

public class FactoriaPremium extends FactoriaAbstracta {

       @Override
    public clientePremium crearCliente(String n, int e, String dni) {
        return new clientePremium(n,e,dni);
    }

    @Override
    public tecnicoPremium crearTecnico(String n, int e, String dni, ArrayList<trabajo> trabajos) {
        return new tecnicoPremium(n,e,dni,trabajos);
    }
}