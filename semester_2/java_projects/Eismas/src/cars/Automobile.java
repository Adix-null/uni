package cars;

import base.TrafficUser;

public class Automobile extends TrafficUser
{
    public int weight;

    public Automobile(int x, int y, boolean active, int weight)
    {
        super(x, y, active);
        this.weight = weight;
    }

    void setWeight(int weight)
    {
        this.weight = weight;
    }

    int getWeight()
    {
        return weight;
    }

    @Override
    public void move(int dx, int dy)
    {
        if (weight < 7000 || dy > 0)
        {
            super.move(dx, dy);
        }
    }

    public void Drive(int x, int y)
    {
        setActive(true);
        move(x, y);
    }

    @Override
    public String toString()
    {
        return "<Automobile> active: " + getActive() + " Point(" + getX() + ", " + getY() + ") weight: " + weight;
    }

    @Override
    public void println()
    {
        System.out.println("Automobile: ");
        super.println();
        System.out.println("Weight: " + weight);
    }

    public static void printDefault(TrafficUser user)
    {
        user.println();
    }
}
