// Technician.h
#pragma once
#include "Employee.h"

class Technician : public Employee {
public:
    Technician(string n, string g, int a, string id);
    void computeSalary() override;
    void printInfo() const override;
};
