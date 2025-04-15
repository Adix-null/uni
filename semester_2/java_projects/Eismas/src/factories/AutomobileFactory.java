package factories;

import cars.Automobile;
import cars.Police;

public class AutomobileFactory implements TrafficUserFactory
{
    @Override
    public Automobile createAutomobile()
    {
        return new Automobile(0, 0, true, false, 100);
    }

    @Override
    public Police createPolice() {
        return null;
    }
}
