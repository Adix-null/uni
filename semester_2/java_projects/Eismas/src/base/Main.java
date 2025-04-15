package base;

import cars.Automobile;
import cars.TrafficUser;
import exceptions.TrafficException;
import factories.AutomobileFactory;
import factories.PoliceFactory;
import factories.TrafficUserFactory;

public class Main {
    public static void main(String[] args) {
        TrafficUserFactory factory = new AutomobileFactory();
        TrafficUser t1 = factory.createTrafficUser();
        t1.setEngine(new Engine("Gas", 200));
        t1.setActive(true);
        try {
            t1.move(-10, 5);
        } catch (TrafficException e) {
            throw new RuntimeException(e);
        }
        try {
            t1.move(Math.TAU / 8, 100.0f);
        } catch (TrafficException e) {
            e.printStackTrace();
        }
        t1.deactivate();

        System.out.println(t1);
        TrafficUser t2 = t1.clone();
        t2.getEngine().setHorsepower(100);
        System.out.println(t1);

        t2.setActive(true);
        System.out.println(t2);
        try {
            t2.move(14, -2);
        } catch (TrafficException e ) {
            throw new RuntimeException(e);
        }
        t2.setActive(false);
        t2.stop();
        System.out.println(t2);

        Automobile t3 = new Automobile(2, 5, true, false, 800);
        System.out.println(t3);
        System.out.println(TrafficUser.getInstanceCount() + " " + t3.getActive());
    }
}