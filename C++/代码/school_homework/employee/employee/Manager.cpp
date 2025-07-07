// Manager.cpp
#include "Manager.h"

Manager::Manager(string n, string g, int a, string id)
    : Employee(n, g, a, id, 150) {
}

void Manager::computeSalary() {
    actualSalary = (age - 20) * baseSalary;
}

void Manager::printInfo() const {
    cout << "¾­Àí - ";
    Employee::printInfo();
}
