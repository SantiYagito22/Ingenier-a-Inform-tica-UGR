package Practica3;

import agents.LARVAFirstAgent;
import jade.core.AID;
import jade.lang.acl.ACLMessage;
import jade.lang.acl.MessageTemplate;
import java.util.*;
import swing.LARVADash;


public class TieFighter extends LARVAFirstAgent{

    enum Status {
        CHECKIN, CHECKOUT, WAIT, COMISSIONING, JOINSESSION, SOLVEPROBLEM, CLOSEPROBLEM, EXIT
    }
    Status mystatus;
    String service = "PManager", 
            problemManager = "", content, sessionKey, sessionManager, storeManager,
            sensorKeys;
    int width, height, maxFlight,x ,y,posxAct,posyAct,poszAct;
    ACLMessage open, session, destroyer;
    int [] jedi = new int [2]; // Coordenadas x e y donde se encuentra el jedi
    final String password = "KILO";
    
    int energy = 3500;
    int anguloActual = 0;
    int alturaActual=0;
    
    int alturaRecargar=0;
    boolean recargando = false;
   
    List<ArrayList<Double>> casillasBucle = new ArrayList<>(); //Vector de las casillas que provocan bucle
    List<ArrayList<Integer>>  vectorLidar= new ArrayList<>();  
   
    String[] contentTokens, coordsInicio,
            mySensors = new String[] {
                "GPS",
                "COMPASS",
                "THERMALHQ",
                "LIDAR"
            };
    boolean step = true;

    
    /**
    * Comprobar si es necesario recargar la energía del agente
    * @param altitude la altituda la que se encuentra el agente
    * @param energy energía que tiene el agente
    * @author Amanda Moyano Romero
    */
    public boolean needRecharge(int altitude, double energy){
        
        if(altitude == 0)
            return (energy <= mySensors.length);
        else
            return (energy <= (altitude/5) + mySensors.length);
        
    }
    
    
    /**
    * El agente realizará una acción
    * @param action acción que deberá realizar al agente
    * @author Amanda Moyano Romero
    */
    
    public boolean act(String action){
        
        session = session.createReply();
        session.setContent("Request execute "+action+" session "+sessionKey);
        session.setPerformative(ACLMessage.REQUEST);
        this.LARVAsend(session);
        session = this.LARVAblockingReceive();
        if (session.getContent().startsWith("Refuse") || session.getContent().startsWith("Failure")) {
            Alert("Executing action failed due to " + session.getContent());
            
            updateSensors();
            return false;
        }
        
        energy --;
        if(!recargando)
            recargar();
        
        return true;
    }
    
 

     /**
    * Comprueba si hay que recargar el agente, y si es que sí, solicita recarga al agente Destroyer
    * @param energy energía del agente
    * @param altitude altitud del agente respecto al suelo
    * @author Amanda Moyano Romero
     */
    public void recargar(){
        
        if (needRecharge(alturaRecargar, energy)) {
            destroyer = new ACLMessage();
            destroyer.addReceiver(new AID(DFGetAllProvidersOf("DESTROYER "+password).get(0), AID.ISLOCALNAME));
            destroyer.setPerformative(ACLMessage.QUERY_IF);
            destroyer.setContent("RECHARGE");
            destroyer.setInReplyTo("MOVE " + posxAct + " " + y + " " + poszAct);
            destroyer.setSender(this.getAID());
            destroyer.setConversationId(sessionKey);
            this.LARVAsend(destroyer);

            destroyer = this.LARVAblockingReceive();

            if (destroyer.getPerformative() == ACLMessage.CONFIRM) {
                recargando = true;
                
                updateSensors();
                int altitude = myDashboard.getLidar()[5][5];
                int altitud_actual = altitude;
                while (altitude != 0) {
                    act("DOWN");
                    altitude -= 5;
                }

                act("RECHARGE");
                energy = 3500;
                Info("Tiefighter recargado");
                recargando = false;

                while (altitude != altitud_actual) {
                    act("UP");
                    altitude += 5;
                }

            }
        }
    }
  
