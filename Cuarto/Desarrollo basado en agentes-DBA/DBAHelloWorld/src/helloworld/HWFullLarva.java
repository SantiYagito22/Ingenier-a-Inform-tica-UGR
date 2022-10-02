/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package helloworld;

import agents.LARVAFirstAgent;
import jade.core.AID;
import jade.lang.acl.ACLMessage;

public class HWFullLarva extends LARVAFirstAgent {

    enum Status {
        CHECKIN, CHECKOUT, OPENPROBLEM, SOLVEPROBLEM, CLOSEPROBLEM, EXIT
    }
    Status mystatus;
    String service = "PManager", problem = "HelloWorld",
            problemManager = "", content, sessionKey, sessionManager;
    ACLMessage open, session;
    String[] contentTokens;
    boolean step = true;

    @Override
    public void setup() {
        super.setup();
        // AUDIT 1: 
        // Allow/disallow log outputs on screen. Default true
        //logger.setEcho(true);
        
        // Sets the output of the agent in tabular format with the name of the agent
        // the date and the output. This allows to have a timestamped output to identify
        // who is sending something to the output
        // logger.onTabular();
        

        // AUDIT 2: Write a detailed record on disk
        // Overwrite/Append log files on disk. Default overwrite
        logger.onOverwrite();
        // It allows writing all logs on disk
         logger.setLoggerFileName("mylog.json");
        // logger.onAppend();
        
        // AUDIT 3: Activate this only upon teacher's request because it produces a high traffic in the
        // network, but could give you full details of your own progress
        this.enableDeepLARVAMonitoring();
        
        Info("Setup and configure agent");
        mystatus = Status.CHECKIN;
        exit = false;
    }

    @Override
    public void Execute() {
        Info("Status: " + mystatus.name());
        if (step) {
            step = this.Confirm("The next status will be " + mystatus.name() + "\n\nWould you like to continue step by step?");
        }
        switch (mystatus) {
            case CHECKIN:
                mystatus = MyCheckin();
                break;
            case OPENPROBLEM:
                mystatus = MyOpenProblem();
                break;
            case SOLVEPROBLEM:
                mystatus = MySolveProblem();
                break;
            case CLOSEPROBLEM:
                mystatus = MyCloseProblem();
                break;
            case CHECKOUT:
                mystatus = MyCheckout();
                break;
            case EXIT:
            default:
                exit = true;
                break;
        }
    }

    @Override
    public void takeDown() {
        Info("Taking down and deleting agent");
        // AUDIT 4: Save sequence diagram on disk
        this.saveSequenceDiagram("./" + this.problem + ".seqd");
        super.takeDown();
    }

    public Status MyCheckin() {
        Info("Loading passport and checking-in to LARVA");
        if (!loadMyPassport("MyPassport.passport")) {
            Error("Unable to load passport file");
            return Status.EXIT;
        }
        if (!doLARVACheckin()) {
            Error("Unable to checkin");
            return Status.EXIT;
        }
        return Status.OPENPROBLEM;
    }

    public Status MyOpenProblem() {
        if (this.DFGetAllProvidersOf(service).isEmpty()) {
            Error("Service PMANAGER is down");
            return Status.CHECKOUT;
        }
        problemManager = this.DFGetAllProvidersOf(service).get(0);
        Info("Found problem manager " + problemManager);
        this.outbox = new ACLMessage();
        outbox.setSender(getAID());
        outbox.addReceiver(new AID(problemManager, AID.ISLOCALNAME));
        outbox.setContent("Request open " + problem);
        this.LARVAsend(outbox);
        Info("Request opening problem " + problem + " to " + problemManager);
        open = LARVAblockingReceive();
        Info(problemManager + " says: " + open.getContent());
        content = open.getContent();
        contentTokens = content.split(" ");
        if (contentTokens[0].toUpperCase().equals("AGREE")) {
            sessionKey = contentTokens[4];
            session = LARVAblockingReceive();
            sessionManager = session.getSender().getLocalName();
            Info(sessionManager + " says: " + session.getContent());
            return Status.CLOSEPROBLEM;
        } else {
            Error(content);
            return Status.CHECKOUT;
        }
    }

    public Status MySolveProblem() {
        return Status.CLOSEPROBLEM;
    }

    public Status MyCloseProblem() {
        outbox = open.createReply();
        outbox.setContent("Cancel session " + sessionKey);
        Info("Closing problem Helloworld, session " + sessionKey);
        this.LARVAsend(outbox);
        inbox = LARVAblockingReceive();
        Info(problemManager + " says: " + inbox.getContent());
        return Status.CHECKOUT;
    }

    public Status MyCheckout() {
        this.doLARVACheckout();
        return Status.EXIT;
    }

}
