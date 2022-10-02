package helloworld;

import appboot.LARVABoot;

public class HelloWorld {

    public static void main(String[] args) {
        String host = "";
        LARVABoot connection = new LARVABoot();

        host = connection.inputSelect("Select connection server", new String[]{"localhost", "isg2.ugr.es"}, host);

        if (host != null && host.length() > 0) {
            connection.Boot(host, 1099);

//        connection.launchAgent("Smith", HWMinimal.class);
        connection.launchAgent("Smith", HWBasicLarva.class);
//        connection.launchAgent("Smith", HWMediumLarva.class);
//            connection.launchAgent("Smith", HWFullLarva.class);
        }
        // Closes immdiately
//        connection.WaitToClose().ShutDown();

        // Don't close until click button
        connection.WaitToShutDown();
    }

}
