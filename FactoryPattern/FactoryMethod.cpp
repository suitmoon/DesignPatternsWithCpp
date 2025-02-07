#include <iostream>
#include <memory>

// 抽象产品类
class Shape {
public:
	virtual void draw() const = 0; // 纯虚函数，绘制形状
	virtual ~Shape() = default; // 虚析构函数
};

// 具体产品类：圆形
class Circle : public Shape {
public:
	void draw() const override {
		std::cout << "Drawing a Circle" << std::endl;
	}
};

// 具体产品类：正方形
class Square : public Shape {
public:
	void draw() const override {
		std::cout << "Drawing a Square" << std::endl;
	}
};

// 抽象工厂类
class ShapeFactory {
public:
	virtual std::unique_ptr<Shape> createShape() const = 0; // 工厂方法
	virtual ~ShapeFactory() = default; // 虚析构函数
};

// 具体工厂类：圆形工厂
class CircleFactory : public ShapeFactory {
public:
	std::unique_ptr<Shape> createShape() const override {
		return std::make_unique<Circle>();
	}
};

// 具体工厂类：正方形工厂
class SquareFactory : public ShapeFactory {
public:
	std::unique_ptr<Shape> createShape() const override {
		return std::make_unique<Square>();
	}
};

// 客户端代码
int main() {
	// 创建圆形工厂
	std::unique_ptr<ShapeFactory> circleFactory = std::make_unique<CircleFactory>();
	std::unique_ptr<Shape> circle = circleFactory->createShape();
	circle->draw(); // 输出 "Drawing a Circle"

	// 创建正方形工厂
	std::unique_ptr<ShapeFactory> squareFactory = std::make_unique<SquareFactory>();
	std::unique_ptr<Shape> square = squareFactory->createShape();
	square->draw(); // 输出 "Drawing a Square"

	return 0;
}