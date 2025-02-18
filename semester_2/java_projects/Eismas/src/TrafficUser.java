public class TrafficUser{
    private int x;
    private int y;
    private boolean active;
    private static int totalInstances = 0;

    public TrafficUser()
    {
        setX(0);
        setY(0);
        this.active = false;
        totalInstances++;
    }
    public TrafficUser(int x, int y)
    {
        setX(x);
        setY(y);
        this.active = false;
        totalInstances++;
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

    public int getX()
    {
        return x;
    }
    public int getY()
    {
        return y;
    }
    public boolean getActive() { return active; }
    public int getIntanceCount() { return totalInstances;}

    public void setX(int x)
    {
        this.x = x;
    }
    public void setY(int y)
    {
        this.y = y;
    }
    public void setActive(boolean active) { this.active = active; }

    public void println()
    {
        System.out.println("actve: " + active + " Point(" + x + ", " + y + ") Instances: " + totalInstances);
    }
}
