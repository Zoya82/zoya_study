#pragma once
#include "Date.h"

// ȫȱʡ�Ĺ��캯��
Date::Date(int year, int month , int day )  //Ĭ�ϲ�����������Ķ�����������ظ����塣Ĭ�ϲ���ֻ���� ���� ʱ������������ ���� ʱ�ٴθ�����
	:_year(year),_month(month),_day(day){}

// �������캯��
// d2(d1)
Date::Date(const Date& d)
{
	_year = d._year;
	_month = d._month;
	_day = d._day;
}

// ��ֵ���������
// d2 = d3 -> d2.operator=(&d2, d3)
Date& Date::operator=(const Date& d)
{
	if (this != &d) {
		_year = d._year;
		_month = d._month;
		_day = d._day;
	}
	return *this;
}

// ����+=����
Date& Date::operator+=(int day)
{
	//�����߼�
	if (day < 0)
	{
		return *this = *this - (-day);
	}

	_day = _day + day;
	while (_day > GetMonthDay(_year, _month))
	{
		_day = _day - GetMonthDay(_year, _month);
		_month = _month + 1;
		if (_month > 12)
		{
			_year = _year + 1;
			_month = 1;
		}
	}
	return *this;
}
//+=�����ã���Ϊ�������ԭ���Ķ���+�ö�����Ϊ����+�����¶���

// ����+����
Date Date::operator+(int day)
{
	Date tmp(*this);  //���캯��
	tmp += day;
	return tmp;
	//����ʱ���󷵻ظ�������֮�������������ڲ������������������߻���յ� tmp �Ŀ������������ã����������������������ڣ�ֱ���������١�
}

// ����-����
Date Date::operator-(int day)
{
	Date tmp = *this;
	tmp -= day;
	return tmp;
}

// ����-=����
Date& Date::operator-=(int day) 
{
	if (day < 0)
	{
		return *this += (-day);
	}
	_day -= day;
	if (_day <= 0)
	{
		--_month;
		if (_month == 0)
		{
			_year--;
			_month = 12;
		}
		_day += GetMonthDay(_year, _month);
	}
	return *this;
}

// ǰ��++
Date& Date::operator++()
{
	*this += 1;
	return *this;
}

// ����++
Date Date::operator++(int)
{
	return *this;
	*this += 1;
}

// ����--
Date Date::operator--(int)
{
	return *this;
	*this -= 1;
}

// ǰ��--
Date& Date::operator--()
{
	*this -= 1;
	return *this;
}

// >���������
bool Date::operator>(const Date& d)
{
	if (_year > d._year)
	{
		return true;
	}
	else if (_year == d._year && _month > d._month)
	{
		return true;
	}
	else if (_year == d._year && _month == d._month)
	{
		return _day > d._day;
	}
	return false;
}

void test()
{
	Date d1(2024,12,9);
	Date d2(d1);
}

int main()
{
	test();
}