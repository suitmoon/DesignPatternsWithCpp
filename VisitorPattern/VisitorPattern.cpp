#include <iostream>
#include <vector>
#include <memory>

// 前向声明
class ConcreteElementA;
class ConcreteElementB;
class ConcreteVisitor;

// 访问者基类
class Visitor {
public:
	virtual ~Visitor() {}
	virtual void visit(ConcreteElementA& elementA) = 0; // 访问元素 A
	virtual void visit(ConcreteElementB& elementB) = 0; // 访问元素 B
};

// Element 接口
class Element {
public:
	virtual ~Element() {}
	virtual void accept(ConcreteVisitor& visitor) = 0; // 接受访问者
};

// 具体元素类 A
class ConcreteElementA : public Element {
public:
	void accept(ConcreteVisitor& visitor) override; // 声明，定义将在后面
	void operationA() {
		std::cout << "Operation A" << std::endl;
	}
};

// 具体元素类 B
class ConcreteElementB : public Element {
public:
	void accept(ConcreteVisitor& visitor) override; // 声明，定义将在后面
	void operationB() {
		std::cout << "Operation B" << std::endl;
	}
};

// 具体访问者
class ConcreteVisitor : public Visitor {
public:
	void visit(ConcreteElementA& elementA) override {
		std::cout << "Visiting ConcreteElementA" << std::endl;
		elementA.operationA(); // 对 A 元素进行操作
	}

	void visit(ConcreteElementB& elementB) override {
		std::cout << "Visiting ConcreteElementB" << std::endl;
		elementB.operationB(); // 对 B 元素进行操作
	}
};

// 具体元素 A 的实现
void ConcreteElementA::accept(ConcreteVisitor& visitor) {
	visitor.visit(*this);
}

// 具体元素 B 的实现
void ConcreteElementB::accept(ConcreteVisitor& visitor) {
	visitor.visit(*this);
}

int main() {
	std::vector<std::shared_ptr<Element>> elements;
	elements.push_back(std::make_shared<ConcreteElementA>());
	elements.push_back(std::make_shared<ConcreteElementB>());

	ConcreteVisitor visitor;

	for (auto element : elements) {
		element->accept(visitor); // 让访问者访问元素
	}

	return 0;
}