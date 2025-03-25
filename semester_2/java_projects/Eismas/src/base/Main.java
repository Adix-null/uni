package base;

import cars.Police;
import cars.Automobile;

public class Main {
    public static void main(String[] args) {
        TrafficUser t1 = new Automobile();
        t1.move(-10, 5);
        System.out.println(t1);
        t1.move(Math.TAU / 8, 10.0f);
        System.out.println(t1);

        Police t2 = new Police(7, 3, true, true);
        System.out.println(t2);
        t2.move(14, -2);
        t2.setActive(false);
        System.out.println(t2);

        Automobile t3 = new Automobile(2, 5, true, 800);
        System.out.println(t3);
        System.out.println(TrafficUser.getInstanceCount() + " " + t3.getActive());
    }
}