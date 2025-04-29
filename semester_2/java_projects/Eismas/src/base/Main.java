package base;

import cars.Automobile;
import cars.TrafficUser;
import exceptions.InactiveException;
import exceptions.OutOfBoundsException;
import exceptions.TrafficException;
import factories.AutomobileFactory;
import factories.PoliceFactory;
import factories.TrafficUserFactory;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

public class Main {
    public static void main(String[] args) throws IOException, ClassNotFoundException, InactiveException, OutOfBoundsException {
        List<TrafficUser> data = new ArrayList<>();
        int i = 0;

        loop:
        for(;;) {
            System.out.println("Menu:\n" +
                    "1. Create Vehicle\n" +
                    "2. Move Vehicle\n" +
                    "3. Switch Vehicle\n" +
                    "4. Print vehicle info\n" +
                    "5. Load data\n" +
                    "6. Save data\n" +
                    "7. Exit program"
            );
            int option = Integer.parseInt(System.console().readLine());

            switch (option) {
                case 1: {
                    TrafficUserFactory factory = new AutomobileFactory();
                    TrafficUser t1 = factory.createTrafficUser();
                    t1.setEngine(new Engine("Gas", 200));
                    data.add(t1);
                break;
                }
                case 2: {
                    System.out.println("dx: ");
                    int dx = Integer.parseInt(System.console().readLine());
                    System.out.println("dy: ");
                    int dy = Integer.parseInt(System.console().readLine());
                    data.get(i).setActive(true);
                    data.get(i).move(dx, dy);
                    break;
                }
                case 3: {
                    System.out.println("Vehicle number: ");
                    int input = Integer.parseInt(System.console().readLine());
                    if(input < 0 || input > data.size())
                    {
                        System.out.println("Illegal number");
                        break;
                    }
                    i = input;
                    break;
                }
                case 4:{
                    System.out.println(data.get(i));
                    break;
                }
                case 5: {
                    data = (List<TrafficUser>) DataManager.load("traffic.dat");
                    break;
                }
                case 6: {
                    DataManager.save("traffic.dat", data);
                    break;
                }
                case 7: {
                    break loop;
                }
                default:
                    System.out.println("Wrong number");
                    break;
            }
        }


//        TrafficUserFactory factory = new AutomobileFactory();
//        TrafficUser t1 = factory.createTrafficUser();
//        data.add(t1);
//        t1.setEngine(new Engine("Gas", 200));
//        t1.setActive(true);
//        try {
//            t1.move(-10, 5);
//        } catch (TrafficException e) {
//            throw new RuntimeException(e);
//        }
//        try {
//            t1.move(Math.TAU / 8, 100.0f);
//        } catch (TrafficException e) {
//            e.printStackTrace();
//        }
//        t1.deactivate();
//
//        System.out.println(t1);
//        TrafficUser t2 = t1.clone();
//        data.add(t2);
//        System.out.println(t2);
//        t2.getEngine().setHorsepower(100);
//        System.out.println(t1);
//
//        t2.setActive(true);
//        System.out.println(t2);
//        try {
//            t2.move(14, -2);
//        } catch (TrafficException e ) {
//            throw new RuntimeException(e);
//        }
//        t2.setActive(false);
//        t2.stop();
//        System.out.println(t2);
//
//        TrafficUser t3 = new Automobile(2, 5, true, false, 800);
//        data.add(t3);
//        System.out.println(t3);
//        System.out.println(TrafficUser.getInstanceCount() + " " + t3.getActive());
    }
}