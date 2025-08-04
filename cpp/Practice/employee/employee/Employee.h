// Employee.h
#pragma once
#include <string>
#include <iostream>
using namespace std;

class Employee {
protected:
    string name;
    string gender;
    int age;
    string employeeID;
    double baseSalary;
    double actualSalary;

public:
    // 构造函数
    Employee(string n, string g, int a, string id, double base);
    // 拷贝构造函数
    Employee(const Employee& e);
    // 虚析构函数
    virtual ~Employee();

    virtual void computeSalary() = 0;  // 纯虚函数
    virtual void printInfo() const;    // 输出员工基本信息
    bool operator<(const Employee& e) const;  // 重载 "<" 比较操作符
};
