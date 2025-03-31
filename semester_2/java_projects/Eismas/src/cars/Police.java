package cars;

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
    public void move(int dx, int dy)
    {
        super.move((sirensActive ? 2 : 1) * dx, (sirensActive ? 2 : 1) * dy);
    }

    @Override
    public void move(double angleRad, double r)
    {
        super.move(angleRad, (sirensActive ? 2 : 1) * r);
    }

    @Override
    public String toString()
    {
        return "<Police> active: " + getActive() + " Point(" + getX() + ", " + getY() + ") sirensActive: " + sirensActive;
    }
}
