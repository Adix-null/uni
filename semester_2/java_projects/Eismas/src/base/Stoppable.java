package base;

public interface Stoppable extends Activeable
{
    boolean getStopped();
    void setStopped(boolean stopped);
    void stop();
}