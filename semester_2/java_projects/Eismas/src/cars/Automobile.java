package cars;

import base.TrafficUser;

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
    public Automobile(int x, int y, boolean active, int weight)
    {
        super(x, y, active);
        this.weight = weight;
    }

    @Override
    public void move(int dx, int dy)
    {
        if (weight < WEIGHT_LIMIT || dy > 0)
        {
            super.move(dx, dy);
        }
    }

    public void drive(int x, int y)
    {
        setActive(true);
        move(x, y);
    }

    @Override
    public String toString()
    {
        return "<Automobile> active: " + getActive() + " Point(" + getX() + ", " + getY() + ") weight: " + weight;
    }
}
