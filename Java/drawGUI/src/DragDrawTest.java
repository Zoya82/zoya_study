import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.awt.geom.Line2D;
import java.util.*;

public class DragDrawTest extends JFrame{
    JButton b1,b2,b3,b4,b5,b6;
    JPanel buttonPanel,drawPanel;
    JTextArea t1;
    int x1,x2,y1,y2,flag;

    public DragDrawTest(){
        super("DragDraw");

        buttonPanel = new JPanel();
        buttonPanel.setLayout(new FlowLayout(FlowLayout.CENTER,10,10));

        b1 = new JButton("文本输出");
        b2 = new JButton("清空");
        b3 = new JButton("徒手绘画");
        b4 = new JButton("画矩形");
        b5 = new JButton("画线");
        b6 = new JButton("画圆");
        buttonPanel.add(b1);
        buttonPanel.add(b2);
        buttonPanel.add(b3);
        buttonPanel.add(b4);
        buttonPanel.add(b5);
        buttonPanel.add(b6);


        t1 = new JTextArea();


        b1.addActionListener(new ActionListener(){
            public void actionPerformed(ActionEvent e){
                flag=1;
                String str = JOptionPane.showInputDialog(null,"你想要输出的内容","输出");
                JOptionPane.showMessageDialog(null,str);
                t1.setText(str);
            }
        });
        b2.addActionListener(new ActionListener(){
            public void actionPerformed(ActionEvent e){
                flag=2;
                drawPanel.repaint();
            }
        });
        b3.addActionListener(new ActionListener(){
            public void actionPerformed(ActionEvent e){
                flag=3;
            }
        });
        b4.addActionListener(new ActionListener(){
            public void actionPerformed(ActionEvent e){
                flag=4;
            }
        });
        b5.addActionListener(new ActionListener(){
            public void actionPerformed(ActionEvent e){
                flag=5;
            }
        });
        b6.addActionListener(new ActionListener(){
            public void actionPerformed(ActionEvent e){
                flag=6;
            }
        });

        drawPanel = new JPanel();
        drawPanel.addMouseListener(new MouseAdapter(){
            public void mousePressed(MouseEvent e){
                x1=e.getX();
                y1=e.getY();
            }
            public void mouseReleased(MouseEvent e){
                x2=e.getX();
                y2=e.getY();
                Graphics2D g=(Graphics2D)drawPanel.getGraphics();
                if(flag==4){
                    g.drawRect(x1,y1,Math.abs(x2-x1),Math.abs(y2-y1));
                }
                if(flag==5){
                    g.drawLine(x1,y1,x2,y2);
                }
                if(flag==6){
                    g.drawOval(x1,y1,x2-x1,y2-y1);//画圆
                }
            }

        });
        drawPanel.addMouseMotionListener(new MouseMotionAdapter(){
            public void mouseDragged(MouseEvent e){
                x2=e.getX();y2=e.getY();
                Graphics2D g = (Graphics2D)drawPanel.getGraphics();
                if(flag==3){
                    g.draw(new Line2D.Double(x1,y1,x2,y2));
                    x1=x2;
                    y1=y2;
                }

            }
        });

        JPanel centerPanel = new JPanel();
        centerPanel.setLayout(new BorderLayout());
        centerPanel.add(drawPanel, BorderLayout.CENTER);
        centerPanel.add(t1, BorderLayout.EAST);
        t1.setPreferredSize(new Dimension(200, 0));

        this.setLayout(new BorderLayout());
        //p1.add(t1);
        this.add(buttonPanel,BorderLayout.NORTH);
        this.add(centerPanel,BorderLayout.CENTER);
        this.setVisible(true);
        this.setSize(500,400);
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }

    public static void main(String[] args) {
        DragDrawTest GUI = new DragDrawTest();
    }

}


