#include <iostream>
#include "vector.h"

void TestInsert()
{
    zoya::vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(4);

    std::cout << "Before insert: ";
    for (size_t i = 0; i < v.size(); ++i)
        std::cout << v[i] << " ";
    std::cout << std::endl;

    v.insert(v.begin() + 2, 3);

    std::cout << "After insert: ";
    for (size_t i = 0; i < v.size(); ++i)
        std::cout << v[i] << " ";
    std::cout << std::endl;
}

int main()
{
    TestInsert(); // 在主函数中调用测试函数
    return 0;
}
