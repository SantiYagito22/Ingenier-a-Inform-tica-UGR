package tiefighter;

import agents.LARVAFirstAgent;
import jade.core.AID;
import jade.lang.acl.ACLMessage;
import java.util.*;
import swing.LARVADash;


public class MySecondTieFighter extends LARVAFirstAgent{

    enum Status {
        CHECKIN, CHECKOUT, OPENPROBLEM, COMISSIONING, JOINSESSION, SOLVEPROBLEM, CLOSEPROBLEM, EXIT
    }
    Status mystatus;
    String service = "PManager", problem = "Zeffo",
            problemManager = "", content, sessionKey, sessionManager, storeManager,
            sensorKeys;
    int width, height, maxFlight;
    ACLMessage open, session;
    int [] jedi = new int [2]; // Coordenadas x e y donde se encuentra el jedi
    List<ArrayList<Double>> casillasBucle = new ArrayList<>(); //Vector de las casillas que provocan bucle
    List<ArrayList<Integer>>  vectorLidar= new ArrayList<>();  // Vector con las casillas de la matriz de lidar
   
    String[] contentTokens,
            mySensors = new String[] {
                "ALIVE",
                "GPS",
                "COMPASS",
                "LIDAR",
                "ENERGY",
                "DISTANCE",
                "ANGULAR"
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
    * Comprueba si la casilla ya ha sido visitada
    * @param gpsX coordenada X de la casilla a comprobar
    * @param gpsY coordenada Y de la casilla a comprobar
    * @author Santiago Muñoz Castro
    * @return boolean
    */
    public boolean checkCasilla(double gpsX, double gpsY){
        Info("Se valora la casilla:" + gpsX + "," + gpsY);
        
        for(int i = 0; i < casillasBucle.size(); i++){
            if(casillasBucle.get(i).get(0) == gpsX && casillasBucle.get(i).get(1) == gpsY){
                Info("La casilla está en el bucle");
                return true;
            }
        }
        
        Info("La casilla es válida");
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

    public int nextStep(double gps[], int lidar[][] ){
        whereIsJedi(gps, myDashboard.getAngular(), myDashboard.getDistance());
        double actualDistance = (jedi[0]-gps[0])*(jedi[0]-gps[0]) + (jedi[1]-gps[1])*(jedi[1]-gps[1]); //distancia entre agente y jedi
        double minDistance = Double.MAX_VALUE;
        int [] nextCords = new int [] {1,1}; //coordenadas relativas de la siguiente posición (entre 0 y 2)
        double [] nextGps = {Double.MAX_VALUE, Double.MAX_VALUE}; //coordenadas globales de la siguiente posición
        
        
        ArrayList<Double> cv = new ArrayList<>(Arrays.asList(gps[0],gps[1]));
        casillasBucle.add(cv);
        
        //recorremos las 8 posiciones alrededor de la casilla actual y escogemos la que esté más cerca del jedi
        for(int i = 0; i < 3; i++){
            
            for(int j = 0; j < 3; j++){   
                
                // Para que no compruebe la casilla del agente
                if (i!=1 || j!=1){
                    
                    if(!checkCasilla((gps[0]+j-1),(gps[1]+i-1))){
                        
                        actualDistance = (jedi[0]-(gps[0]+j-1))*(jedi[0]-(gps[0]+j-1)) + (jedi[1]-(gps[1]+i-1))*(jedi[1]-(gps[1]+i-1));
                           
                        if (actualDistance < minDistance){
                            
                            minDistance = actualDistance;
                            nextCords[0] = i;
                            nextCords[1] = j;
                            nextGps[0] = (gps[0]+j-1);
                            nextGps[1] = (gps[1]+i-1);
                        }
                    }  
                }
            }
        }
        
        //si la casilla tiene una altura mayor al vuelo máximo
        if ( gps[2] - (lidar[nextCords[0]+4][nextCords[1]+4]) > maxFlight  ){
          
            int pos=-1;
            
            for(int i=0; i<vectorLidar.size() && pos == -1; i++){
                
                if(vectorLidar.get(i).get(0) == nextCords[0]+4 && vectorLidar.get(i).get(1) == nextCords[1]+4 ){
                    pos = i;
                }
            }

            //giramos hacia la izquierda hasta encontrar una casilla a la que se pueda pasar
            while(gps[2] - (lidar[vectorLidar.get(pos).get(0)][vectorLidar.get(pos).get(1)]) > maxFlight || checkCasilla(gps[0] + nextCords[1] - 1, gps[1] + nextCords[0] - 1)){
                pos++;
                pos %= 8;
            }
            
            nextCords[0] = vectorLidar.get(pos).get(0) - 4;
            nextCords[1] = vectorLidar.get(pos).get(1) - 4;
            nextGps[0] = gps[0] + nextCords[1] - 1;
            nextGps[1] = gps[1] + nextCords[0] - 1;
           
        }   
        
        //Obtenemos la orientación de la casilla siguiente
    
        int coord = -1;
        
        if (nextCords[0] == 0){
            if (nextCords[1] == 0){
                coord = 135;
            }
            else if (nextCords[1] == 1){
                coord = 90;
            }
            else{
                coord = 45;
            }
        }
        else if (nextCords[0] == 1){
            if (nextCords[1] == 0){
                coord = 180;
            }
            
            else if(nextCords[1] == 2){
                coord = 0;
            }
        }
        else if(nextCords[0] == 2){
            if (nextCords[1] == 0){
                coord = 225;
            }   
            else if(nextCords[1] == 1){
                coord = 270;
            }
            else if(nextCords[1] == 2){
                coord = 315;
            }
        }
        
        Info("La siguiente casilla es: " + nextGps[0] + ", " + nextGps[1] + "con orientación de: " + coord);
        return coord;
    }
    
    /**
    * Comprobar si es necesario recargar la energía del agente
    * @param lidar matriz con los valores de la distancia del agente al suelo
    * @param energy energía que tiene el agente
    * @author Amanda Moyano Romero
    */
    
    public boolean needRecharge(int lidar[][], double energy){
        
        if(lidar[5][5] == 0)
            return (energy <= (mySensors.length * 2));
        
        else
            return (energy <= (lidar[5][5] * mySensors.length)  );
    }
    
    
    /**
    * El agente realizará una acción
    * @param action acción que deberá realizar al agente
    * @author Amanda Moyano Romero
    */
    
    public boolean act(String action){
        
        session = session.createReply();
        session.setContent("Request execute "+action+" session "+sessionKey);
        this.LARVAsend(session);
        session = this.LARVAblockingReceive();
        
        if (session.getContent().startsWith("Refuse") || session.getContent().startsWith("Failure")) {
            Alert("Executing action failed due to " + session.getContent());
            updateSensors();
            return false;
        }
        
        updateSensors();
        recargar(myDashboard.getEnergy(), myDashboard.getLidar());
        
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
        int auxCompass = compass;
        
        //Giramos a la orientación de la casilla
        while(coord != auxCompass ){
            
            auxCompass = (auxCompass + 45) % 360;
            cont++;
            
        }
        
        if(cont >= 4){
            while(compass != coord){
                act("RIGHT");
                compass = myDashboard.getCompass();
            }
        }
        
        else{
            while(compass != coord){
                act("LEFT");
                compass = myDashboard.getCompass();
            }
        }

        //subimos si a la altura de la casilla
        while(myDashboard.getLidar()[coord_lidar[0]][coord_lidar[1]] < 0){
            act("UP");
        }

        //nos movemos a la casilla si se está a la altura adecuada
        if(myDashboard.getLidar()[coord_lidar[0]][coord_lidar[1]] >= 0){
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
        
         for(int i=0; i<3;i++){
            for(int j=0;j<3;j++){
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
    * Comprueba si hay que recargar el agente, y si es que sí, lo recarga
    * @param energy energía del agente
    * @param lidar matriz con los valores de la distancia del agente al suelo
    * @author Amanda Moyano Romero
    * @author Lucía Salamanca López
     */
    public void recargar(double energy, int lidar[][]){
        
        //si necesita recargar
        if(needRecharge(lidar, energy)){
            
            //baja a la altura de 0
            while(lidar[5][5] != 0){
                act("DOWN");
                lidar = myDashboard.getLidar();
            }

            act("RECHARGE");
            Info("El agente se ha recargado correctamente");
            
        }
    }
    
    /**
    * Inicializar un vector con las coordenadas de la matriz de lidar
    */
    
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
    * Actualizar los sensores
    */
    
    public boolean updateSensors() {
        session = session.createReply();
        session.setContent("Query sensors session "+sessionKey);
        this.LARVAsend(session);
        session = this.LARVAblockingReceive();
        if (session.getContent().startsWith("Refuse") ||
                session.getContent().startsWith("Failure")) {
            Alert ("Reading of sensors failed due to "+session.getContent());
            return false;
        }
        return true;
    }
    

    @Override
    public void setup() {
        super.setup();
        logger.onOverwrite();
        logger.setLoggerFileName("mylog.json");
        //this.enableDeepLARVAMonitoring();
        Info("Setup and configure agent");
        mystatus = Status.CHECKIN;
        exit = false;
        this.myDashboard = new LARVADash(this);
        //this.doActivateLARVADash();
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
        Info("Taking down and deleting agent");
        this.saveSequenceDiagram("./" + this.problem + ".seqd");
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
            return Status.COMISSIONING;
        } else {
            Error(content);
            return Status.CHECKOUT;
        }
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
            return Status.CLOSEPROBLEM;
        }
        storeManager = this.DFGetAllProvidersOf(localService).get(0);
        Info("Found store manager " + storeManager);
        sensorKeys="";
        // PEDIMOS LOS SENSORES AL STORE MANAGER
        for (String s: mySensors) {
            outbox = new ACLMessage();
            outbox.setSender(this.getAID());
            outbox.addReceiver(new AID(storeManager, AID.ISLOCALNAME));
            outbox.setContent("Request product "+s+ " session "+sessionKey);
            this.LARVAsend(outbox);
            inbox = this.LARVAblockingReceive();
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
    

    public Status MyJoinSession() {
        session = session.createReply();
        session.setContent("Request join session "+sessionKey+
                " attach sensors "+sensorKeys);
        this.LARVAsend(session);
        session = this.LARVAblockingReceive();

        String parse[] = session.getContent().split(" ");
        if (parse[0].equals("Confirm")){
            width = Integer.parseInt(parse[8]);
            height = Integer.parseInt(parse[10]);
            maxFlight = Integer.parseInt(parse[14]);
            return Status.SOLVEPROBLEM;
        }
        else{
            Alert("Error joining session: "+session.getContent());
            return Status.CLOSEPROBLEM;
        }
    }
    
    
    public Status MySolveProblem() {
        
        inicializarVectorLidar();
        
        if(!updateSensors()){
            return Status.CLOSEPROBLEM;
        }
        
        //Mientras la distancia no sea 0, la altura sea mayor que 0 y el agente siga vivo
        while(myDashboard.getDistance() > 0 && myDashboard.getGPS()[2] >= 0 && myDashboard.getAlive()){   
            //obtenemos la orientación a la que se tiene que mover
            int next = nextStep(myDashboard.getGPS(), myDashboard.getLidar());
            
            //nos movemos a ese orientación
            moveTo(next, myDashboard.getLidar(), myDashboard.getCompass());

        }
        
        //si la distancia con el jedi es 0
        if(myDashboard.getDistance() == 0){
           
            //bajamos a su altura
            while(myDashboard.getLidar()[5][5] != 0){
                act("DOWN");
            }
            
            //capturamos al jedi
            act("CAPTURE");
            Info("El jedi ha sido capturado");
            
        }

        return Status.CLOSEPROBLEM;      
    }

}