#include <iostream>
#include <memory>
#include <string>

// 产品类
class House {
public:
	std::string walls;
	std::string roof;
	std::string foundation;

	void show() {
		std::cout << "House with " << walls << ", " << roof << ", and " << foundation << "." << std::endl;
	}
};

// 抽象建造者
class HouseBuilder {
public:
	virtual void buildWalls() = 0;
	virtual void buildRoof() = 0;
	virtual void buildFoundation() = 0;
	virtual std::unique_ptr<House> getResult() = 0;
	virtual ~HouseBuilder() = default;  // 确保有虚析构函数
};

// 具体建造者
class ConcreteHouseBuilder : public HouseBuilder {
private:
	std::unique_ptr<House> house;

public:
	ConcreteHouseBuilder() {
		house = std::make_unique<House>();
	}

	void buildWalls() override {
		house->walls = "brick walls";
	}

	void buildRoof() override {
		house->roof = "sloped roof";
	}

	void buildFoundation() override {
		house->foundation = "concrete foundation";
	}

	std::unique_ptr<House> getResult() override {
		return std::move(house);  // 转移所有权
	}
};

// 指挥者
class Director {
private:
	std::unique_ptr<HouseBuilder> builder;

public:
	Director(std::unique_ptr<HouseBuilder> builder) : builder(std::move(builder)) {}

	void construct() {
		builder->buildFoundation();
		builder->buildWalls();
		builder->buildRoof();
	}

	std::unique_ptr<House> getHouse() {
		return builder->getResult();  // 允许获取构建好的房子
	}
};

int main() {
	// 创建具体的建造者
	auto builder = std::make_unique<ConcreteHouseBuilder>();
	Director director(std::move(builder));  // 将建造者的所有权转交给指挥者

	director.construct();  // 执行构建步骤

	// 通过指挥者获取构建的房子
	std::unique_ptr<House> house = director.getHouse();
	house->show();  // 展示房子的细节

	return 0; 
}