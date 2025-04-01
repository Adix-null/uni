package exceptions;

public class OutOfBoundsException extends TrafficException
{
    public OutOfBoundsException(int boundX, int boundY)
    {
        super("Exceeded maximum bounds of " + boundX + "X, " + boundY + "Y");
    }
}
