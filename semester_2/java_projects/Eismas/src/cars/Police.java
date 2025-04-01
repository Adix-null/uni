package cars;

import exceptions.InactiveException;
import exceptions.OutOfBoundsException;

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
        super(x, y, active, !sirens);
        this.sirensActive = sirens;
    }

    void setSirensActive(boolean sirensActive)
    {
        setStopped(false);
        this.sirensActive = sirensActive;
    }

    boolean getSirensActive()
    {
        return sirensActive;
    }

    @Override
    public void move(int dx, int dy) throws InactiveException, OutOfBoundsException {
        super.move((sirensActive ? 2 : 1) * dx, (sirensActive ? 2 : 1) * dy);
    }

    @Override
    public void move(double angleRad, double r) throws InactiveException, OutOfBoundsException
    {
        super.move(angleRad, (sirensActive ? 2 : 1) * r);
    }

    @Override
    public String toString()
    {
        return "<Police> active: " + getActive() + " stopped: " + getStopped() + " Point(" + getX() + ", " + getY() + ") sirensActive: " + sirensActive;
    }
}
