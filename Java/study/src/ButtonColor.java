import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class ButtonColor extends JFrame{
    JButton b1;

    int flag = 0;

    public ButtonColor(){
        b1 = new JButton("按钮");
        b1.setBackground(Color.yellow);
        add(b1,BorderLayout.NORTH);
        M1 m1 = new M1();
        b1.addMouseListener(m1);

        setSize(500,400);
        setVisible(true);
    }
    class M1 extends MouseAdapter{
        @Override
        public void mouseEntered(MouseEvent e){
            b1.setBackground(Color.red);
        }
        public void mouseExited(MouseEvent e){
            b1.setBackground(Color.yellow);
        }
    }
    public static void main(String[] arg){
        new ButtonColor();
    }
}
