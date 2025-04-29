package base;

import cars.Automobile;
import cars.TrafficUser;
import exceptions.TrafficException;
import factories.AutomobileFactory;
import factories.PoliceFactory;
import factories.TrafficUserFactory;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

public class Main {
    public static void main(String[] args) throws IOException {
        List<TrafficUser> data = new ArrayList<>();

        TrafficUserFactory factory = new AutomobileFactory();
        TrafficUser t1 = factory.createTrafficUser();
        data.add(t1);
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
        data.add(t2);
        System.out.println(t2);
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

        TrafficUser t3 = new Automobile(2, 5, true, false, 800);
        data.add(t3);
        System.out.println(t3);
        System.out.println(TrafficUser.getInstanceCount() + " " + t3.getActive());

        System.out.println("Menu:\n" +
                "1. Create Vehicle" +
                "2. Move Vehicle" +
                "3. Deactivate Vehicle" +
                "4. Deactivate Vehicle" +
                "5. Switch Vehicle" +
                "6. Load data" +
                "7. Save data"
        );
        int option = Integer.parseInt(System.console().readLine());
        switch(option)
        {
            case 1:
            {

            }
            break;
            case 2:
            {

            }
            break;
        }

        DataManager.save("traffic.dat", data);
    }
}