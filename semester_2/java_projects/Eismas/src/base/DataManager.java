package base;

import javax.swing.*;
import java.util.function.Consumer;
import java.io.*;

public class DataManager
{
    public static void save(String filename, Object data) throws IOException
    {
        new Thread(() -> {
            try (ObjectOutputStream out = new ObjectOutputStream(new FileOutputStream(filename)))
            {
                out.writeObject(data);
            }
            catch (IOException e)
            {
                e.printStackTrace();
            }
        }).start();
    }

    public static Object load(String filename) throws IOException, ClassNotFoundException
    {
        try (ObjectInputStream in = new ObjectInputStream(new FileInputStream(filename)))
        {
            return in.readObject();
        }
    }
}
