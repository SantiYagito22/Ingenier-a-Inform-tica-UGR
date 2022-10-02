package Practica3;

import agents.LARVAFirstAgent;
import jade.core.AID;
import jade.lang.acl.ACLMessage;
import jade.lang.acl.MessageTemplate;
import java.util.*;
import swing.LARVADash;


public class Corellian extends LARVAFirstAgent{

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
    final String password = "102Batallion";
    
    int alturaActual=0;
    boolean recargando = false;
   
    List<ArrayList<Double>> casillasBucle = new ArrayList<>(); //Vector de las casillas que provocan bucle
    List<ArrayList<Integer>>  vectorLidar= new ArrayList<>();  
   
    String[] contentTokens, coordsInicio,
            mySensors = new String[] {
                "GPS",
                "LIDAR",
                "ENERGY",
                "COMPASS",
                "THERMALHQ",
                "ALIVE",
                "ALTITUDE",
                "DISTANCE"
            };
    boolean step = true;



    /**
    * Guarda las coordenadas donde se encuentra el jedi
    * @param gps coordenadas donde se encuentra el agente
    * @param angular ángulo donde se encuentra el jedi respecto a nuestra posición
    * @param distance distancia a la que se encuentra el jedi
    * @author Lucía Salamanca López
    */
    
    public void whereIsJedi(double gps[], double angular, double distance){

        jedi[0] = (int)Math.round(gps[0]+distance*Math.cos(Math.toRadians(angular)));
        jedi[1] = (int)Math.round(gps[1]-distance*Math.sin(Math.toRadians(angular)));
    
    }

    
    /**
    * Comprueba si la casilla a comprobar ya ha sido visitada
    * @param gpsX coordenada X de donde se 
    * @param gpsY coordenada Y de donde se esta comprobando
    * @author Santiago Muñoz Castro
     * @return boolean
    */
    public boolean checkCasilla(double gpsX,double gpsY)
    {
        Info("Casilla a valorar:"+gpsX+","+gpsY);
        
        for(int i=0;i<casillasBucle.size();i++)
        {
            if(casillasBucle.get(i).get(0)==gpsX && casillasBucle.get(i).get(1)==gpsY)
            {
                Info("NO SE PUEDE");
                return true;
            }
        }
        
        return false;
    }
    
    /**
     * Devuelve la coordenada de la siguiente posición más cercana al jedi
     * @param gps coordenadas donde se encuentra el agente
     * @param jedi coordenadas donde se encuentra el jedi
     * @param lidar matriz con los valores de la distancia del agente al suelo, el valor del agente se encuentra en el lidar[6][6], así que los que hay que comprobar son:
     * 5,5  6,5  7,5            
     * 5,6       7,6
     * 5,7  6,7  7,7
     * @author Jesús Espínola Conde
     * @author Santiago Muñoz Castro
     */

