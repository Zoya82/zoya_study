// main.cpp
#include "Employee.h"
#include "Technician.h"
#include "Manager.h"
#include "LinkedList.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    vector<Employee*> employees;

    int n;
    cout << "请输入员工数量: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        string name, gender, id;
        int age;
        cout << "请输入员工" << i + 1 << "的姓名、性别、年龄、工号: ";
        cin >> name >> gender >> age >> id;

        char type;
        cout << "输入类型（T表示技术员，M表示经理）: ";
        cin >> type;

        if (type == 'T') {
            Technician* tech = new Technician(name, gender, age, id);
            tech->computeSalary();
            employees.push_back(tech);
        }
        else if (type == 'M') {
            Manager* mgr = new Manager(name, gender, age, id);
            mgr->computeSalary();
            employees.push_back(mgr);
        }
    }

    LinkedList<Employee> employeeList;
    for (auto emp : employees) {
        employeeList.add(emp);
    }

    int insertPosition;
    cout << "请输入插入位置: ";
    cin >> insertPosition;
    employeeList.insertAt(insertPosition);

    employees.clear();
    employees = employeeList.getAllEmployees();

    // 插入后打印员工列表
    cout << "\n插入后员工列表：" << endl;
    employeeList.printList();

    sort(employees.begin(), employees.end(), [](Employee* a, Employee* b) {
        return *a < *b;
        });

    cout << "\n按工资排序后的员工:" << endl;
    for (auto emp : employees) {
        emp->printInfo();
    }

    ofstream outFile("employees.dat", ios::binary);
    for (auto emp : employees) {
        outFile.write(reinterpret_cast<char*>(emp), sizeof(Employee*));
    }
    outFile.close();

    ifstream inFile("employees.dat", ios::binary);
    while (inFile.read(reinterpret_cast<char*>(&employees[0]), sizeof(Employee*))) {
        employees[0]->printInfo();
    }
    inFile.close();

    return 0;
}
