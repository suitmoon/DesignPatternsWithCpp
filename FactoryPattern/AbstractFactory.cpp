#include <iostream>
#include <memory>

// 抽象产品：形状
class Shape {
public:
	virtual void draw() const = 0; // 纯虚函数：绘制形状
	virtual ~Shape() = default; // 虚析构函数
};

// 抽象产品：颜色
class Color {
public:
	virtual void fill() const = 0; // 纯虚函数：填充颜色
	virtual ~Color() = default; // 虚析构函数
};

// 具体产品：圆形
class Circle : public Shape {
public:
	void draw() const override {
		std::cout << "Circle" << std::endl;
	}
};

// 具体产品：正方形
class Square : public Shape {
public:
	void draw() const override {
		std::cout << "Square" << std::endl;
	}
};

// 具体产品：红色
class Red : public Color {
public:
	void fill() const override {
		std::cout << " Red " ;
	}
};

// 具体产品：蓝色
class Blue : public Color {
public:
	void fill() const override {
		std::cout << " Blue " ;
	}
};

// 具体商品类：图形（形状和颜色的组合）
class Graphic {
private:
	std::unique_ptr<Shape> shape;
	std::unique_ptr<Color> color;

public:
	Graphic(std::unique_ptr<Shape> sh, std::unique_ptr<Color> cl)
		: shape(std::move(sh)), color(std::move(cl)) {}

	void draw() const {
		std::cout << "Now drawing a" ;
		color->fill();
		shape->draw();
		
	}
};

int main() {
	// 创建红色圆形
	Graphic redCircle(std::make_unique<Circle>(), std::make_unique<Red>());
	redCircle.draw(); 
	// 创建蓝色正方形
	Graphic blueSquare(std::make_unique<Square>(), std::make_unique<Blue>());
	blueSquare.draw(); 
	return 0;
}