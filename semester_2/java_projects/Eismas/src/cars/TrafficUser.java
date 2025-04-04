package cars;
import base.Stoppable;
import exceptions.InactiveException;
import exceptions.OutOfBoundsException;

abstract public class TrafficUser implements Stoppable
{
    private int x;
    private int y;
    private boolean active;
    private boolean stopped;
    private static int totalInstances = 0;
    public static final int gridSizeX = 1000;
    public static final int gridSizeY = 1000;

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

    public final boolean getActive()
    {
        return active;
    }
    public void setActive(boolean active)
    {
        this.active = active;
    }

    public final boolean getStopped()
    {
        return stopped;
    }
    public void setStopped(boolean stopped)
    {
        this.stopped = stopped;
    }

    public void deactivate()
    {
        active = false;
        stopped = true;
    }
    public void stop()
    {
        stopped = true;
    }

    static public int getInstanceCount()
    {
        return totalInstances;
    }

    public TrafficUser()
    {
        this(0,0, false, true);
    }
    public TrafficUser(int x, int y)
    {
        this(x, y, false, true);
    }
    public TrafficUser(int x, int y, boolean active, boolean stopped)
    {
        setX(x);
        setY(y);
        this.active = active;
        this.stopped = true;
        totalInstances++;
    }

    public void move(int dx, int dy) throws InactiveException, OutOfBoundsException {
        if(!active)
            throw new InactiveException();
        if(Math.abs(this.x + dx) >= gridSizeX || Math.abs(this.y + dy) >= gridSizeY)
            throw new OutOfBoundsException(gridSizeX, gridSizeY);
        this.x += dx;
        this.y += dy;
    }
    public void move(double angleRad, double r)  throws InactiveException, OutOfBoundsException
    {
        int dx = (int)(Math.cos(angleRad) * r);
        int dy = (int)(Math.sin(angleRad) * r);
        move(dx, dy);
    }
}
