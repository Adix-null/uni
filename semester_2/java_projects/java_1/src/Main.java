import javax.swing.*;
import java.awt.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;

enum MouseState {
    NOT_CLICKED,
    TOP_LEFT,
    TOP_RIGHT,
    BOTTOM_RIGHT,
    BOTTOM_LEFT
}

public class Main extends JPanel {
    MouseState mouse_state = MouseState.NOT_CLICKED;
    static int window_width = 1000;
    static int window_height = 700;

    public Main()
    {
        setBackground(Color.BLACK);

        addMouseListener(new MouseAdapter()
        {
            @Override
            public void mouseClicked(MouseEvent e)
            {
                if(e.getX() * 2 < window_width)
                {
                    if(e.getY() * 2 < window_height)
                    {
                        mouse_state = MouseState.TOP_LEFT;
                    }
                    else
                    {
                        mouse_state = MouseState.BOTTOM_LEFT;
                    }
                }
                else
                {
                    if(e.getY() * 2 < window_height)
                    {
                        mouse_state = MouseState.TOP_RIGHT;
                    }
                    else
                    {
                        mouse_state = MouseState.BOTTOM_RIGHT;
                    }
                }
                System.out.println("Mouse clicked at: " + mouse_state);
            }
        });
    }

    @Override
    protected void paintComponent(Graphics g)
    {
        super.paintComponent(g);
        g.setColor(Color.WHITE);
        g.drawLine(50, 50, 200, 200);
    }

    void drawShape(Graphics g, int side_count, int side_length, int x, int y)
    {
        for(int i = 0; i < side_count; i++)
        {

        }
    }

    public static void main(String[] args)
    {
        JFrame frame = new JFrame();
        Main panel = new Main();

        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(window_width, window_height);
        frame.add(panel);
        frame.setVisible(true);
    }
}