    @Override
    public void setup() {
        super.setup();
        logger.onOverwrite();
        logger.setLoggerFileName("mylog.json");
        Info("Setup and configure agent");
        mystatus = Status.CHECKIN;
        exit = false;
        this.myDashboard = new LARVADash(this);
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
            case WAIT:
                mystatus = MyWait();
                break;
            case COMISSIONING:
                mystatus = MyComissioning();
                break;
            case JOINSESSION:
                mystatus = MyJoinSession();
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
        if (this.AMSIsConnected(this.sessionManager) && this.isCheckedin()) {
            this.MyCheckout();
        }
        super.takeDown();
    }

    public Status MyCheckin() {
        Info("Loading passport and checking-in to LARVA");
        if (!loadMyPassport("passport/MyPassport.passport")) {
            Error("Unable to load passport file");
            return Status.EXIT;
        }
        if (!doLARVACheckin()) {
            Error("Unable to checkin");
            return Status.EXIT;
        }
        return Status.WAIT;
    }
    
    /**
    * Espera del agente hasta ser reclutado o no.
    * @author Santiago Muñoz Castro
    */

    public Status MyWait() {
        
        this.DFSetMyServices(new String[] {"FIGHTER "+password});
        
        open=this.LARVAblockingReceive();
        
        String parse[] = open.getContent().split(" ");
        
        
        outbox = open.createReply();
        sessionKey=open.getConversationId();
        outbox.setPerformative(ACLMessage.AGREE);
        outbox.setInReplyTo("RECRUITMENT "+password);
        this.LARVAsend(outbox);
     
        open = this.LARVAblockingReceive();
        
        if(open.getPerformative() == ACLMessage.ACCEPT_PROPOSAL){
            content = open.getContent();
            coordsInicio= content.split(" ");
            x=Integer.parseInt(coordsInicio[0]);
            y=Integer.parseInt(coordsInicio[1]);
            return Status.COMISSIONING;
        }
        else if(open.getPerformative() == ACLMessage.REJECT_PROPOSAL){
            return Status.CHECKOUT;
        }
        
        return Status.CHECKOUT;
    }


    public Status MyCloseProblem() {
        outbox = open.createReply();
        outbox.setContent("Cancel session " + sessionKey);
        Info("Closing problem, session " + sessionKey);
        this.LARVAsend(outbox);
        inbox = LARVAblockingReceive();
        Info(problemManager + " says: " + inbox.getContent());
        return Status.CHECKOUT;
    }

    public Status MyCheckout() {
        
        
        this.doLARVACheckout();
        return Status.EXIT;
    }
    
    public Status MyComissioning() {
        

        String localService="STORE "+sessionKey;
        
        if(this.DFGetAllProvidersOf(localService).isEmpty()) {
            Error("Service STORE is down");
            return Status.CHECKOUT;
        }
        storeManager = this.DFGetAllProvidersOf(localService).get(0);
        Info("Found store manager " + storeManager);
        
        AID sM=new AID(storeManager, AID.ISLOCALNAME);
        MessageTemplate t= MessageTemplate.MatchSender(sM);
        sensorKeys="";
        for (String s: mySensors) {
            outbox = new ACLMessage();
            outbox.setSender(this.getAID());
            outbox.addReceiver(new AID(storeManager, AID.ISLOCALNAME));
            outbox.setContent("Request product "+s+ " session "+sessionKey);
            outbox.setPerformative(ACLMessage.REQUEST);
            this.LARVAsend(outbox);
            inbox = this.LARVAblockingReceive(t);
            if (inbox.getContent().startsWith("Confirm")) {
                Info("Bought sensor "+s);
                sensorKeys += inbox.getContent().split(" ")[2]+" ";
            } else {
                this.Alert("Sensor "+s+" could not be obtained");
                return Status.CLOSEPROBLEM;
            }
        }
        Info("Bought all sensor keys"+sensorKeys); 
        
        
        return Status.JOINSESSION;
    }
    