    public int nextStep(int x, int y, double gps[], int lidar[][] )
    {
       
        double actualDistance = (x-gps[0])*(x-gps[0]) + (y-gps[1])*(y-gps[1]);
        double minDistance=Double.MAX_VALUE;
        int [] minCords = new int [] {1,1};
        double nextGpsX=Double.MAX_VALUE, nextGpsY=Double.MAX_VALUE;
        
        ArrayList<Double> cv = new ArrayList<>(Arrays.asList(gps[0],gps[1]));
        casillasBucle.add(cv);
        
        
        /*
        Info("VISITADAS");
        for(int i=0;i<casillasBucle.size();i++)
        {   
            Info("{"+casillasBucle.get(i).get(0)+","+casillasBucle.get(i).get(1)+"}"); 
        }
        */
        
        for(int i=0; i<3;i++)
        {
            for(int j=0;j<3;j++)
            {   
                // Para que no compruebe la casilla del agente
                if (i!=1 || j!=1){
                    
                        double gpsX = gps[0]+j-1;
                        double gpsY = gps[1]+i-1;
                        if(!checkCasilla(gpsX,gpsY))
                        {
                            actualDistance = (x-gpsX)*(x-gpsX) + (y-gpsY)*(y-gpsY);
                            //Info("actualDistance: "+ actualDistance);
                            if (actualDistance < minDistance) {
                                nextGpsX=gpsX;
                                nextGpsY=gpsY;
                                minDistance = actualDistance;
                                minCords[0] = i;
                                minCords[1] = j;
                            }
                        }
                      
                    }
                
            }
        }
        
        if ( gps[2] - (lidar[minCords[0]+4][minCords[1]+4]) > maxFlight  ){
              
            //Info("RODEANDO");
            
            int pos=-1;
            for(int i=0;i<vectorLidar.size() && pos==-1;i++)
            {
                if(vectorLidar.get(i).get(0)==minCords[0]+4 && vectorLidar.get(i).get(1)==minCords[1]+4 )
                {
                    pos=i;
                }
            }
            //Info("POSICION VECTOR LIDAR "+pos);
            
            while(gps[2] - (lidar[vectorLidar.get(pos).get(0)][vectorLidar.get(pos).get(1)]) > maxFlight || checkCasilla(gps[0]+minCords[1]-1,gps[1]+minCords[0]-1)){
                pos++;
                pos%=8;
            }
            
            minCords[0]=vectorLidar.get(pos).get(0)-4;
            minCords[1]=vectorLidar.get(pos).get(1)-4;
           
        }   
        
        
        
        //&& !checkCasilla(gps[0]+minCords[1]-1,gps[1]+minCords[0]-1)
        nextGpsX=gps[0]+minCords[1]-1;
        nextGpsY=gps[1]+minCords[0]-1;
        
        

        //Info("Casilla con menor distancia: X:"+minCords[0]+" Y:"+minCords[1]);

        int coord = -1;
        
        if (minCords[0] == 0){
            if (minCords[1] == 0){
                coord = 135;
            }
            else if (minCords[1] == 1){
                coord = 90;
            }
            else{
                coord = 45;
            }
        }
        else if (minCords[0] == 1){
            if (minCords[1] == 0){
                coord = 180;
            }
            
            else if(minCords[1] == 2){
                coord = 0;
            }
        }
        else if(minCords[0] == 2)
        {
            if (minCords[1] == 0)
            {
                coord = 225;
            }   
            else if(minCords[1] == 1)
            {
                coord = 270;
            }
            else if(minCords[1] == 2)
            {
                coord = 315;
            }
        }
        
        Info("WAISOFNOEIG Coord " + coord);
        return coord;
    }
    
    /**
    * Comprobar si es necesario recargar la energía del agente
    * @param altitude la altituda la que se encuentra el agente
    * @param energy energía que tiene el agente
    * @author Amanda Moyano Romero
    */
    
    public boolean needRecharge(int altitude, double energy){
        
        if(altitude == 0)
            return (energy <= (mySensors.length * 2));
        else
            return (energy <= (altitude * mySensors.length * 10)  );
        
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
        
        if(!recargando)
            recargar();
        
        return true;
    }
    
    
    /**
    * El agente se moverá hacia la siguiente casilla
    * @param coord Dirección a la que se tiene que dirigir el agente
    * @param lidar matriz con los valores de la distancia del agente al suelo
    * @param compass Ángulo en el que se encuentra el agente
    * @author Amanda Moyano Romero
    * @author Lucía Salamanca López
    */
    
    public void moveTo( int coord, int lidar[][], int compass){
        
        int coord_lidar[] =  angleToCoordLidar(coord);  
        
        int cont=0;
        int auxCompass=compass;
        while(coord != auxCompass ){
            auxCompass=(auxCompass+45)%360;
            cont++;
            
        }
        if(cont>=4)
        {
            while(compass != coord){
            act("RIGHT");
            compass = myDashboard.getCompass();
            }
        }
        else
        {
            while(compass != coord){
            act("LEFT");
            compass = myDashboard.getCompass();
            }
        }
        
       
             
        
        String message="";
        for (int y=0; y<lidar.length; y++) {
            for (int x=0; x<lidar[0].length; x++){
                message += String.format("%03d ", lidar[x][y]);
            }
            message += "\n";
        }
        
        lidar = myDashboard.getLidar() ;
        //Info("Altura siguiente: "+lidar[coord_lidar[0]][coord_lidar[1]]);
        //Info(message);

        while(myDashboard.getLidar()[coord_lidar[0]][coord_lidar[1]] < 0){
            
            act("UP");
        }
        
        
        if(myDashboard.getLidar()[coord_lidar[0]][coord_lidar[1]] >= 0)
        {
            act("MOVE");
        }
            
    
    }
    
    /**
    * Devuelve la casilla del lidar que tenemos que mirar en función del ángulo al que nos queremos dirigir
    * @param angle ángulo al que nos queremos dirigir
    * @author Amanda Moyano Romero
    * @author Lucía Salamanca López
     */
    public int[] angleToCoordLidar(int angle){
        
        int x = 4, y = 4;
        
         for(int i=0; i<3;i++)
        {
            for(int j=0;j<3;j++)
            {
                if(myDashboard.getLidar()[i+4][j+4] > 0){
                    x = i+4;
                    y = j+4;
                }
                    
            }
        }
        switch(angle){
            case 0:
                return new int[] {5,6};

            case 45:
                return new int[] {4,6};

            case 90:
                return new int[] {4,5};

            case 135:
                return new int[] {4,4};

            case 180:
                return new int[] {5,4};

            case 225:
                return new int[]{6,4};

            case 270:
                return new int[] {6,5};

            case 315:
                return new int[] {6,6};
                
            case -1:
                return new int[] {x,y};
               
            default:
                return new int[] {5,5};
        }
    }

