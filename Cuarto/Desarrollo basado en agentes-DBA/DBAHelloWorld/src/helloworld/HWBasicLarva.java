package helloworld;

import agents.LARVAFirstAgent;

/**
 * Basic agent which shows the main structure of a LARVA Agent
 * - setup()
 * - Execute()
 * - takeDown()
 * The first and third method are provided by JADE, LARVAFirstAgent provides the 
 * Execute() method as a basic repetitive behaviour which ends once the variable 
 * exit is set to true, otherwise it continues executing indefinitedly
 * @author Anatoli Grishenko <Anatoli.Grishenko@gmail.com>
 */
public class HWBasicLarva extends LARVAFirstAgent {

    @Override
    public void setup() {
        super.setup();
        // Loggin info as regular messages
        Info("Setup and configure agent");
        exit = true;
    }

    @Override
    public void Execute() {
        Info("Hello World, I am an agent and my name is " + getLocalName());
        exit = true;
        // This body executes indefinitely, uncomment this to stop at a 
        // given step count        
//        if (this.getNCycles() > 5) {
//            Error("End of repetitions");
//            exit = true;
//        } else
//            exit=false;

    }

    @Override
    public void takeDown() {
        // Regular termination of all agents
        Info("Taking down and deleting agent");
        super.takeDown();
    }
}
