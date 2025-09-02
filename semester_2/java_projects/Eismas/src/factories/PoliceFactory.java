package factories;

import cars.Automobile;
import cars.Police;
import cars.TrafficUser;

public class PoliceFactory implements TrafficUserFactory
{
    @Override
    public TrafficUser createTrafficUser() {
        return new Police(0, 0, true, false);
    }
}
