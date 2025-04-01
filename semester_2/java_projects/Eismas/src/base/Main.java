package base;

import cars.Police;
import cars.Automobile;
import cars.TrafficUser;

public class Main {
    public static void main(String[] args) {
        TrafficUser t1 = new Automobile();
        t1.move(-10, 5);
        System.out.println(t1);
        t1.move(Math.TAU / 8, 10.0f);
        t1.deactivate();
        System.out.println(t1);

        Police t2 = new Police(7, 3, true, true);
        System.out.println(t2);
        t2.move(14, -2);
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