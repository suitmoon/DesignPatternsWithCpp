#include <iostream>
#include <memory>
#include <string>

// 组件接口：订单
class Order {
public:
	virtual float getTotalPrice() const = 0;  // 计算总价
	virtual std::string getDescription() const = 0;  // 获取订单详情
	virtual ~Order() = default;
};

// 具体组件：基础订单
class BasicOrder : public Order {
private:
	float basePrice;  // 基础价格

public:
	explicit BasicOrder(float price) : basePrice(price) {}

	float getTotalPrice() const override {
		return basePrice;  // 基础订单的总价
	}

	std::string getDescription() const override {
		return "Basic Order";  // 基础订单的描述
	}
};

// 装饰器基类
class OrderDecorator : public Order {
protected:
	std::shared_ptr<Order> order;  // 持有一个订单对象的引用

public:
	explicit OrderDecorator(std::shared_ptr<Order> order)
		: order(std::move(order)) {}

	float getTotalPrice() const override {
		return order->getTotalPrice();  // 默认行为：调用被装饰对象的方法
	}

	std::string getDescription() const override {
		return order->getDescription();  // 默认行为：调用被装饰对象的方法
	}
};

// 具体装饰器：加急配送
class ExpressDelivery : public OrderDecorator {
public:
	explicit ExpressDelivery(std::shared_ptr<Order> order)
		: OrderDecorator(std::move(order)) {}

	float getTotalPrice() const override {
		return order->getTotalPrice() + 20.0f;  // 加急配送增加 20 元
	}

	std::string getDescription() const override {
		return order->getDescription() + " + Express Delivery";  // 添加加急配送描述
	}
};

// 具体装饰器：礼品包装
class GiftWrap : public OrderDecorator {
public:
	explicit GiftWrap(std::shared_ptr<Order> order)
		: OrderDecorator(std::move(order)) {}

	float getTotalPrice() const override {
		return order->getTotalPrice() + 10.0f;  // 礼品包装增加 10 元
	}

	std::string getDescription() const override {
		return order->getDescription() + " + Gift Wrap";  // 添加礼品包装描述
	}
};

// 具体装饰器：发票打印
class InvoicePrint : public OrderDecorator {
public:
	explicit InvoicePrint(std::shared_ptr<Order> order)
		: OrderDecorator(std::move(order)) {}

	float getTotalPrice() const override {
		return order->getTotalPrice() + 5.0f;  // 发票打印增加 5 元
	}

	std::string getDescription() const override {
		return order->getDescription() + " + Invoice Print";  // 添加发票打印描述
	}
};

int main() {
	// 创建一个基础订单
	std::shared_ptr<Order> order = std::make_shared<BasicOrder>(100.0f);

	// 动态添加附加服务
	order = std::make_shared<ExpressDelivery>(order);  // 加急配送
	order = std::make_shared<GiftWrap>(order);         // 礼品包装
	order = std::make_shared<InvoicePrint>(order);     // 发票打印

	// 输出订单详情和总价
	std::cout << "Order Description: " << order->getDescription() << std::endl;
	std::cout << "Total Price: ￥" << order->getTotalPrice() << std::endl;

	return 0;
}