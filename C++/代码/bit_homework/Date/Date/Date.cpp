#pragma once
#include "Date.h"

// 全缺省的构造函数
Date::Date(int year, int month , int day )  //默认参数不能在类的定义和声明中重复定义。默认参数只能在 声明 时给出，不能在 定义 时再次给出。
	:_year(year),_month(month),_day(day){}

// 拷贝构造函数
// d2(d1)
Date::Date(const Date& d)
{
	_year = d._year;
	_month = d._month;
	_day = d._day;
}

// 赋值运算符重载
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

// 日期+=天数
Date& Date::operator+=(int day)
{
	//补充逻辑
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
//+=用引用，因为加完后还是原来的对象，+用对象，因为可以+后创造新对象

// 日期+天数
Date Date::operator+(int day)
{
	Date tmp(*this);  //构造函数
	tmp += day;
	return tmp;
	//将临时对象返回给调用者之后，它的生命周期不会立即结束。调用者会接收到 tmp 的拷贝（或者引用），并且这个拷贝会继续存在，直到它被销毁。
}

// 日期-天数
Date Date::operator-(int day)
{
	Date tmp = *this;
	tmp -= day;
	return tmp;
}

// 日期-=天数
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

// 前置++
Date& Date::operator++()
{
	*this += 1;
	return *this;
}

// 后置++
Date Date::operator++(int)
{
	return *this;
	*this += 1;
}

// 后置--
Date Date::operator--(int)
{
	return *this;
	*this -= 1;
}

// 前置--
Date& Date::operator--()
{
	*this -= 1;
	return *this;
}

// >运算符重载
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