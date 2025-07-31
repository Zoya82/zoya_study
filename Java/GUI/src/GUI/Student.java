package GUI;

public class Student {

    private int num;
    private String name;
    private Date birthDay;//数据成员是类对象
    private String major;

    public Student(){birthDay=new Date();}
    public Student(int n,String na,int year,int month,int day){
        num=n;
        name=na;
        birthDay=new Date(year,month,day);
    }

    public int getNum(){return num;}
    public String getName(){return name;}
    public Date getBirthDay(){return birthDay;}
    public void setStudent(int n,String na,int year,int month,int day){
        num=n;
        na=name;
        birthDay.setDate(year,month,day);
    }

    public String toString(){
        return "学号："+num+";姓名："+name+";出生日期："+birthDay;
    }

}