package factories;

import cars.Automobile;
import cars.Police;

public class PoliceFactory implements TrafficUserFactory
{
    @Override
    public Police createPolice()
    {
        return new Police(0, 0, true, false);
    }

    @Override
    public Automobile createAutomobile() {
        return null;
    }
}
