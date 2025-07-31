package GUI;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class GUI extends JFrame implements ActionListener {
    JLabel jl1,jl2,jl3,jl4,jl5,jl6,jl7,jl8,jl9,jl10,jl11;
    JButton jb1,jb2,jb3;
    JTextArea jt1=new JTextArea();
    JTextField jtf1,jtf2,jtf3,jtf4,jtf6,jtf7,jtf8,jtf9,jtf10;
    int courseCounter = 0;
    StringBuilder studentInfo = new StringBuilder();

    public GUI(){
        JFrame jfm=new JFrame("GUI成绩单管理系统");
        JPanel jp=new JPanel();
        jl1=new JLabel("Please input 学号：");
        jl2=new JLabel("Please input 姓名：");
        jl3=new JLabel("Please input 所学专业：");
        jl4=new JLabel("Please input 出生日期：");
        jl5=new JLabel("/**********************以下输入该同学的课程信息**********************/");
        jl6=new JLabel("参加了几门课程的考试？");
        jl7=new JLabel("Please input 考试科目：");
        jl8=new JLabel("Please input 考试日期：");
        jl9=new JLabel("Please input 考试分数：");
        jl10=new JLabel("Please input 授课教师：");
        jl11=new JLabel("以下为该同学的基本信息和各科成绩：");
        jb1=new JButton("确认第一门课程的输入");
        jb2=new JButton("显示该同学的基本信息和各科成绩");
        jb3=new JButton("显示全班成绩");
        setLayout(new FlowLayout());

        jtf1=new JTextField(30);
        jtf2=new JTextField(30);
        jtf3=new JTextField(30);
        jtf4=new JTextField(30);
        jtf6=new JTextField(30);
        jtf7=new JTextField(30);
        jtf8=new JTextField(30);
        jtf9=new JTextField(30);
        jtf10=new JTextField(30);

        jp.add(jl1);    jp.add(jtf1);
        jp.add(jl2);    jp.add(jtf2);
        jp.add(jl3);    jp.add(jtf3);
        jp.add(jl4);    jp.add(jtf4);
        jp.add(jl5);
        jp.add(jl6);    jp.add(jtf6);
        jp.add(jl7);    jp.add(jtf7);
        jp.add(jl8);    jp.add(jtf8);
        jp.add(jl9);    jp.add(jtf9);
        jp.add(jl10);   jp.add(jtf10);
        jp.add(jb1);    jp.add(jb2);    jp.add(jb3);
        jp.add(jl11);
        jp.add(jt1);
        jt1.setLineWrap(true);
        jt1.setPreferredSize(new Dimension(400, 300));
        jb1.addActionListener(this);    jb2.addActionListener(this);    jb3.addActionListener(this);
        jfm.getContentPane().add(jp);
        jfm.setSize(515,700);
        jfm.setVisible(true);

    }

    public static void main(String[] args){
        GUI Score=new GUI();
        Score.setDefaultCloseOperation(EXIT_ON_CLOSE);
    }


    @Override
    public void actionPerformed(ActionEvent e) {
        if (e.getSource() == jb1) {
            Date testDate = new Date();
            if (!testDate.setDate(jtf4.getText())) {
                JOptionPane.showMessageDialog(this, "请输入正确的日期格式 xxxx.xx.xx ，并且年份大于1924年！");
                return;
            }else{
                courseCounter++;
                studentInfo.append("\n考试科目：" + jtf7.getText() + "\t考试日期：" + jtf8.getText() + "\t考试分数：" + jtf9.getText() + "\t授课教师：" + jtf10.getText());
                jt1.setText(studentInfo.toString());
                if (courseCounter < Integer.parseInt(jtf6.getText())) {
                    jtf7.setText("");
                    jtf8.setText("");
                    jtf9.setText("");
                    jtf10.setText("");
                }else {
                    JOptionPane.showMessageDialog(this, "输入完成！");
                }
            }

        } else if (e.getSource() == jb2) {
            if(courseCounter < Integer.parseInt(jtf6.getText())){
                JOptionPane.showMessageDialog(this, "考试信息未输入完成！");
            }else{
                jt1.setText("学号：" + jtf1.getText() +
                        "        姓名：" + jtf2.getText() +
                        "        所学专业：" + jtf3.getText() +
                        "        出生日期：" + jtf4.getText() +
                        "\n参加了" + jtf6.getText() + "门考试" + studentInfo.toString());
            }

        } else {
            System.exit(0);
        }
    }
}