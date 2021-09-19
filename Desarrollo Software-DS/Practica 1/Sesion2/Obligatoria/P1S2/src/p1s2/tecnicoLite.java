package p1s2;

import java.util.ArrayList;
import java.util.Random;

public class tecnicoLite extends tecnico {

    
    public static Boolean gastosTransporte=true;
    
    public tecnicoLite(String n, int e, String dni,  ArrayList<trabajo> trabajos) {
        super(n, e, dni, trabajos);
    }
    
    @Override
	public void run(){
        Random ram=new Random();
        int cont=ram.nextInt(3) +1;
        while(cont!=0)
        {
        int numTrb= ram.nextInt(trabajos.size());
        float ofertaRandom = (trabajos.get(numTrb).getOferta()-500) + ram.nextFloat() * ((trabajos.get(numTrb).getOferta()) - (trabajos.get(numTrb).getOferta()-500));
        if(ofertaRandom<=20)
        {
            ofertaRandom=20;
            cont=0;
        }
        System.out.println("El tecnico LITE "+nombre+" realiza una puja al trabajo con id "+ trabajos.get(numTrb).num_trabajo+" de "+ ofertaRandom);
        trabajos.get(numTrb).pujar(ofertaRandom, this,gastosTransporte);
              try {
                //Ponemos a "Dormir" el programa durante los s que queremos
                Thread.sleep(2*1000);
             } catch (Exception e) {
                System.out.println(e);
             }
            cont--;
        } 
        
        
        }
}