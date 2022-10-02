
package Practica3;

import appboot.LARVABoot;
import crypto.Keygen;


public class Practica3 {
    public static void main(String[] args) {
        LARVABoot connection = new LARVABoot();
        connection.Boot("isg2.ugr.es", 1099);
        connection.launchAgent("TF1", TieFighter.class);
        //connection.launchAgent("C1"+Keygen.getHexaKey(4), Corellian.class);
        //connection.launchAgent("C2"+Keygen.getHexaKey(4), Corellian.class);
        connection.launchAgent("DC1", DestroyerCommand.class);
        connection.launchAgent("TF2", TieFighter.class);
        connection.launchAgent("C1", Corellian.class);
        connection.launchAgent("C2", Corellian.class);
        //connection.launchAgent("C1", Corellian.class);
        connection.WaitToShutDown();
       
    }
    
}
