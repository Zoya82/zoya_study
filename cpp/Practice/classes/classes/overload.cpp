#define _CRT_SECURE_NO_WARNINGS

int Date::operator-(const Date& d) const
{
    Date max = *this;
    Date min = d;
    int flag = 1;
    if (*this < d)
    {
        max = d;
        min = *this;
        flag = -1;
    }
    int n = 0;
    while (min != max)
    {
        ++min;
        ++n;
    }
    return n * flag;
}