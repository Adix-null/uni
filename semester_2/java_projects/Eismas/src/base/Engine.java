package base;

public class Engine implements Cloneable
{
    private String fuel;
    private int horsepower;

    public String getFuel()
    {
        return fuel;
    }
    public void setFuel(String fuel)
    {
        this.fuel = fuel;
    }

    public int getHorsepower() {
        return horsepower;
    }
    public void setHorsepower(int horsepower) {
        this.horsepower = horsepower;
    }

    public Engine()
    {
        this.fuel = "None";
        this.horsepower = 0;
    }
    public Engine(String fuel, int horsepower)
    {
        this.fuel = fuel;
        this.horsepower = horsepower;
    }

    @Override
    public Engine clone()
    {
        try{
            return (Engine) super.clone();
        }catch (CloneNotSupportedException e) {
            throw new AssertionError();
        }
    }

}
