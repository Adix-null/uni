package cars;

import base.TrafficUser;

public class Police extends TrafficUser
{
    public boolean sirensActive = false;
    public Police()
    {
        super();
    }

    public Police(int x, int y)
    {
        super(x, y);
    }

    public Police(int x, int y, boolean active, boolean sirens)
    {
        super(x, y, active);
        this.sirensActive = sirens;
    }

    void setSirensActive(boolean sirensActive)
    {
        this.sirensActive = sirensActive;
    }

    boolean getSirensActive()
    {
        return sirensActive;
    }

    @Override
    public void setActive(boolean active)
    {
        super.setActive(active);
        if (!active)
        {
            this.sirensActive = false;
        }
    }

    public void move(int dx, int dy)
    {
        super.move(dx, dy);
    }

    public void move(double angleRad, double r)
    {
        super.move(angleRad, r);
    }

    @Override
    public String toString()
    {
        return "<Police> active: " + getActive() + " Point(" + getX() + ", " + getY() + ") sirensActive: " + sirensActive;
    }

    @Override
    public void println()
    {
        System.out.println("Police: ");
        super.println();
        System.out.println("Sirens: " + sirensActive);
    }

    public static void printDefault(TrafficUser user)
    {
        user.println();
    }

}
