package cars;

interface MovingVehicle
{
    void move(int dx, int dy);
}

public class TrafficUser implements MovingVehicle
{
    private int x;
    private int y;
    private boolean active;
    private static int totalInstances = 0;

    public final int getX()
    {
        return x;
    }
    public void setX(int x)
    {
        this.x = x;
    }

    public final int getY()
    {
        return y;
    }
    public void setY(int y)
    {
        this.y = y;
    }

    public boolean getActive()
    {
        return active;
    }
    public void setActive(boolean active)
    {
        this.active = active;
    }

    static public int getInstanceCount()
    {
        return totalInstances;
    }

    public TrafficUser()
    {
        this(0,0, false);
    }
    public TrafficUser(int x, int y)
    {
        this(x, y, false);
    }
    public TrafficUser(int x, int y, boolean active)
    {
        setX(x);
        setY(y);
        this.active = active;
        totalInstances++;
    }

    public void move(int dx, int dy)
    {
        this.x += dx;
        this.y += dy;
    }
    public void move(double angleRad, double r)
    {
        this.x += (int)(Math.cos(angleRad) * r);
        this.y += (int)(Math.sin(angleRad) * r);
    }
}
