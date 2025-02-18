public class Main {
    public static void main(String[] args) {
        TrafficUser t1 = new TrafficUser();
        t1.move(-10, 5);
        t1.println();

        TrafficUser t2 = new TrafficUser(7, 3, true);
        t2.println();
        t2.move(14, -2);
        t2.println();
    }
}