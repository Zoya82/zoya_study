import java.awt.*;
import javax.swing.*;

public class MyFrame {
    public void CreateJFrame(String title){
        JFrame frame = new JFrame(title);
        JPanel p1= new JPanel();
        p1.setBackground(Color.PINK);

        JLabel l1 = new JLabel("这是一个标签");
        //JScrollBar s1 = new JScrollBar();
        JScrollPane s1 = new JScrollPane(l1);
        //p1.add(l1);
        p1.add(s1);
        //JOptionPane.showConfirmDialog(null,"对话框中的内容","对话框标题",JOptionPane.YES_NO_CANCEL_OPTION,JOptionPane.INFORMATION_MESSAGE);
        String name=JOptionPane.showInputDialog(null,"输入要输入对话框的内容");
        System.out.println("用户输入的名字是: " + name);
        frame.setContentPane(p1);
        frame.setVisible(true);
        frame.setBounds(400,400,400,300);
        //frame.setSize(new Dimension(400,300));
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }

    public static void main(String args[]){
        new MyFrame().CreateJFrame("一个JFrame的标题");
    }

    /**JButton b1=new JButton("一个普通按钮");
    JToggleButton b2 = new JToggleButton("一个切换按钮");
    JToggleButton b3 = new JToggleButton("一个带指定初始状态的切换按钮",true);
    **/
}
