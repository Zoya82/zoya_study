// LinkedList.h
#pragma once
#include <vector>
#include <cassert>
#include <iostream>
#include <fstream>
#include "Employee.h"
#include "Technician.h"
#include "Manager.h"

using namespace std;

template<typename T>
class LinkedList {
private:
    struct Node {
        T* data;
        Node* next;
        Node(T* d) : data(d), next(nullptr) {}
    };
    Node* head;

public:
    LinkedList();
    ~LinkedList();
    void add(T* employee);
    void deleteAt(int i);
    void insertAt(int i);
    void printList();
    void writeToFile(const string& filename);
    void readFromFile(const string& filename);
    std::vector<T*> getAllEmployees() const;
};

// Implementations of template functions (moved from .cpp file to header)

template<typename T>
LinkedList<T>::LinkedList() : head(nullptr) {}

template<typename T>
void LinkedList<T>::add(T* employee) {
    Node* newNode = new Node(employee);
    if (head == nullptr || dynamic_cast<Manager*>(employee)) {
        newNode->next = head;
        head = newNode;
    }
    else {
        Node* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

template<typename T>
void LinkedList<T>::deleteAt(int i) {
    if (head == nullptr) return;
    Node* temp = head;
    if (i == 0) {
        head = temp->next;
        delete temp;
        return;
    }
    for (int j = 0; temp != nullptr && j < i - 1; j++) {
        temp = temp->next;
    }
    if (temp == nullptr || temp->next == nullptr) return;
    Node* next = temp->next->next;
    delete temp->next;
    temp->next = next;
}

template<typename T>
void LinkedList<T>::insertAt(int i) {
    assert(head);

    string name, gender, id;
    int age;
    char type;

    cout << "请输入新员工的姓名、性别、年龄、工号: ";
    cin >> name >> gender >> age >> id;

    cout << "输入新员工类型（T表示技术员，M表示经理）: ";
    cin >> type;

    Employee* newEmployee;
    if (type == 'T') {
        newEmployee = new Technician(name, gender, age, id);
    }
    else if (type == 'M') {
        newEmployee = new Manager(name, gender, age, id);
    }
    else {
        cout << "无效的员工类型!" << endl;
        return;
    }

    newEmployee->computeSalary();

    Node* newNode = new Node(newEmployee);
    if (i == 0) {
        newNode->next = head;
        head = newNode;
        return;
    }

    Node* temp = head;
    for (int j = 0; temp != nullptr && j < i - 1; j++) {
        temp = temp->next;
    }
    if (temp == nullptr) {
        cout << "插入位置超出链表范围!" << endl;
        delete newNode;
        return;
    }
    newNode->next = temp->next;
    temp->next = newNode;
}

template<typename T>
void LinkedList<T>::printList() {
    Node* temp = head;
    while (temp != nullptr) {
        temp->data->printInfo();
        temp = temp->next;
    }
}

template<typename T>
void LinkedList<T>::writeToFile(const string& filename) {
    ofstream file(filename, ios::binary);
    Node* temp = head;
    while (temp != nullptr) {
        file.write(reinterpret_cast<char*>(temp->data), sizeof(*temp->data));
        temp = temp->next;
    }
    file.close();
}

template<typename T>
void LinkedList<T>::readFromFile(const string& filename) {
    ifstream file(filename, ios::binary);
    while (file.peek() != EOF) {
        Employee* emp;
        file.read(reinterpret_cast<char*>(&emp), sizeof(Employee));
        emp->printInfo();
    }
    file.close();
}

template<typename T>
std::vector<T*> LinkedList<T>::getAllEmployees() const {
    std::vector<T*> employees;
    Node* temp = head;
    while (temp != nullptr) {
        employees.push_back(temp->data);
        temp = temp->next;
    }
    return employees;
}

template<typename T>
LinkedList<T>::~LinkedList() {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp->data;
        delete temp;
    }
}
