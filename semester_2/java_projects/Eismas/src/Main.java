class EismoDalyvis{
    private int x;
    private int y;

    public EismoDalyvis(int x, int y)
    {
        this.x = x;
        this.y = y;
    }

    public void Move(int dx, int dy)
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

    @Override
    public String toString()
    {
        return "Point(" + x + ", " + y + ")";
    }
}

public class Main {
    public static void main(String[] args) {
        EismoDalyvis eismoDalyvis = new EismoDalyvis(30, 10);
        System.out.println("X: " + eismoDalyvis.getX());
        System.out.println("Y: " + eismoDalyvis.getY());

        eismoDalyvis.Move(-10, 5);
        System.out.println("X: " + eismoDalyvis.getX());
        System.out.println("Y: " + eismoDalyvis.getY());
    }
}