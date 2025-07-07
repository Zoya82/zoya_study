// Employee.cpp
#include "Employee.h"

Employee::Employee(string n, string g, int a, string id, double base)
    : name(n), gender(g), age(a), employeeID(id), baseSalary(base), actualSalary(0) {
    cout << "员工构造函数调用，员工名：" << name << endl;
}

Employee::Employee(const Employee& e)
    : name(e.name), gender(e.gender), age(e.age), employeeID(e.employeeID), baseSalary(e.baseSalary), actualSalary(e.actualSalary) {
    cout << "员工拷贝构造函数调用，员工名：" << name << endl;
}

Employee::~Employee() {
    cout << "员工析构函数调用，员工名：" << name << endl;
}

void Employee::printInfo() const {
    cout << "姓名: " << name << ", 性别: " << gender << ", 年龄: " << age
        << ", 工号: " << employeeID << ", 基础工资: " << baseSalary
        << ", 实际工资: " << actualSalary << endl;
}

bool Employee::operator<(const Employee& e) const {
    return actualSalary < e.actualSalary;
}
