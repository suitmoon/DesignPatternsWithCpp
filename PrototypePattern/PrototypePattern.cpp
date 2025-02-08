#include <iostream>
#include <memory>

// 抽象原型类
class Prototype {
public:
	// 抽象克隆方法
	virtual std::unique_ptr<Prototype> clone() const = 0;  
	// 显示对象内容
	virtual void show() const = 0;
    // 虚析构函数
	virtual ~Prototype() = default;
};

// 具体原型类
class ConcretePrototype : public Prototype {
private:
	int value;  // 示例属性

public:
	ConcretePrototype(int v) : value(v) {}

	// 实现克隆方法
	std::unique_ptr<Prototype> clone() const override {
		// 返回自身的深拷贝
		return std::make_unique<ConcretePrototype>(*this);  
	}

	// show打印对象的内容和地址
	void show() const override {
		std::cout << "ConcretePrototype value: " << value
			<< ", Address: " << this << std::endl;  
	}
};

// 客户端代码示例
int main() {
	// 创建一个原型对象
	ConcretePrototype prototype(42);

	// 克隆原型对象
	std::unique_ptr<Prototype> cloneprototype = prototype.clone();

	// 显示原型对象和克隆对象的地址
	std::cout << "Original Object: ";
	prototype.show();  // 输出: 原始对象的内容和地址 

	std::cout << "Cloned Object: ";
	cloneprototype->show(); // 输出: 克隆对象的内容和地址

	return 0;
}