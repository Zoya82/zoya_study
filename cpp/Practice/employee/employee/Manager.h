// Manager.h
#pragma once
#include "Employee.h"

class Manager : public Employee {
public:
    Manager(string n, string g, int a, string id);
    void computeSalary() override;
    void printInfo() const override;
};
