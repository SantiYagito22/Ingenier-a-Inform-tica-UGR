package sosemado;
import java.util.Random;
import java.util.Observable;
import java.util.concurrent.ThreadLocalRandom;


 
public class Trabajo extends java.util.Observable implements Runnable {
	private float oferta;
        
       

        public Trabajo(float ofertaInicial){
                oferta=ofertaInicial;
        }
        
        
	public float getOferta() {
		return this.oferta;
	}

	public void setOferta(float aNuevaOferta) {
		this.oferta = aNuevaOferta;
                setChanged();
                notifyObservers(aNuevaOferta);
	}
        
         @Override
	public void run(){
        Random ram=new Random();
        while(true)
        {
        float ofertaRandom = (oferta-100) + ram.nextFloat() * ((oferta) - (oferta-100));
        if(ofertaRandom<=20)
        {
            ofertaRandom=20;
        }
        this.setOferta(ofertaRandom);
              try {
                //Ponemos a "Dormir" el programa durante los s que queremos
                Thread.sleep(5*1000);
             } catch (Exception e) {
                System.out.println(e);
             }
        } 
        }
}