public class TrafficUser
{
    private int x;
    private int y;
    private boolean active;
    private static int totalInstances = 0;

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

    public int getX()
    {
        return x;
    }
    public int getY()
    {
        return y;
    }
    public boolean getActive()
    {
        return active;
    }
    static public int getInstanceCount()
    {
        return totalInstances;
    }

    public void setX(int x)
    {
        this.x = x;
    }
    public void setY(int y)
    {
        this.y = y;
    }
    public void setActive(boolean active)
    {
        this.active = active;
    }

    public void println()
    {
        System.out.println("active: " + active + " Point(" + x + ", " + y + ") Instances: " + totalInstances);
    }
}