    // ENTRAMOS EN LA SESIÓN CON LOS SENSORES Y OBTENEMOS LA INFORMACIÓN DEL MUNDO
    public Status MyJoinSession() {
        
      
        
        String localService="SESSION MANAGER "+sessionKey;
        
        if(this.DFGetAllProvidersOf(localService).isEmpty()) {
            Error("Session MANAGER is down");
            return Status.CLOSEPROBLEM;
        }
        
        sessionManager = this.DFGetAllProvidersOf(localService).get(0);
       
        Info("Found session manager " + sessionManager);
        
        AID sM=new AID(sessionManager, AID.ISLOCALNAME);
        MessageTemplate t= MessageTemplate.MatchSender(sM);
        
        session=new ACLMessage();
        session.setSender(this.getAID());
        session.addReceiver(new AID(sessionManager,AID.ISLOCALNAME));
        session.setContent("Request join session "+sessionKey+ " as Fighter at "+x+" "+y+" attach sensors "+sensorKeys);
        session.setConversationId(sessionKey);
        session.setPerformative(ACLMessage.REQUEST);
        
        this.LARVAsend(session);
        
        session = this.LARVAblockingReceive(t);
        
        String parse[] = session.getContent().split(" ");
         
        Info(session.getContent());
        if (session.getPerformative() == ACLMessage.CONFIRM) {
            outbox = new ACLMessage();
            outbox.setSender(this.getAID());
            outbox.addReceiver(new AID(DFGetAllProvidersOf("DESTROYER "+password).get(0), AID.ISLOCALNAME));
            outbox.setPerformative(ACLMessage.INFORM);
            outbox.setInReplyTo("TAKEOFF");
            outbox.setContent(x + " " + y);
            posxAct=x;
            posyAct=y;
            this.LARVAsend(outbox);
            return Status.SOLVEPROBLEM;
        }
        else{
            Alert("Error joining session: "+open.getContent());
            return Status.CLOSEPROBLEM;
        }

        
        
    }
    
    // ACTUALIZAMOS LOS SENSORES
    public boolean updateSensors() {
        session = session.createReply();
        session.setContent("Query sensors session "+sessionKey);
        session.setPerformative(ACLMessage.QUERY_REF);
        this.LARVAsend(session);
        session = this.LARVAblockingReceive();
        if (session.getContent().startsWith("Refuse") ||
                session.getContent().startsWith("Failure")) {
            Alert ("Reading of sensors failed due to "+session.getContent());
            return false;
        }
        
        energy -= 4;
        return true;
    }


    public void showInfo(double gps[], double angular, double distance, int altitude, double energy)
    {
        Info("Reading of GPS\nX="+gps[0]+" Y="+gps[1]+" Z="+gps[2]);
        Info("Reading of angular= "+angular+"º");
        Info("Reading of distance= "+distance+"m");
        Info("Reading of altitude= "+altitude+"m");
        Info("Reading of energy= "+energy+"W");
       
    }

    
    public void inicializarVectorLidar(){
        
        ArrayList<Integer> v1 = new ArrayList<>(Arrays.asList(4,4));
        ArrayList<Integer> v2 = new ArrayList<>(Arrays.asList(5,4));
        ArrayList<Integer> v3 = new ArrayList<>(Arrays.asList(6,4));
        ArrayList<Integer> v4 = new ArrayList<>(Arrays.asList(6,5));
        ArrayList<Integer> v5 = new ArrayList<>(Arrays.asList(6,6));
        ArrayList<Integer> v6 = new ArrayList<>(Arrays.asList(5,6));
        ArrayList<Integer> v7 = new ArrayList<>(Arrays.asList(4,6));
        ArrayList<Integer> v8 = new ArrayList<>(Arrays.asList(4,5));
        
        
        vectorLidar.add(v1);
        vectorLidar.add(v2);
        vectorLidar.add(v3);
        vectorLidar.add(v4);
        vectorLidar.add(v5);
        vectorLidar.add(v6);
        vectorLidar.add(v7);
        vectorLidar.add(v8);
    
   
    }
    
