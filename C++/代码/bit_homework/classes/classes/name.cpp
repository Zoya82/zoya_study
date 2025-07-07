#define _CRT_SECURE_NO_WARNINGS

class Date
{
public:
    void Init(int year, int month, int day)
    {
        _year = year;
        _month = month;
        _day = day;
    }
private:
    int _year; // year_  m_year
    int _month;
    int _day;
};

//int main()
//{
//    Date d;
//    d.Init(2024, 3, 31);
//    return 0;
//}