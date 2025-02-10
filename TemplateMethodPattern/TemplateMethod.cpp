#include <iostream>
#include <string>

template <typename T>
class TemplateMethod {
public:
	// 执行模板方法
	void execute(const T& data) {
		stepOne(data);
		stepTwo(data);
		stepThree(data);
	}

protected:
	// 抽象步骤，必须由子类实现
	virtual void stepOne(const T& data) {
		std::cout << "Default step one implementation with data: " << data << std::endl;
	}

	virtual void stepTwo(const T& data) = 0; // 纯虚函数

	virtual void stepThree(const T& data) {
		std::cout << "Default step three implementation with data: " << data << std::endl;
	}
};

class ConcreteClassInt : public TemplateMethod<int> {
protected:
	void stepOne(const int& data) override {
		std::cout << "ConcreteClassInt: Step one implementation with data: " << data << std::endl;
	}

	void stepTwo(const int& data) override {
		std::cout << "ConcreteClassInt: Step two implementation with data: " << data * 2 << std::endl;
	}
};

class ConcreteClassString : public TemplateMethod<std::string> {
protected:
	void stepOne(const std::string& data) override {
		std::cout << "ConcreteClassString: Step one implementation with data: " << data << std::endl;
	}

	void stepTwo(const std::string& data) override {
		std::cout << "ConcreteClassString: Step two implementation with data length: " << data.length() << std::endl;
	}

	void stepThree(const std::string& data) override {
		std::cout << "ConcreteClassString: Custom step three implementation with data: " << data << std::endl;
	}
};

int main() {
	ConcreteClassInt instanceInt;
	instanceInt.execute(42); // 传递一个整数

	std::cout << std::endl;

	ConcreteClassString instanceString;
	instanceString.execute("Hello World"); // 传递一个字符串

	return 0;
}