#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
using namespace std;

class Date
{
public:
    Date(int year = 1, int month = 1, int day = 1)
    {
        _year = year;
        _month = month;
        _day = day;
    }

    Date(const Date& d)
    {
            _year = d._year;
            _month = d._month;
            _day = d._day;
    }
        Date(Date* d)
    {
        _year = d->_year;
        _month = d->_month;
        _day = d->_day;
    }
    void Print()
    {
        cout << _year << "-" << _month << "-" << _day << endl;
    }
private:
    int _year;
    int _month;
    int _day;
};
void Func1(Date d)
{
    cout << &d << endl;
    d.Print();
}

Date& Func2()
{
    Date tmp(2024, 7, 5);
    tmp.Print();
    return tmp;
}

int main()
{
    Date d1(2024, 7, 5);
    Func1(d1);
    cout << &d1 << endl;

    Date d2(&d1);
    d1.Print();
    d2.Print();

    Date d3(d1);
    d2.Print();

    Date d4 = d1;
    d2.Print();

    Date ret = Func2();
    ret.Print();

    return 0;
}