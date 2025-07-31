import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class account extends JFrame {
    private JTextField t1 = new JTextField(10);
    private JPasswordField p1 = new JPasswordField(10);
    private JButton b1 = new JButton("确定");
    private JButton b2 = new JButton("重置");

    public account() {
        setLayout(new FlowLayout());
        add(new JLabel("用户名："));
        add(t1);
        add(new JLabel("密码："));
        add(p1);
        add(b1);
        add(b2);

        M1 m1 = new M1();
        b1.addActionListener(m1);
        b2.addActionListener(m1);

        setSize(100,100);
        pack();
        setVisible(true);
    }

    // 处理动作事件的内部类
    class M1 implements ActionListener {
        public void actionPerformed(ActionEvent e) {
            Object obj = e.getSource();
            if (obj == b1) {
                String tt1 = t1.getText();
                String pp1 = new String(p1.getPassword());
                if (tt1.equals("123") && pp1.equals("123")) {
                    JOptionPane.showMessageDialog(null, "登录成功！");
                } else {
                    JOptionPane.showMessageDialog(null, "用户名或密码错误！");
                }
            } else if (obj == b2) {
                t1.setText("");
                p1.setText("");
            }
        }
    }

    public static void main(String[] args) {
        new account();
    }
}
