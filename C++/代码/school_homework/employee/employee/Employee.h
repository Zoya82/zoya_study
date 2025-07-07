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
    // ���캯��
    Employee(string n, string g, int a, string id, double base);
    // �������캯��
    Employee(const Employee& e);
    // ����������
    virtual ~Employee();

    virtual void computeSalary() = 0;  // ���麯��
    virtual void printInfo() const;    // ���Ա��������Ϣ
    bool operator<(const Employee& e) const;  // ���� "<" �Ƚϲ�����
};
