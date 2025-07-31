package GUI;

public class Date {
    private int year,month,day;//数据隐藏私有化保护
    public Date(){}
    public Date(int y,int m,int d){year=y;month=m;day=d;}
    public int getYear(){return year;}
    public int getMonth(){return month;}
    public int getDay(){return day;}
    public void setDate(int y,int m,int d){year=y;month=m;day=d;}

    public boolean setDate(String dateStr) {
        String[] parts = dateStr.split("\\.");
        if (parts.length != 3) {
            return false; // 格式不正确
        }
        try {
            int y = Integer.parseInt(parts[0]);
            int m = Integer.parseInt(parts[1]);
            int d = Integer.parseInt(parts[2]);

            if (y < 1924) {
                return false; // 年份太小
            }
            if (m < 1 || m > 12) {
                return false; // 月份不在1-12范围内
            }
            if (d < 1 || d > 31) {
                return false; // 日期不在1-31范围内
            }

            year = y;
            month = m;
            day = d;
            return true;
        } catch (NumberFormatException e) {
            return false; // 格式不正确
        }
    }

    public String toString(){
        return year+"年"+month+"月"+day+"日";
    }

}