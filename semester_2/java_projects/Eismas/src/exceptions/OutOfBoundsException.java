package exceptions;

public class OutOfBoundsException extends TrafficException
{
    private int x;
    private int y;

    public int getX()
    {
        return x;
    }
    public int getY()
    {
        return y;
    }

    public void setX(int x)
    {
         this.x = x;
    }
    public void setY(int y)
    {
        this.y = y;
    }

    public OutOfBoundsException()
    {
        super("Exceeded maximum bounds");
    }
    public OutOfBoundsException(int x, int y)
    {
        super("Exceeded maximum bounds " + x + "X, " + y + "Y");
        setX(x);
        setY(y);
    }
}