    /**
    * Que suba el tie hasta la altura indicada
    * @author Santiago Muñoz Castro
    */
    
    public void subirHasta(int x){
        updateSensors();
        alturaActual=  (int)myDashboard.getGPS()[2];
        alturaRecargar = myDashboard.getLidar()[5][5];
      
       while(alturaActual != x)
        {
            
            act("UP");
            alturaActual+=5;
            alturaRecargar+=5;
        }
        
        poszAct=alturaActual;
        informarPosicion(posxAct,posyAct,poszAct);
    }
    
    /**
    * Informar al destroyer de que ha llegado a las posiciones
    * @author Santiago Muñoz Castro
    */
    
    public void informarPosicion(int x, int y , int z){
        
        destroyer = new ACLMessage();
        destroyer.setPerformative(ACLMessage.INFORM);
        destroyer.setContent("MOVE "+x+" "+y+" "+z);
        destroyer.setInReplyTo("MOVE "+x+" "+y+" "+z);
        destroyer.setConversationId(sessionKey);
        destroyer.setSender(this.getAID());
        destroyer.addReceiver(new AID(DFGetAllProvidersOf("DESTROYER "+password).get(0), AID.ISLOCALNAME));

        this.LARVAsend(destroyer);
    }
    
     
    /**
    * Funcion que recibe ordenes de movimiento del destroyer
    * @author Santiago Muñoz Castro
    */
    
    public boolean recibirMovimiento(){
        
        MessageTemplate t = MessageTemplate.MatchSender(new AID(DFGetAllProvidersOf("DESTROYER "+password).get(0), AID.ISLOCALNAME));
        open = this.LARVAblockingReceive(t);
        
        if(open.getPerformative() == ACLMessage.REQUEST){
           String parse[] = open.getContent().split(" ");
           int x= (int)Double.parseDouble(parse[1]);
           int y= (int)Double.parseDouble(parse[2]);
           int z= (int)Double.parseDouble(parse[3]);
           destroyer=new ACLMessage();
           destroyer.setSender(getAID());
           destroyer.addReceiver(new AID(DFGetAllProvidersOf("DESTROYER "+password).get(0), AID.ISLOCALNAME));
           destroyer.setPerformative(ACLMessage.AGREE);
           destroyer.setInReplyTo("MOVE "+x+" "+y+" "+z);
           destroyer.setConversationId(sessionKey);
           this.LARVAsend(destroyer);
           moverseHacia(x,y,z);
           return true;
        }
        Info("HE PASADO DEL REQUEST Y ME HA LLEGADO"+open.getContent());
        if(open.getPerformative() == ACLMessage.CANCEL)
        {
            
            return false;
        }
        
        return false;
    }
    
