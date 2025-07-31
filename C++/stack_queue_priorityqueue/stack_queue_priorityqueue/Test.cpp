#include <stack>
#include <list>
#include <queue>
#include <iostream>

using namespace std;

#include "Stack.h"
#include "Queue.h"
#include "PriorityQueue.h"

class Date
{
	friend ostream& operator<<(ostream& _cout, const Date& d);
public:
	Date(int year = 1900, int month = 1, int day = 1)
		: _year(year)
		, _month(month)
		, _day(day)
	{
	}

	bool operator<(const Date& d)const
	{
		return (_year < d._year) ||
			(_year == d._year && _month < d._month) ||
			(_year == d._year && _month == d._month && _day < d._day);
	}

	bool operator>(const Date& d)const
	{
		return (_year > d._year) ||
			(_year == d._year && _month > d._month) ||
			(_year == d._year && _month == d._month && _day > d._day);
	}

private:
	int _year;
	int _month;
	int _day;
};

ostream& operator<<(ostream& _cout, const Date& d)
{
	_cout << d._year << "-" << d._month << "-" << d._day;
	return _cout;
}

struct LessPDate
{
	bool operator()(Date* p1, Date* p2)
	{
		return *p1 < *p2;
	}
};

int main()
{
	//priority_queue<Date> q1;
	priority_queue<Date, vector<Date>, greater<Date>> q1;
	q1.push(Date(2025, 10, 29));
	q1.push(Date(2025, 10, 28));
	q1.push(Date(2025, 10, 30));
	while (!q1.empty())
	{
		std::cout << ' ' << q1.top();
		q1.pop();
	}
	std::cout << '\n';

	priority_queue<Date*, vector<Date*>, LessPDate> q2;
	q2.push(new Date(2025, 10, 29));
	q2.push(new Date(2025, 10, 28));
	q2.push(new  Date(2025, 10, 30));
	while (!q2.empty())
	{
		std::cout << ' ' << *q2.top();
		q2.pop();
	}
	std::cout << '\n';

	return 0;
}