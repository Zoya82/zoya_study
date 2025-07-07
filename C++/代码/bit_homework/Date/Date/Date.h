#pragma once

class Date
{
public:
	// ��ȡĳ��ĳ�µ�����
	int GetMonthDay(int year, int month)const
	{
		static int monthDayArray[13] = { -1,31,28,31,30,31,30,31,31,30,31,30,31 };
		//365
		if (month == 2 && (year % 400 == 0) || (year % 100 != 0 && year % 4 == 0))
		{
			return 29;
		}
		return monthDayArray[month];
	}

	// ȫȱʡ�Ĺ��캯��
	Date(int year = 1900, int month = 1, int day = 1);

	// �������캯��
    // d2(d1)
	Date(const Date& d);

	// ��ֵ���������
    // d2 = d3 -> d2.operator=(&d2, d3)
	Date& operator=(const Date& d);

	// ��������
	~Date()
	{
		_year = 0;
		_month = 0;
		_day = 0;
	}

	// ����+=����
	Date& operator+=(int day);

	// ����+����
	Date operator+(int day);

	// ����-����
	Date operator-(int day);

	// ����-=����
	Date& operator-=(int day);

	// ǰ��++
	Date& operator++();

	// ����++
	Date operator++(int);

	// ����--
	Date operator--(int);

	// ǰ��--
	Date& operator--();

	// >���������
	bool operator>(const Date& d);

private:
	int _year;
	int _month;
	int _day;
};