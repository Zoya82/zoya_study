#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
using namespace std;
class A
{
private:
    static int _k;
    int _h = 1;
public:

    class B // B默认就是A的友元
    {
    public:
        void foo(const A& a)
        {
            cout << _k << endl;    
            cout << a._h << endl; 
        }
    };
};
int A::_k = 1;

int main()
{
    cout << sizeof(A) << endl;
    A::B b;
    A aa;
    b.foo(aa);
    return 0;
}