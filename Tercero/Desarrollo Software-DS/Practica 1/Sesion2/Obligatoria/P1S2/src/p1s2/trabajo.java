package p1s2;

import java.util.ArrayList;

public class trabajo {
    
    float oferta;
    int num_trabajo;
    String tipo;
    cliente c;
    tecnico t;
    
    
            
    public trabajo(float of,String tipo, int num_trb,cliente cl){
        this.oferta=of;
        this.tipo=tipo;
        this.num_trabajo=num_trb;
        this.c=cl;
    }
    
    public int getnumeroTrabajo()
    {
        return this.num_trabajo;
    }
       
    void setOferta(float of)
    {
        this.oferta=of;
    }
    
    void setTipo(String tip)
    {
        this.tipo=tip;
    }
    
    float getOferta()
    {
        return this.oferta;
    }
    
    
    
    void pujar(float puja,tecnico tec,Boolean gastos){
        if(puja<oferta)
        {
            oferta=puja;
            this.t=tec;
            if(gastos)
            System.out.println("El tecnico LITE "+t.nombre+" se queda por ahora con la subasta con una oferta de "+oferta+" del trabajo "+num_trabajo);
            else
            System.out.println("El tecnico PREMIUM "+t.nombre+" se queda por ahora con la subasta con una oferta de "+oferta+" del trabajo "+num_trabajo); 
            
            try {
                //Ponemos a "Dormir" el programa durante los s que queremos
                Thread.sleep(5*1000);
             } catch (Exception e) {
                System.out.println(e);
             }
        }
    }
    
    void ResultadoFinal()
    {
        if(t!=null)
        System.out.println("El trabajo con id "+num_trabajo+" ha sido otorgado al tecnico "+t.nombre);
    }
    
    
    
    

   
    
    
    
    
    
}