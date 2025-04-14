package base;

import cars.Police;
import cars.Automobile;
import cars.TrafficUser;
import exceptions.TrafficException;

public class Main {
    public static void main(String[] args) {
        TrafficUser t1 = new Automobile();
        t1.setActive(true);
        try {
            t1.move(-10, 5);
        } catch (TrafficException e) {
            throw new RuntimeException(e);
        }
        System.out.println(t1);
        try {
            t1.move(Math.TAU / 8, 10000.0f);
        } catch (TrafficException e) {
            e.printStackTrace();
        }
        //t1.deactivate();
        System.out.println(t1);

        TrafficUser t2 = new Police(7, 3, true, true);
        t2 = t1;
        System.out.println(t2);
        try {
            t2.move(14, -2);
        } catch (TrafficException e ) {
            throw new RuntimeException(e);
        }
        t2.setActive(false);
        t2.stop();
        System.out.println(t2);

        Stoppable s = new Police(1, 4, true, true);
        s.stop();


        Automobile t3 = new Automobile(2, 5, true, false, 800);
        System.out.println(t3);
        System.out.println(TrafficUser.getInstanceCount() + " " + t3.getActive());
    }
}