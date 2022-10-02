package Practica3;

import agents.LARVAFirstAgent;
import geometry.Point;
import jade.core.AID;
import jade.lang.acl.ACLMessage;
import jade.lang.acl.MessageTemplate;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import swing.LARVADash;


public class DestroyerCommand extends LARVAFirstAgent{

    enum Status {
        CHECKIN, CHECKOUT, OPENPROBLEM, COMISSIONING, JOINSESSION, SOLVEPROBLEM, CLOSEPROBLEM, EXIT
    }
    Status mystatus;
    String service = "PManager", problem = "Mustafar",
            problemManager = "", content, sessionKey, sessionManager, storeManager,
            sensorKeys, mapa;
    int width, height, maxFlight, x=0, y=0;
    int posxTF1,posxTF2,posyTF1,posyTF2,poszTF,jedisEncontrados=0;
    int posxC1,posxC2,posyC1,posyC2,poszC,jedisCapturados=0, cancelCrewFighters=0;
    ACLMessage open, session;
    boolean prueba = true;
    final String password = "KILO";
    String[] contentTokens,
            mySensors = new String[] {
                "ALTITUDE"
            };
    
    boolean step = true;
    List<ArrayList<Integer>> tf1Jedis= new ArrayList<>(), tf2Jedis= new ArrayList<>(); // listas que contienen las coordenadas de cada jedi encontrado por cada tiefighter
    AID TF1,TF2, C1, C2;
    String tf1,tf2;
    int recargas = 5;
    
    Boolean apoyoX1=false,apoyoX2=false; //Variable para saber si tiene que moverse a la izquierda o derecha cada tie.
            
