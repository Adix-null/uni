package cars;

import exceptions.InactiveException;
import exceptions.OutOfBoundsException;

public class Automobile extends TrafficUser
{
    private static final int WEIGHT_LIMIT = 7000;
    public int weight;

    int getWeight()
    {
        return weight;
    }
    void setWeight(int weight)
    {
        this.weight = weight;
    }

    public Automobile()
    {
        super();
    }
    public Automobile(int x, int y)
    {
        super(x, y);
    }
    public Automobile(int x, int y, boolean active, boolean stopped, int weight)
    {
        super(x, y, active, stopped);
        this.weight = weight;
    }

    @Override
    public void move(int dx, int dy) throws InactiveException, OutOfBoundsException {
        if (weight < WEIGHT_LIMIT || dy > 0)
        {
            super.move(dx, dy);
        }
        else
        {
            setStopped(true);
        }
    }

    @Override
    public String toString()
    {
        return "<Automobile> active: " + getActive() + " stopped: " + getStopped() + " Point(" + getX() + ", " + getY() + ") weight: " + weight;
    }

    @Override
    public Automobile clone()
    {
        Automobile cloned = (Automobile) super.clone();
        cloned.setWeight(this.getWeight());
        return cloned;
    }
}
