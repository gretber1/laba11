#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>      
#include <windows.h>

using namespace std;
class Employee {
private:
    int id;
    string name;
    string position;
    double salary;


    static set<int> usedIds;

public:
    Employee(int id, string name, string position, double salary) {
        if (id <= 0) {
            cout << "Оооо, ID не может быть меньше или равен нулю!\n"
                         "Я поставил, "<< name <<" теперь имеет ID = 1 по умолчанию.\n";
            id = 1;
        }

        if (usedIds.find(id) != usedIds.end()) {
            cout << "Оооо, а тут ID-то не может одинаковый быть у сотрудников! "
                         "Я поменял ID на новый уникальный.\n";
            
            int newId = 1;
            while (usedIds.find(newId) != usedIds.end())
                newId++;
            id = newId;
            cout << name << " теперь имеет ID = " << id << endl;
        }
        usedIds.insert(id);

        if (salary < 1 || salary > 10000000) {
            cout << "Оооо, зарплата должна быть от 1 до 10 000 000! "
                         "Я поставил 1000 по умолчанию.\n";
            salary = 1000;
        }

        this->id = id;
        this->name = name;
        this->position = position;
        this->salary = salary;
    }

    int getId() const { return id; }
    string getName() const { return name; }
    string getPosition() const { return position; }
    double getSalary() const { return salary; }

    void displayInfo() const {
        cout << "ID: " << id << ", Имя: " << name << ", Должность: " << position << ", Зарплата: " << salary << endl;
    }
};


set<int> Employee::usedIds;

class HRDepartment {
private:
    vector<Employee> employees;

    HRDepartment() {}

public:
    HRDepartment(const HRDepartment&) = delete;
    HRDepartment& operator=(const HRDepartment&) = delete;

    static HRDepartment& getInstance() {
        static HRDepartment instance;
        return instance;
    }

    void addEmployee(const Employee& e) {
        employees.push_back(e);
    }


    void removeEmployee(int id) {
        employees.erase(remove_if(employees.begin(), employees.end(), [id](const Employee& e) {return e.getId() == id;}), employees.end());
    }


    void showAll() const {
        if (employees.empty()) {
            cout << "Нет сотрудников в отделе кадров.\n";
            return;
        }

        for (const auto& e : employees)
            e.displayInfo();
    }
};


int main() {
    SetConsoleOutputCP(CP_UTF8);

    HRDepartment& hr = HRDepartment::getInstance();
    HRDepartment& hr2 = HRDepartment::getInstance();

    hr.addEmployee(Employee(1, "Иван Иванов", "Менеджер", 50000));
    hr.addEmployee(Employee(2, "Петр Петров", "Инженер", 60000));
    hr.addEmployee(Employee(2, "Анна Смирнова", "Бухгалтер", 55000)); // повтор ID
    hr.addEmployee(Employee(-5, "Вася Пупкин", "Тестировщик", 70000)); // некорректный ID
    hr.addEmployee(Employee(5, "Ольга Кузнецова", "Тикток аналитик", 20000000)); // слишком большая зп
    

    cout << "\nСписок сотрудников:\n";
    hr.showAll();
    hr2.addEmployee(Employee(6, "sana", "Менеджер", 50000));
    cout << "\nСписок сотрудников:\n";
    hr.showAll();
    hr.removeEmployee(2);

    cout << "\nПосле удаления:\n";
    hr.showAll();

    return 0;
}
