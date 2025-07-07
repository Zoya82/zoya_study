// Employee.cpp
#include "Employee.h"

Employee::Employee(string n, string g, int a, string id, double base)
    : name(n), gender(g), age(a), employeeID(id), baseSalary(base), actualSalary(0) {
    cout << "Ա�����캯�����ã�Ա������" << name << endl;
}

Employee::Employee(const Employee& e)
    : name(e.name), gender(e.gender), age(e.age), employeeID(e.employeeID), baseSalary(e.baseSalary), actualSalary(e.actualSalary) {
    cout << "Ա���������캯�����ã�Ա������" << name << endl;
}

Employee::~Employee() {
    cout << "Ա�������������ã�Ա������" << name << endl;
}

void Employee::printInfo() const {
    cout << "����: " << name << ", �Ա�: " << gender << ", ����: " << age
        << ", ����: " << employeeID << ", ��������: " << baseSalary
        << ", ʵ�ʹ���: " << actualSalary << endl;
}

bool Employee::operator<(const Employee& e) const {
    return actualSalary < e.actualSalary;
}
