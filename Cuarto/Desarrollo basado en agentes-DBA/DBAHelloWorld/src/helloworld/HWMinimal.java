package helloworld;

import jade.core.Agent;

/**
 * Basic version, 
 * @author Anatoli.Grishenko@gmail.com
 */
public class HWMinimal extends Agent{
    
   
    @Override
    public void setup() {
        System.out.println("Hello World, I am an agent and my name is "+getLocalName());
        doDelete();
    }
    
}
