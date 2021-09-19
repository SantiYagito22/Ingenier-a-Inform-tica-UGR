/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package sosemado;
import GUI.GUIPujador;
import GUI.GUIGrafica;
import GUI.GUITecnico;
/**
 *
 * @author yagoe
 */
public class Sosemado {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        Trabajo trabajo1=new Trabajo(10000);
        Cliente cliente1=new Cliente(trabajo1);
        
        GUIPujador tecPujador=new GUIPujador(trabajo1);
        GUITecnico tecnico=new GUITecnico();
        GUIGrafica grafica=new GUIGrafica();
        
        trabajo1.addObserver(tecPujador);
        trabajo1.addObserver(tecnico);
        trabajo1.addObserver(grafica);
        
        Thread hebra=new Thread(trabajo1);
        Thread hebraCliente=new Thread(cliente1);
        hebra.start();
        hebraCliente.start();
        
    }
    
}
