#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <memory> 

// 抽象观察者类
class Observer {
public:
	virtual void update(const std::string& message) = 0;
	virtual ~Observer() = default;
};

// 具体观察者类
class ConcreteObserver : public Observer {
public:
	ConcreteObserver(const std::string& name) : name(name) {}

	void update(const std::string& message) override {
		std::cout << "Observer " << name << " updated with message: " << message << std::endl;
	}

private:
	std::string name;
};

// 抽象主题类
class Subject {
public:
	virtual void attach(std::shared_ptr<Observer> observer) = 0;
	virtual void detach(std::shared_ptr<Observer> observer) = 0;
	virtual void notify(const std::string& message) = 0;
	virtual ~Subject() = default;
};

// 具体主题类
class ConcreteSubject : public Subject {
public:
	void attach(std::shared_ptr<Observer> observer) override {
		observers.push_back(observer);
	}

	void detach(std::shared_ptr<Observer> observer) override {
		observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
	}

	void notify(const std::string& message) override {
		for (const auto& observer : observers) {
			observer->update(message);
		}
	}

private:
	std::vector<std::shared_ptr<Observer>> observers; // 使用 shared_ptr 管理观察者
};

int main() {
	ConcreteSubject subject;

	// 使用智能指针来管理观察者的生命周期
	std::shared_ptr<Observer> observer1 = std::make_shared<ConcreteObserver>("Observer1");
	std::shared_ptr<Observer> observer2 = std::make_shared<ConcreteObserver>("Observer2");

	subject.attach(observer1);
	subject.attach(observer2);

	subject.notify("State has changed!");  // 通知所有观察者

	subject.detach(observer1);  // 移除一个观察者
	subject.notify("Another state change.");  // 通知剩下的观察者

	return 0;
}