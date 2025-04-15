package cars;
import base.Engine;
import interfaces.Stoppable;
import exceptions.InactiveException;
import exceptions.OutOfBoundsException;

abstract public class TrafficUser implements Stoppable, Cloneable
{
    private int x;
    private int y;
    private boolean active;
    private boolean stopped;
    protected  Engine engine;
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

    public Engine getEngine() {
        return engine;
    }
    public void setEngine(Engine engine) {
        this.engine = engine;
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
        this(0, 0, false, true,  new Engine());
    }
    public TrafficUser(int x, int y)
    {
        this(x, y, false, true,  new Engine());
    }
    public TrafficUser(int x, int y, boolean active, boolean stopped, Engine engine) {
        setX(x);
        setY(y);
        this.active = active;
        this.stopped = true;
        this.engine = engine;
        totalInstances++;
    }

    public void move(int dx, int dy) throws InactiveException, OutOfBoundsException {
        OutOfBoundsException exc = new OutOfBoundsException();
        exc.setX(gridSizeX);
        exc.setY(gridSizeY);
        if(!active)
            throw new InactiveException();
        if(Math.abs(this.x + dx) >= exc.getX() || Math.abs(this.y + dy) >= exc.getY())
            throw new OutOfBoundsException(dx, dy);
        this.x += dx;
        this.y += dy;
    }
    public void move(double angleRad, double r)  throws InactiveException, OutOfBoundsException
    {
        int dx = (int)(Math.cos(angleRad) * r);
        int dy = (int)(Math.sin(angleRad) * r);
        move(dx, dy);
    }

    @Override
    public TrafficUser clone()
    {
        try
        {
            TrafficUser cloned = (TrafficUser) super.clone();
            //cloned.engine = new Engine(); //deep cloning
            return cloned;
        }
        catch (CloneNotSupportedException e)
        {
            throw new AssertionError();
        }
    }
}
