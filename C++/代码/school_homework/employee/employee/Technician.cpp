// Technician.cpp
#include "Technician.h"

Technician::Technician(string n, string g, int a, string id)
    : Employee(n, g, a, id, 100) {
}

void Technician::computeSalary() {
    actualSalary = (age - 18) * baseSalary;
}

void Technician::printInfo() const {
    cout << "¼¼ÊõÔ± - ";
    Employee::printInfo();
}
