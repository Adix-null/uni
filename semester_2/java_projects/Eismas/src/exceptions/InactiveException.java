package exceptions;

public class InactiveException extends TrafficException
{
    public InactiveException()
    {
        super("Vehicle must be active to start moving");
    }
}