     /**
    * Comprueba si hay que recargar el agente, y si es que sí, solicita recarga al agente Destroyer
    * @param energy energía del agente
    * @param altitude altitud del agente respecto al suelo
    * @author Amanda Moyano Romero
     */
    public void recargar(){
        
        updateSensors();
        Info("ENERGIIIIIA: " + myDashboard.getEnergy());
        if(needRecharge(myDashboard.getAltitude(), myDashboard.getEnergy())){
            
            destroyer.setPerformative(ACLMessage.QUERY_IF);
            destroyer.setContent("RECHARGE");
            destroyer.setInReplyTo("MOVE "+posxAct+" "+y+" "+poszAct);
            this.LARVAsend(destroyer);

            destroyer = this.LARVAblockingReceive();

            if (destroyer.getPerformative() == ACLMessage.CONFIRM){
                recargando = true;
                
                int altitude = myDashboard.getLidar()[5][5];
                
                while(altitude != 0){
                    act("DOWN");
                    altitude -= 5;
                }
                
                act("RECHARGE");
                Info("Tiefighter recargado");
                recargando = false;
                
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
        
        this.DFSetMyServices(new String[] {"CORELLIAN "+password});
        
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
        session.setContent("Request join session "+sessionKey+ " as Corellian at "+x+" "+y+" attach sensors "+sensorKeys);
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
    * Funcion para capturar a un Jedi
    * @author Amanda Moyano Romero
    */
    
    public void capturarJedi(int x, int y)
    {
        int altitude = myDashboard.getLidar()[5][5];
                
        while(altitude != 0){
                act("DOWN");
                altitude -= 5;
        }
                
        act("CAPTURE");
        
        /*destroyer=new ACLMessage();
        destroyer.setSender(getAID());
        destroyer.addReceiver(new AID(DFGetAllProvidersOf("DESTROYER "+password).get(0), AID.ISLOCALNAME));
        destroyer.setPerformative(ACLMessage.AGREE);
        destroyer.setContent("CAPTURE "+x+" "+y);
        destroyer.setInReplyTo("CAPTURE "+x+" "+y);
        destroyer.setConversationId(sessionKey);

        this.LARVAsend(destroyer);*/
        
    }
    

    
    
     
    /**
    * Recibir órdenes de captura de Destroyer
    * @author Amanda Moyano Romero
    */
    
    public boolean recibirCaptura(){
        
        open = this.LARVAblockingReceive();
        
        if(open.getPerformative() == ACLMessage.REQUEST){
           String parse[] = open.getContent().split(" ");
           int x= Integer.parseInt(parse[1]);
           int y= Integer.parseInt(parse[2]);
           int z = Integer.parseInt(parse[3]);
           destroyer=new ACLMessage();
           destroyer.setSender(getAID());
           destroyer.addReceiver(new AID(DFGetAllProvidersOf("DESTROYER "+password).get(0), AID.ISLOCALNAME));
           destroyer.setPerformative(ACLMessage.AGREE);
           destroyer.setInReplyTo("CAPTURE "+x+" "+y+" "+z);
           destroyer.setConversationId(sessionKey);
           this.LARVAsend(destroyer);
           updateSensors();
           
           inicializarVectorLidar();
            //Mientras la distancia no sea 0, la altura sea mayor que 0 y el agente siga vivo
            while(myDashboard.getDistance() > 0 && myDashboard.getGPS()[2] >= 0 && myDashboard.getAlive()){   
                //obtenemos la orientación a la que se tiene que mover
                int next = nextStep(x, y, myDashboard.getGPS(), myDashboard.getLidar());

                //nos movemos a ese orientación
                moveTo(next, myDashboard.getLidar(), myDashboard.getCompass());

            }
            
            if(myDashboard.getDistance() == 0){
                capturarJedi(x,y);
            }
            
           return true;
        }
        if(open.getPerformative() == ACLMessage.CANCEL)
        {
            return false;
        }
        
        return true;
    }
    
    
    
    public Status MySolveProblem(){
        
        Boolean sigue=true;
        while(sigue)
        {
            sigue=recibirCaptura();
               
        }
        
        
        
        
        //Info(Integer.toString(alturaActual));
        
        return Status.CHECKOUT;      
    }

}
