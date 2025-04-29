package base;

import java.io.*;

public class DataManager
{
    public static void save(String filename, Object data) throws IOException
    {
        try (ObjectOutputStream out = new ObjectOutputStream(new FileOutputStream(filename)))
        {
            out.writeObject(data);
        }
    }

    public static Object load(String filename) throws IOException, ClassNotFoundException
    {
        try (ObjectInputStream in = new ObjectInputStream(new FileInputStream(filename)))
        {
            return in.readObject();
        }
    }
}
