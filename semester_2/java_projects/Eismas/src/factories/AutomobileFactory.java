package factories;

import cars.Automobile;
import cars.Police;
import cars.TrafficUser;

public class AutomobileFactory implements TrafficUserFactory
{
    @Override
    public TrafficUser createTrafficUser() {
        return new Automobile(0, 0, true, false, 100);
    }
}
