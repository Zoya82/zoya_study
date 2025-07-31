import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class T extends JFrame{
    JButton b1;
    JButton b2;
    JButton b3;
    JButton b4;
    private Color color = Color.black;
    int flag=0;
    int x,y,x1,y1;

    public T(){
        super("DrawTest");
        b1 = new JButton("红色");
        b2 = new JButton("绿色");
        b3 = new JButton("画直线");
        b4 = new JButton("显示当前坐标");
        A1 a1 = new A1();
        M1 m1 = new M1();
        M2 m2 = new M2();
        add(b1,BorderLayout.EAST);
        add(b2,BorderLayout.WEST);
        add(b3,BorderLayout.SOUTH);
        add(b4,BorderLayout.NORTH);
        b1.addActionListener(a1);
        b2.addActionListener(a1);
        b3.addActionListener(a1);
        b4.addActionListener(a1);
        addMouseListener(new M1());
        addMouseMotionListener(m2);
        setSize(500,400);
        setVisible(true);
        //pack();
    }

    public static void main(String[] args){
        new T();
    }

    class A1 implements ActionListener{
        @Override
        public void actionPerformed(ActionEvent e){
            if(e.getSource()==b1){
                color = Color.red;
            }
            if(e.getSource()==b2){
                color = Color.green;
            }
            if(e.getSource()==b3){
                flag=1;
            }
            if(e.getSource()==b4){
                flag=2;
            }
        }
    }
    class M1 extends MouseAdapter{
        @Override
        public void mousePressed(MouseEvent e){
            x=x1=e.getX();
            y=y1=e.getY();
            if(flag==2){
                Graphics g =getGraphics();
                g.setColor(color);
                g.drawString("("+x+","+y+")",x,y);
                g.dispose();
            }
        }
        public void mouseReleased(MouseEvent e){
            if(flag==1&&x!=x1&&y!=y1){
                Graphics g = getGraphics();
                g.setColor(color);
                g.drawLine(x,y,x1,y1);
                g.dispose();
            }
        }
    }
    class M2 extends MouseMotionAdapter{
        @Override
        public void mouseDragged(MouseEvent e){
            x1=e.getX();
            y1=e.getY();


        }
    }
}
