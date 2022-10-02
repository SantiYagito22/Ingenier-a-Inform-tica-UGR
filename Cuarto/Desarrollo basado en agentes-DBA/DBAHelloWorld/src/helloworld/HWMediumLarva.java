/**
 * @author Anatoli.Grishenko@gmail.com
 *
 */
package helloworld;

import agents.LARVAFirstAgent;

public class HWMediumLarva extends LARVAFirstAgent {

    /**
     * Internal states of the agent
     */
    enum Status {
        CHECKIN, CHECKOUT, EXIT
    }
    Status mystatus;

    @Override
    public void setup() {
        super.setup();

        Info("Setup and configure agent");
        mystatus = Status.CHECKIN;
        exit = false;
    }

    /**
     * This is the simplest version, just do everything and do not check for
     * errors
     */
//    public void Execute() {
//        Info("Status: " + mystatus.name());
//        switch (mystatus) {
//            case CHECKIN:
//                Info("Loading passport and checking-in to LARVA");
//                loadMyPassport("ANATOLI_GRISHENKO.passport");
//                this.doLARVACheckin();
//                mystatus = HWMediumLarva.Status.CHECKOUT;
//                break;
//            case CHECKOUT:
//                this.doLARVACheckout();
//                mystatus = HWMediumLarva.Status.EXIT;
//                break;
//            case EXIT:
//            default:
//                exit = true;
//                break;
//        }
//    }
    /**
     * This is the right version, do everything but also, do check for possible
     * errors
     */
    @Override
    public void Execute() {
        Info("Status: " + mystatus.name());
        switch (mystatus) {
            case CHECKIN:
                mystatus = MyCheckin();
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
        return Status.CHECKOUT;
    }

    public Status MyCheckout() {
        this.doLARVACheckout();
        return Status.EXIT;
    }
}