    /**
    * Tie hace cuatro usos del thermal y busca a los jedis si los encuentra se los pasa al destroyer
    * @author Santiago Muñoz Castro
    * @author Lucía Salamanca López
    */
    public void checkJedis(int y,boolean sube){

        int numChecks=0;
        while(numChecks !=4)
        {
            if(anguloActual== 315 || anguloActual==45 || anguloActual==135 || anguloActual==225)
            {
                updateSensors();
                int thermal[][] = myDashboard.getThermal();
                int inicio_i = 0, inicio_j = 0, fin_i = 0, fin_j = 0; 
                
                switch(anguloActual){
                    case 315:
                        inicio_i = 10;
                        fin_i = thermal.length;
                        inicio_j = 10;
                        fin_j = thermal[0].length;
                        break;
                    
                    case 45:
                        inicio_i = 0;
                        fin_i = 11;
                        inicio_j = 10;
                        fin_j = thermal[0].length;
                        break;
                        
                    case 135:
                        inicio_i = 0;
                        fin_i = 11;
                        inicio_j = 0;
                        fin_j = 11;
                        break;
                        
                    case 225:
                        inicio_i = 10;
                        fin_i = thermal.length;
                        inicio_j = 0;
                        fin_j = 11;
                        break;
                }
            
               
                for (int i=inicio_i; i<fin_i; i++) {
                    for (int j=inicio_j; j<fin_j; j++){
                        if(thermal[i][j]==0)
                        {
                            int xJedi=j-10 + (int) myDashboard.getGPS()[0];
                            int yJedi=i-10 + (int) myDashboard.getGPS()[1];
                            destroyer = new ACLMessage();
                            destroyer.addReceiver(new AID(DFGetAllProvidersOf("DESTROYER "+password).get(0), AID.ISLOCALNAME));
                            destroyer.setPerformative(ACLMessage.INFORM_REF);
                            destroyer.setContent("FOUND "+xJedi+" "+yJedi);
                            destroyer.setInReplyTo("MOVE "+posxAct+" "+y+" "+poszAct);
                            destroyer.setConversationId(sessionKey);
                            destroyer.setSender(this.getAID());
                            destroyer.setOntology("COMMITMENT");
                            this.LARVAsend(destroyer);
                        }
                    }
               
                }
                numChecks++;
            }
            
             act("LEFT");
             anguloActual=(anguloActual+45) % 360;
        }
        
        
        if(sube)
        {
            while(anguloActual!=270)
            {
              act("LEFT");
              anguloActual=(anguloActual+45) % 360;

            }
        }
        else{
            while(anguloActual!=90)
            {
              act("LEFT");
              anguloActual=(anguloActual+45) % 360;
            }
        }  
    }
    
    
    /**
    * Que se mueva el jedi en Y haciendo los chequeos correspondientes con thermal
    * @author Santiago Muñoz Castro
    */
    
    public void moverseHastaY(int y,boolean sube){
       int cont=0;
       Boolean checkJedis=true;
       while(posyAct != y)
        {   
            if(checkJedis)
            {
                checkJedis(y,sube);
                checkJedis=false;
            }

            act("MOVE");
            if(sube) posyAct++;
            else posyAct--;
            
            cont++;
            if(cont==20){
                checkJedis=true;
                cont=0;
            }
        }
       checkJedis(y,sube);
        
        informarPosicion(posxAct,posyAct,poszAct);
    }
    /**
    * Que se mueva el jedi en X 
    * @author Santiago Muñoz Castro
    */
    
    public void moverseHastaX(int x,boolean derecha){
        
        
        if(derecha)
        {
            while(anguloActual!=0)
            {
              act("LEFT");
              anguloActual=(anguloActual+45) % 360;
            }
        }
        else{
            while(anguloActual!=180)
            {
              act("LEFT");
              anguloActual=(anguloActual+45) % 360;
            }
        }
        
       
       while(posxAct != x)
       {
            act("MOVE");
            if(derecha) posxAct++;
            else posxAct--;
       }
       
        
        informarPosicion(posxAct,posyAct,poszAct);
    }

    
    /**
    * Funcion que invoca los movimientos necesarios para ir a la posicion indicada
    * @author Santiago Muñoz Castro
    */
    
    public void moverseHacia(int x, int y, int z)
    {
        Info("RECIBO "+x+ " "+y+" "+z);
        Info("MISPOS 2 "+posxAct+ " "+posyAct+" "+poszAct);
        if(x==posxAct && y==posyAct && z>0)
        {
            subirHasta(z);
        }
        else if(x==posxAct && y!=posyAct && z==poszAct)
        {
            if(y>=posyAct)
            {
                
                moverseHastaY(y,true);
            }
            else{
                moverseHastaY(y,false);
            }
            
        }
        else if(x!=posxAct && y==posyAct && z==poszAct)
        {
            if(x>=posxAct)
            {  
                moverseHastaX(x,true);
            }
            else{
                moverseHastaX(x,false);
            }
            
        }
    }
    
    
    public Status MySolveProblem() {
        
        Boolean sigue=true;
        while(sigue)
        {
            sigue=recibirMovimiento();
            
        }
      
        //Info(Integer.toString(alturaActual));
        
        return Status.CHECKOUT;      
    }

}
