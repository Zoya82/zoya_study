import java.awt.*;
import java.awt.event.*;
import java.awt.geom.*;
import javax.swing.*;

public class JFrame2 extends JFrame{
    JPanel p1;
    JLabel l1;
    int x1,y1,x2,y2;

    public JFrame2(){
        l1 = new JLabel("Java GUI应用程序开始运行！",JLabel.CENTER);
        M1 m1 = new M1();
        M2 m2 = new M2();
        addMouseListener(m1);
        addMouseMotionListener(m2);

        add(l1,BorderLayout.NORTH);
        setSize(500,400);
        setVisible(true);
    }
    class M1 extends MouseAdapter{
        @Override
        public void mousePressed(MouseEvent e){
            x1=e.getX();
            y1=e.getY();
            l1.setText("当前鼠标位置：（"+x1+"，"+y1+")");
        }
    }
    class M2 extends MouseMotionAdapter{
        @Override
        public void mouseDragged(MouseEvent e){
            x2=e.getX();
            y2=e.getY();
            l1.setText("当前鼠标位置：（"+x2+"，"+y2+")");
            Graphics2D g = (Graphics2D)getGraphics();
            g.draw(new Line2D.Double(x1,y1,x2,y2));
            x1=x2;
            y1=y2;
            g.dispose();
        }

    }
    public static void main(String[] arg){
        new JFrame2();
    }
}
