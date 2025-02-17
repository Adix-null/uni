import javax.swing.*;
import java.awt.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;

//7 užduotis, Adomas Bielūnas 1k 2.1gr

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
    int mouse_pos_x = 0;
    int mouse_pos_y = 0;

    public Main() {
        setBackground(Color.BLACK);

        addMouseListener(new MouseAdapter() {
            @Override
            public void mousePressed(MouseEvent e) {
                mouse_pos_x = e.getX();
                mouse_pos_y = e.getY();
                mouse_state = (mouse_pos_x * 2 < window_width)
                        ? (mouse_pos_y * 2 < window_height ? MouseState.TOP_LEFT : MouseState.BOTTOM_LEFT)
                        : (mouse_pos_y * 2 < window_height ? MouseState.TOP_RIGHT : MouseState.BOTTOM_RIGHT);
                repaint();
            }
        });
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        g.setColor(Color.WHITE);

        int sides = switch (mouse_state)
        {
            case NOT_CLICKED -> 0;
            case TOP_LEFT -> 3;
            case TOP_RIGHT -> 5;
            case BOTTOM_RIGHT -> 8;
            case BOTTOM_LEFT -> 11;
        };

        drawShape(g, sides, (window_height + window_width) / 15, mouse_pos_x, mouse_pos_y);
    }

    void drawShape(Graphics g, int side_count, int radius, int x, int y)
    {
        double angle = - Math.TAU / 4;
        int x_old = 0;
        int y_old = 0;
        for(int i = 0; i <= side_count; i++)
        {
            int x_new = (int)(Math.cos(angle) * radius) + x;
            int y_new = (int)(Math.sin(angle) * radius) + y;
            if(i != 0)
                g.drawLine(x_old, y_old, x_new, y_new);
            x_old = x_new;
            y_old = y_new;
            angle += Math.TAU / side_count;
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