    /**
    * Coge el mapa del mundo del problema
    * @author Lucía Salamanca López
    * @author Jesús Espínola Conde+
    * @author Amanda Moyano Romero
    */
    public void cogerMapa(){
        
        // Subimos para coger el mapa 
        while (myDashboard.getAltitude() < (maxFlight - myDashboard.getMapLevel(0,0))) {
            session = session.createReply();
            session.setContent("Request execute UP session " + sessionKey);
            session.setPerformative(ACLMessage.REQUEST);
            this.LARVAsend(session);
            session = this.LARVAblockingReceive();

            if (session.getContent().startsWith("Refuse") || session.getContent().startsWith("Failure")) {
                Alert("Executing action failed due to " + session.getContent());
                updateSensors();
            }

            updateSensors();
        }
        
        // cogemos el mapa
        session = session.createReply();
        session.setContent("Query map session "+ sessionKey);
        session.setPerformative(ACLMessage.QUERY_REF);
        this.LARVAsend(session);
        
        mapa=this.LARVAblockingReceive().getContent();
        
        //Recluta a los tiefighters
        session = new ACLMessage(ACLMessage.CFP);
        session.setContent(mapa);
        session.setOntology("COMMITMENT");
        session.setSender(this.getAID());
        
        for(int i=0 ;i<DFGetAllProvidersOf("FIGHTER "+password).size(); i++)
        {
          session.addReceiver(new AID(DFGetAllProvidersOf("FIGHTER "+password).get(i), AID.ISLOCALNAME));
        }
        
        session.setReplyWith("RECRUITMENT "+password);
        session.setConversationId(sessionKey);
        this.LARVAsend(session);
        
        
       
        MessageTemplate t = MessageTemplate.MatchInReplyTo("RECRUITMENT " + password);
        
        TF1 = new AID(DFGetAllProvidersOf("FIGHTER "+password).get(0), AID.ISLOCALNAME);
        TF2 = new AID(DFGetAllProvidersOf("FIGHTER "+password).get(1), AID.ISLOCALNAME);
        
        for(int i=0 ;i<DFGetAllProvidersOf("FIGHTER "+password).size(); i++)
        {
            open = this.LARVAblockingReceive(t);
             
            if (open.getPerformative() == ACLMessage.AGREE) {
                session = open.createReply();
                
                session.setPerformative(ACLMessage.ACCEPT_PROPOSAL);
                if(open.getSender().equals(TF1) ){
                    session.setContent(10 + " " + 10);
                }
                
                else if(open.getSender().equals(TF2)){
                    session.setContent(width-10 + " " + 10);
                }
                
                session.setReplyWith("TAKEOFF");
                
                this.LARVAsend(session);
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
        if (this.AMSIsConnected(this.sessionManager) && this.isCheckedin()) {
            this.MyCloseProblem();
            this.MyCheckout();
        }
        Info("Take Down");
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

    /**
    * Abre el problema
    * @author Lucía Salamanca López
     */
    public Status MyOpenProblem() {
        if (this.DFGetAllProvidersOf(service).isEmpty()) {
            Error("Service PMANAGER is down");
            return Status.CHECKOUT;
        }
        problemManager = this.DFGetAllProvidersOf(service).get(0);
        Info("Found problem manager " + problemManager);
              
        int nAgents;
        do {
            nAgents = 0;
            nAgents += DFGetAllProvidersOf("FIGHTER " + password).size();
            nAgents += DFGetAllProvidersOf("CORELLIAN " + password).size();
        } while (nAgents < 4);
        
              
        this.DFSetMyServices(new String[] {"DESTROYER "+password});
        
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
        
        int nAgents;
        do {
            nAgents = 0;
            nAgents += DFGetAllProvidersOf("FIGHTER " + password).size();
            nAgents += DFGetAllProvidersOf("CORELLIAN " + password).size();
        } while (nAgents != 0);
        
        
        session = session.createReply();
        session.setPerformative(ACLMessage.CANCEL);
        this.LARVAsend(session);
      
        
        open= this.LARVAblockingReceive();

        outbox = open.createReply();
        outbox.setContent("Cancel session " + sessionKey);
        Info("Closing problem P3, session " + sessionKey);
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
        
        for (String s: mySensors) {
            outbox = new ACLMessage();
            outbox.setSender(this.getAID());
            outbox.addReceiver(new AID(storeManager, AID.ISLOCALNAME));
            outbox.setContent("Request product "+s+ " session "+sessionKey);
            outbox.setPerformative(ACLMessage.REQUEST);
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
    
    /**
    * Se une a la sesión 
    * @author Lucía Salamanca López
     */
    public Status MyJoinSession() {
        session = session.createReply();
        session.setContent("Request join session "+sessionKey+ " as Destroyer at "+x+" "+y+" attach sensors "+sensorKeys);
        session.setPerformative(ACLMessage.REQUEST);
        this.LARVAsend(session);
        session = this.LARVAblockingReceive();

        String parse[] = session.getContent().split(" ");
        Info(" "+session.getContent());
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
    
    
    /**
    * Actualiza los sensores
    * @author Lucía Salamanca López
     */
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
    
    /**
    * Obtiene el obstaculo de mayor altura y dice a los fighters que suban un UP por encima de este y a los corellian que vayan allí
    * @author Santiago Muñoz Castro
    * @author Lucía Salamanca López
     */
    public void obtenerMayorObstaculoTF(){
        int mayorObstaculo=0;
        
                
        for (int i= 0; i< width ;i ++){
            for(int j=0; j<height ; j++)
            {
                if(myDashboard.getMapLevel(i, j) > mayorObstaculo)
                {
                    mayorObstaculo=myDashboard.getMapLevel(i, j);
                }
            }
        }
        poszTF=mayorObstaculo+5;
        
        MessageTemplate t2 = MessageTemplate.MatchInReplyTo("TAKEOFF");
        int x=0,y=0,altura;
        for(int i=0 ;i<DFGetAllProvidersOf("FIGHTER "+password).size(); i++)
        {
            open = this.LARVAblockingReceive(t2);
            String parse[] = open.getContent().split(" ");
            session = open.createReply();
           
            if(open.getPerformative()==ACLMessage.INFORM){
                x = Integer.parseInt(parse[0]);
                y = Integer.parseInt(parse[1]);
                
                session.setContent("MOVE "+x+" "+y+" "+poszTF);
                session.setReplyWith("MOVE "+x+" "+y+" "+poszTF);
                
            }
            
            session.setPerformative(ACLMessage.REQUEST);
            this.LARVAsend(session);    
        }
        
    }
    
    
    /**
    * Ordena movimiento a casilla a tie, esperando la respuesta de este
    * @author Santiago Muñoz Castro
    * @author Amanda Moyano Romero
    */
    
    public void ordenMovimientoTie(){
        
          
        open = this.LARVAblockingReceive();
        
        
        if( open.getPerformative()==ACLMessage.INFORM)
        {
            String parse[] = open.getContent().split(" ");
            int x=Integer.parseInt(parse[1]);
            int y=Integer.parseInt(parse[2]);
            poszTF=Integer.parseInt(parse[3]);
            
            if(jedisEncontrados==13)
            {
                 cancelCrewFighters++;
                 ACLMessage message = open.createReply();
                 message.setPerformative(ACLMessage.CANCEL);
                 message.setContent("CANCEL CREW");
                 message.setConversationId(sessionKey);
                 message.setOntology("COMMITMENT");
                 this.LARVAsend(message);
            }
            else if(x<=width/2 && !apoyoX1)
            {
                int movX=-1,movY=-1;
            
                if(y==10)
                {
                    movX=x;
                    movY=height-10;
                }
                else if(y==height-10)
                {
                    movX=x;
                    movY=10;
                }
                open= open.createReply();
                open.setContent("MOVE "+movX+" "+movY+" "+poszTF);
                open.setPerformative(ACLMessage.REQUEST);
                open.setReplyWith("MOVE "+movX+" "+movY+" "+poszTF);
                this.LARVAsend(open);    
                apoyoX1=true;
            }
            else if(x<=width/2 && apoyoX1)
            {
                int movX=-1,movY=-1;
            
                if(x+10>=width/2)
                {
                    movX=x+((width/2)-x-1); 
                }
                else{
                    movX=x+10;
                }
                
                movY=y;
                
                open= open.createReply();
                open.setContent("MOVE "+movX+" "+movY+" "+poszTF);
                open.setPerformative(ACLMessage.REQUEST);
                open.setReplyWith("MOVE "+movX+" "+movY+" "+poszTF);
                this.LARVAsend(open);
                apoyoX1=false;
            }
            else if(x>width/2 && !apoyoX2)
            {
                 int movX=-1,movY=-1;
            
                if(y==10)
                {
                    movX=x;
                    movY=height-10;
                }
                else if(y==height-10)
                {
                    movX=x;
                    movY=10;
                }
                open= open.createReply();
                open.setContent("MOVE "+movX+" "+movY+" "+poszTF);
                open.setPerformative(ACLMessage.REQUEST);
                open.setReplyWith("MOVE "+movX+" "+movY+" "+poszTF);
                this.LARVAsend(open);    
                apoyoX2=true;
            }
            else if(x>width/2 && apoyoX2)
            {
                int movX=-1,movY=-1;
            
                if(x-10<=width/2)
                {
                    movX=x-((width/2)-x);
                }
                else{
                    movX=x-10;
                }
                
                movY=y;
                
                open= open.createReply();
                open.setContent("MOVE "+movX+" "+movY+" "+poszTF);
                open.setPerformative(ACLMessage.REQUEST);
                open.setReplyWith("MOVE "+movX+" "+movY+" "+poszTF);
                this.LARVAsend(open);
                apoyoX2=false;
            }
                
        }
        else if(open.getPerformative()==ACLMessage.INFORM_REF)
        {
            String parse[] = open.getContent().split(" ");
            int x=Integer.parseInt(parse[1]);
            int y=Integer.parseInt(parse[2]);
            if(x<=width/2)
            {
                ArrayList<Integer> v1 = new ArrayList<>(Arrays.asList(x,y));
                if(!tf1Jedis.contains(v1))
                {
                    tf1Jedis.add(v1);
                    Info("Tiefighter 1 ha localizado el jedi en: " + x + ", " + y);
                    jedisEncontrados++;
                }
            }
            else{
                ArrayList<Integer> v1 = new ArrayList<>(Arrays.asList(x,y));
                if(!tf2Jedis.contains(v1))
                {
                    tf2Jedis.add(v1);
                    Info("Tiefighter 2 ha localizado el jedi en: " + x + ", " + y);
                    jedisEncontrados++;
                }
                
                
            }
            
            Info("Lista de jedis que hay que encontrar por tf1 \n");
            for(int i=0; i<tf1Jedis.size();i++)
            {
                Info(tf1Jedis.get(i).get(0)+","+tf1Jedis.get(i).get(1));
            }
            
            Info("Lista de jedis que hay que encontrar por tf2 \n");
            for(int i=0; i<tf2Jedis.size();i++)
            {
                Info(tf2Jedis.get(i).get(0)+","+tf2Jedis.get(i).get(1));
            }
            
        }
        
        else if(open.getPerformative()==ACLMessage.QUERY_IF){
            
             if(recargas != 0){
                open= open.createReply();
                open.setContent("RECHARGE");
                open.setPerformative(ACLMessage.CONFIRM);
                recargas --;
                Info("Recarga autorizada");
                Info("Nº de recargas restantes: " + recargas);
                this.LARVAsend(open);
             }
            
            
            else{
                open= open.createReply();
                open.setContent("RECHARGE");
                open.setPerformative(ACLMessage.DISCONFIRM);
                Info("Recarga no autorizada");
                this.LARVAsend(open); 
            
            }
         
        }
       
        
    }
    
   
    /**
    * Autoriza la recarga de un agente Corellian
    * @author Amanda Moyano Romero
    * @author Santiago Muñoz Castro
    */
    public void recargaCorellian(AID corellian){
        MessageTemplate t = MessageTemplate.MatchPerformative(ACLMessage.QUERY_IF);
        
        ACLMessage solicitud = this.LARVAblockingReceive(t);
        
        if(solicitud.getPerformative() == ACLMessage.QUERY_IF){
           if(recargas != 0){
                solicitud= solicitud.createReply();
                solicitud.setContent("RECHARGE");
                solicitud.setPerformative(ACLMessage.CONFIRM);
                recargas --;
                Info("Recarga autorizada");
                this.LARVAsend(solicitud);
             }
            else{
                solicitud= solicitud.createReply();
                solicitud.setContent("RECHARGE");
                solicitud.setPerformative(ACLMessage.DISCONFIRM);
                Info("Recarga no autorizada");
                this.LARVAsend(solicitud); 
            
            }
        }
    
    }
    
    /**
    * Mandar a un Corellian posiciones para capturar Jedi
    * @author Amanda Moyano Romero
    * @author Lucía Salamanca López
    */
    public void ordenCaptura(int x, int y, AID corellian){
    
       
        ACLMessage message = new ACLMessage(ACLMessage.REQUEST);
        message.setSender(this.getAID());
        message.setContent("CAPTURE " + x + " " + y + " " + poszC);
        message.setReplyWith("CAPTURE " + x + " " + y + " " + poszC);
        message.addReceiver(corellian);
        message.setConversationId(sessionKey);
        message.setOntology("COMMITMENT");
        this.LARVAsend(message);

        MessageTemplate t = MessageTemplate.MatchInReplyTo("CAPTURE " + x + " " + y + " " + poszC);
        ACLMessage confirm = this.LARVAblockingReceive(t);
        
        while(confirm.getPerformative() != ACLMessage.INFORM){
            if(confirm.getPerformative() == ACLMessage.QUERY_IF)
            {
                if(recargas != 0){
                confirm= confirm.createReply();
                confirm.setContent("RECHARGE");
                confirm.setPerformative(ACLMessage.CONFIRM);
                recargas --;
                Info("Recarga autorizada");
                this.LARVAsend(confirm);
             }
            else{
                confirm= confirm.createReply();
                confirm.setContent("RECHARGE");
                confirm.setPerformative(ACLMessage.DISCONFIRM);
                Info("Recarga no autorizada");
                this.LARVAsend(open); 
            
            }
            }
            confirm = this.LARVAblockingReceive(t);
            
        }
        

        
        Info("Jedi Capturado por "+corellian);
        

    }
        


    /**
    * Soluciona el problema
    * @author Lucía Salamanca López
    * @author Jesús Espínola Conde
    * @author Amanda Moyano Romero
     */
    public Status MySolveProblem() {
        if(!updateSensors()){
            return Status.CLOSEPROBLEM;
        }
        
        // Cogemos el mapa
        cogerMapa();
        
        //Obtenemos el obstaculo de mayor altura
        obtenerMayorObstaculoTF();
        
        while(cancelCrewFighters<2)
        {
          ordenMovimientoTie();
        }
       
      
       
       //Se ordenan los jedis de menor "y" a mayor
       List<ArrayList<Integer>> tf1JedisOrdenado= new ArrayList<>();
       List<ArrayList<Integer>> tf2JedisOrdenado= new ArrayList<>();
       
       int xyMin[] = {width, height};
       
       while(tf1JedisOrdenado.size() != tf1Jedis.size()){
       
        for(int i=0; i<tf1Jedis.size();i++)
        {
           if(xyMin[1] >  tf1Jedis.get(i).get(1) && !tf1JedisOrdenado.contains(tf1Jedis.get(i))){
               xyMin[0] = tf1Jedis.get(i).get(0);
               xyMin[1] = tf1Jedis.get(i).get(1);
           }   
        }
        
        ArrayList<Integer> aux= new ArrayList<>();
        aux.add(xyMin[0]);
        aux.add(xyMin[1]);
        tf1JedisOrdenado.add(aux);  
        xyMin[0] = width;
        xyMin[1] = height;
        
      }
       
      xyMin[0] = width;
      xyMin[1] = height;
           
      while(tf2JedisOrdenado.size() != tf2Jedis.size()){
       
       for(int i=0; i<tf2Jedis.size();i++)
       {
           if(xyMin[1] >  tf2Jedis.get(i).get(1) && !tf2JedisOrdenado.contains(tf2Jedis.get(i))){
               xyMin[0] = tf2Jedis.get(i).get(0);
               xyMin[1] = tf2Jedis.get(i).get(1);
           }

       }
        
       ArrayList<Integer> aux= new ArrayList<>();

       aux.add(xyMin[0]);
       aux.add(xyMin[1]);
       tf2JedisOrdenado.add(aux); 

       xyMin[0] = width;
       xyMin[1] = height;
      }
       
       
      session = new ACLMessage(ACLMessage.CFP);
      session.setContent(mapa);
      session.setOntology("COMMITMENT");
      session.setSender(this.getAID());
       
      //Recluta a los corellian
      for(int i=0 ;i<DFGetAllProvidersOf("CORELLIAN "+password).size(); i++) {
        session.addReceiver(new AID(DFGetAllProvidersOf("CORELLIAN "+password).get(i), AID.ISLOCALNAME));
      }
      
      session.setReplyWith("RECRUITMENT "+password);
      session.setConversationId(sessionKey);
      this.LARVAsend(session);
        
      MessageTemplate t = MessageTemplate.MatchInReplyTo("RECRUITMENT " + password);
        
      C1 = new AID(DFGetAllProvidersOf("CORELLIAN "+password).get(0), AID.ISLOCALNAME);
      C2 = new AID(DFGetAllProvidersOf("CORELLIAN "+password).get(1), AID.ISLOCALNAME);
        
      for(int i = 0; i < DFGetAllProvidersOf("CORELLIAN "+password).size(); i++) {
        open = this.LARVAblockingReceive(t);
             
        if (open.getPerformative() == ACLMessage.AGREE) {
                session = open.createReply();
                
                session.setPerformative(ACLMessage.ACCEPT_PROPOSAL);

                if(open.getSender().equals(C1)) {
                    session.setContent(tf1JedisOrdenado.get(0).get(0) + " " + tf1JedisOrdenado.get(0).get(1));
                }
                else if(open.getSender().equals(C2)){
                    session.setContent(tf2JedisOrdenado.get(0).get(0) + " " + tf2JedisOrdenado.get(0).get(1));
                }
                
                session.setReplyWith("TAKEOFF");
            
            
                this.LARVAsend(session);
            }
      }
        
       
        
      Info("TODOS LOS JEDIS ENCONTRADOS");
       
       
      
       
      Info("Corellian 1 debe capturar el jedi: ");
      for(int i=0; i<tf1JedisOrdenado.size();i++)
      {
           
        Info(tf1JedisOrdenado.get(i).get(0)+","+tf1JedisOrdenado.get(i).get(1));
        ordenCaptura(tf1JedisOrdenado.get(i).get(0),tf1JedisOrdenado.get(i).get(1),C1);
        
       
      }
       
      Info("Corellian 2 debe capturar el jedi: ");
      for(int i=0; i<tf2JedisOrdenado.size();i++)
      {
        Info(tf2JedisOrdenado.get(i).get(0)+","+tf2JedisOrdenado.get(i).get(1));
        ordenCaptura(tf2JedisOrdenado.get(i).get(0),tf2JedisOrdenado.get(i).get(1),C2);
        
      }
        
             
       ACLMessage message = new ACLMessage();
       message.setPerformative(ACLMessage.CANCEL);
       message.addReceiver(C1);
       message.addReceiver(C2);
       message.setContent("CANCEL CREW");
       message.setConversationId(sessionKey);
       message.setOntology("COMMITMENT");
       this.LARVAsend(message);
       
       int nAgents;
       do {
            nAgents = 0;
            nAgents += DFGetAllProvidersOf("FIGHTER " + password).size();
            nAgents += DFGetAllProvidersOf("CORELLIAN " + password).size();
        } while (nAgents != 0);
       
       
       return Status.CLOSEPROBLEM;      
    }

}