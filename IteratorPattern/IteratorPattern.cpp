#include <iostream>
#include <vector>
#include <string>
#include <memory>

// 抽象迭代器
template<typename T>
class Iterator {
public:
	virtual ~Iterator() {}
	virtual bool hasNext() = 0;
	virtual T& next() = 0;
};

// 具体迭代器
template<typename T>
class ConcreteIterator : public Iterator<T> {
private:
	std::vector<T>& collection;
	size_t index;

public:
	ConcreteIterator(std::vector<T>& collection) : collection(collection), index(0) {}

	bool hasNext() override {
		return index < collection.size();
	}

	T& next() override {
		return collection[index++];
	}
};

// 员工类
class Employee {
public:
	Employee(int id, const std::string& name) : id(id), name(name) {}

	int getId() const { return id; }
	std::string getName() const { return name; }

private:
	int id;
	std::string name;
};

// 抽象聚合类
class Aggregate {
public:
	virtual ~Aggregate() {}
	virtual Iterator<Employee>* createIterator() = 0;
};

// 具体聚合类：部门
class Department : public Aggregate {
private:
	std::vector<Employee> employees;

public:
	void addEmployee(const Employee& employee) {
		employees.push_back(employee);
	}

	Iterator<Employee>* createIterator() override {
		return new ConcreteIterator<Employee>(employees);
	}
};

// 公司类
class Company {
private:
	std::vector<std::unique_ptr<Department>> departments;

public:
	void addDepartment(std::unique_ptr<Department> department) {
		departments.push_back(std::move(department));
	}

	void listEmployees() {
		for (const auto& department : departments) {
			Iterator<Employee>* iterator = department->createIterator();
			std::cout << "Employees in department:" << std::endl;
			while (iterator->hasNext()) {
				Employee& emp = iterator->next();
				std::cout << "Employee ID: " << emp.getId() << ", Name: " << emp.getName() << std::endl;
			}
			delete iterator;
		}
	}
};

int main() {
	Company company;

	auto dept1 = std::make_unique<Department>();
	dept1->addEmployee(Employee(1, "Alice"));
	dept1->addEmployee(Employee(2, "Bob"));

	auto dept2 = std::make_unique<Department>();
	dept2->addEmployee(Employee(3, "Charlie"));
	dept2->addEmployee(Employee(4, "David"));

	company.addDepartment(std::move(dept1));
	company.addDepartment(std::move(dept2));

	company.listEmployees();

	return 0;
}