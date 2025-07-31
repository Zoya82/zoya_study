import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class Test {
    public static void main(String[] args) {
        JFrame frame = new JFrame("算数运算");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.getContentPane().add(new Operator());
        frame.pack();
        frame.setVisible(true);
    }
}

class Operator extends JPanel {
    private JTextField a1 = new JTextField(5);
    private JTextField a2 = new JTextField(5);
    private JLabel a3 = new JLabel("=");
    private JLabel a4 = new JLabel("");
    private JButton b1 = new JButton("+");
    private JButton b2 = new JButton("-");
    private JButton b3 = new JButton("*");

    public Operator() {
        add(a1);
        add(a2);
        add(a3);
        add(a4);
        add(b1);
        add(b2);
        add(b3);
        m1 m1 = new m1();
        b1.addActionListener(m1);
        b2.addActionListener(m1);
        b3.addActionListener(m1);
    }

    class m1 implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            double a = Double.parseDouble(a1.getText());
            double b = Double.parseDouble(a2.getText());
            double c = 0;
            Object obj = e.getSource();
            if (obj == b1) {
                c = a + b;
            }
            if (obj == b2) {
                c = a - b;
            }
            if (obj == b3) {
                c = a * b;
            }
            a4.setText("" + c);
        }
    }
}
