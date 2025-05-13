package cars;
import base.Engine;
import interfaces.Stoppable;
import exceptions.InactiveException;
import exceptions.OutOfBoundsException;

import java.io.Serial;
import java.io.Serializable;

/**
 * Abstract base class representing an entity that can move within a 2D grid,
 * with controllable activity and stoppable behavior.
 * Implements {@code Stoppable}, {@code Cloneable}, and {@code Serializable}.
 */
abstract public class TrafficUser implements Stoppable, Cloneable, Serializable
{
    private int x;
    private int y;
    private boolean active;
    private boolean stopped;
    protected Engine engine;
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

    /**
     * Gets the current Engine of the vehicle.
     */
    public Engine getEngine() {
        return engine;
    }
    /**
     * Sets the current Engine of the vehicle.
     * @param engine The Engine object that will be inserted
     */
    public void setEngine(Engine engine) {
        this.engine = engine;
    }

    /**
     * Deactivates and stops the entity.
     */
    public void deactivate()
    {
        active = false;
        stopped = true;
    }
    public void stop()
    {
        stopped = true;
    }

    /**
     * Gets the total amount of vehicles.
     */
    static public int getInstanceCount()
    {
        return totalInstances;
    }

    /**
     * Constructs a TrafficUser at position (0,0), inactive and stopped.
     */
    public TrafficUser()
    {
        this(0, 0, false, true,  new Engine());
    }
    /**
     * Constructs a TrafficUser at specified position, inactive and stopped.
     * @param x X-coordinate
     * @param y Y-coordinate
     */
    public TrafficUser(int x, int y)
    {
        this(x, y, false, true,  new Engine());
    }
    /**
     * Constructs a TrafficUser with full control over all properties.
     * @param x X-coordinate
     * @param y Y-coordinate
     * @param active whether active
     * @param stopped whether stopped
     * @param engine Engine instance
     */
    public TrafficUser(int x, int y, boolean active, boolean stopped, Engine engine) {
        setX(x);
        setY(y);
        this.active = active;
        this.stopped = true;
        this.engine = engine;
        totalInstances++;
    }

    /**
     * Moves the entity by a delta (dx, dy).
     * @param dx X delta
     * @param dy Y delta
     * @throws InactiveException if not active
     * @throws OutOfBoundsException if movement exceeds grid bounds
     */
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
    /**
     * Moves the entity in a given direction and distance.
     * @param angleRad angle in radians
     * @param r distance to move
     * @throws InactiveException if not active
     * @throws OutOfBoundsException if movement exceeds grid bounds
     */
    public void move(double angleRad, double r)  throws InactiveException, OutOfBoundsException
    {
        int dx = (int)(Math.cos(angleRad) * r);
        int dy = (int)(Math.sin(angleRad) * r);
        move(dx, dy);
    }
    /**
     * Creates a deep clone of the TrafficUser.
     * @return cloned TrafficUser
     */
    @Override
    public TrafficUser clone()
    {
        try
        {
            TrafficUser cloned = (TrafficUser) super.clone();
            cloned.engine = engine.clone(); // deep cloning
            return cloned;
        }
        catch (CloneNotSupportedException e)
        {
            throw new AssertionError();
        }
    }
}
