



import org.apache.thrift.TException;
import org.apache.thrift.transport.TSSLTransportFactory;
import org.apache.thrift.transport.TTransport;
import org.apache.thrift.transport.TSocket;
import org.apache.thrift.transport.TSSLTransportFactory.TSSLTransportParameters;
import org.apache.thrift.protocol.TBinaryProtocol;
import org.apache.thrift.protocol.TProtocol;

import java.util.*;

public class Cliente{
        public static void main(String [] args) {


            try {
                TTransport transport;

                transport = new TSocket("localhost", 9090);
                transport.open();


                TProtocol protocol = new  TBinaryProtocol(transport);
                Calculator.Client client = new Calculator.Client(protocol);

                perform(client);

                transport.close();
            } catch (TException x) {
                x.printStackTrace();
            }
        }

        private static void perform(Calculator.Client client) throws TException
        {

            System.out.println("Calculadora básica:\n");
            System.out.println("");

            operacionBasica oB= new operacionBasica();
            oB.a=5.0;
            oB.b=3.5;

            System.out.println("Para los números "+oB.a+" y "+oB.b);
            double sum = client.suma(oB);
            double rest= client.resta(oB);
            double mult= client.multiplicacion(oB);
            System.out.println("Suma: "+ sum);
            System.out.println("Resta: "+ rest);
            System.out.println("Multiplicación: "+ mult);
            try {
                double div = client.division(oB);
                System.out.println("División: "+ div);
            } catch (operacionInvalida oi) {
                System.out.println("Error "+oi.tipo +": " +oi.why);
            }



            operacionVectores oV= new operacionVectores();

            oV.v1=Arrays.asList(1.0,2.0,3.0,4.0);

            oV.v2=Arrays.asList(0.0,5.0,6.0,7.0);



            System.out.println("Calculadora de vectores:\n");

            System.out.println("El vector 1 es:");
            for(int i=0;i<oV.v1.size();i++)
                System.out.print(oV.v1.get(i)+"  ");
            System.out.println("\nEl vector 2 es:");
            for(int i=0;i<oV.v2.size();i++)
                System.out.print(oV.v2.get(i)+"  ");

            try {
                List<Double> vSuma=client.sumaVectores(oV);
                System.out.println("\nSuma: ");
                for(int i=0;i<vSuma.size();i++)
                    System.out.print(vSuma.get(i)+"  ");
            } catch (operacionInvalida oi) {
                System.out.println("\nError "+oi.tipo +": " +oi.why);
            }


            try {
                List<Double> vResta=client.restaVectores(oV);
                System.out.println("\nResta: ");
                for(int i=0;i<vResta.size();i++)
                    System.out.print(vResta.get(i)+"  ");
            } catch (operacionInvalida oi) {
                System.out.println("\nError "+oi.tipo +": " +oi.why);
            }


            try {
                List<Double> vMult=client.multiplicacionVectores(oV);
                System.out.println("\nMultiplicacion: ");
                for(int i=0;i<vMult.size();i++)
                    System.out.print(vMult.get(i)+"  ");
            } catch (operacionInvalida oi) {
                System.out.println("\nError "+oi.tipo +": " +oi.why);
            }

            try {
                List<Double> vDiv=client.divisionVectores(oV);
                System.out.println("\nDivision: ");
                for(int i=0;i<vDiv.size();i++)
                    System.out.print(vDiv.get(i)+"  ");
            } catch (operacionInvalida oi) {
                System.out.println("\nError "+oi.tipo +": " +oi.why);
            }

            System.out.println("Calculadora ecuacion cuadratica:\n");
            segundoGrado sg=new segundoGrado();
            sg.a=3;
            sg.b=5;
            sg.c=-2;
            System.out.println("La solucion a la ecuacion de segundo grado "+sg.a+"x² "+ sg.b+"x "+sg.c+" es:");
            try {
                List<Double> ec=client.ecuacionCuadratica(sg);

                for(int i=0;i<ec.size();i++)
                    System.out.print(ec.get(i)+"  ");
            } catch (operacionInvalida oi) {
                System.out.println("\nError "+oi.tipo +": " +oi.why);
            }

            System.out.println("\nCalculadora operacion combinada:\n");
            combinada cb=new combinada();

            cb.op=Arrays.asList("+","-","*","+","/","-","*");
            cb.nums=Arrays.asList(5.0,8.0,7.0,3.0,5.0,5.0,7.0,10.0);

            System.out.println("La soluciona a la operacion combinada 5 + 8 - 7 * 3 + 5 / 5 - 7 * 10 es "+client.operacionCombinada(cb));
        }
    }



