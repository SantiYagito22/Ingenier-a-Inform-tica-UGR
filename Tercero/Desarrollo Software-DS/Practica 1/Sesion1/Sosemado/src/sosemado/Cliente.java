package sosemado;


import java.util.Observable;
import GUI.GUICliente;
import sosemado.Trabajo;
import java.util.Observer;



public class Cliente extends Thread implements Observer{
	public Trabajo trabajo;
        private GUICliente ventanaCliente;
        
	public void pull(Trabajo aO, Object aArg) {
		throw new UnsupportedOperationException();
	}
        
        public Cliente(Trabajo work)
        {
            ventanaCliente=new GUICliente(work);
            this.trabajo=work;
        }
        
    @Override
        public void update(Observable trabajo, Object oferta){
    
}
    @Override
    public void run() {
        while(true)
        {
              ventanaCliente.setOfertaGUI(trabajo.getOferta());
              try {
                //Ponemos a "Dormir" el programa durante los s que queremos
                Thread.sleep(12*1000);
             } catch (Exception e) {
                System.out.println(e);
             }
        } 
    }
}