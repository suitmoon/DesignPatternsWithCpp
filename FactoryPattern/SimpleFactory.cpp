#include <iostream>
#include <memory>
#include <string>
#include <vector>

// 抽象产品类
class Shape {
public:
	virtual void draw() = 0; // 纯虚函数
	virtual ~Shape() = default; // 虚析构函数
};

// 具体产品类
class Circle : public Shape {
public:
	void draw() override {
		std::cout << "Drawing a Circle !" << std::endl;
	}
};

class Square : public Shape {
public:
	void draw() override {
		std::cout << "Drawing a Square !" << std::endl;
	}
};

class Triangle : public Shape {
public:
	void draw() override {
		std::cout << "Drawing a Triangle !" << std::endl;
	}
};

// 工厂类
class ShapeFactory {
public:
	// 创建对象的静态方法，根据输入的字符串生成对应的对象
	static std::unique_ptr<Shape> createShape(const std::string& shapeType) {
		if (shapeType == "Circle") {
			return std::make_unique<Circle>();
		}
		else if (shapeType == "Square") {
			return std::make_unique<Square>();
		}
		else if (shapeType == "Triangle") {
			return std::make_unique<Triangle>();
		}
		return nullptr; // 返回空指针，表示未知类型

	}
};


int main() {
	std::vector<std::string> shapes= { "Circle","Square","Triangle" };
	for (size_t i = 0; i < 3; i++){
	// 使用工厂创建对象
	std::unique_ptr<Shape> shape = ShapeFactory::createShape(shapes[i]);

	if (shape) {
		shape->draw(); // 调用绘制方法
	}
	else {
		std::cout << "Unknown shape type!" << std::endl;
	}	
	}

	return 0;
}