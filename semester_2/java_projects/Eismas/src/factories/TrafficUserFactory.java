package factories;

import base.VehicleType;
import cars.TrafficUser;
import cars.Automobile;
import cars.Police;

//Do by https://refactoring.guru/design-patterns/factory-method

public interface TrafficUserFactory
{
    public TrafficUser createTrafficUser();
}
