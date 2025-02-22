#include <iostream>
#include <memory>

// 支付渠道接口（实现部分）
class PaymentChannel {
public:
	virtual void processPayment(float amount) const = 0;
	virtual ~PaymentChannel() = default;
};

// 国内支付
class DomesticPayment : public PaymentChannel {
public:
	void processPayment(float amount) const override {
		std::cout << "Processing domestic payment of ￥" << amount << std::endl;
	}
};

// 国际支付
class InternationalPayment : public PaymentChannel {
public:
	void processPayment(float amount) const override {
		std::cout << "Processing international payment of $" << amount << std::endl;
	}
};

// 支付方式接口（抽象部分）
class PaymentMethod {
protected:
	std::unique_ptr<PaymentChannel> channel;  // 使用 unique_ptr 管理资源

public:
	explicit PaymentMethod(std::unique_ptr<PaymentChannel> channel)
		: channel(std::move(channel)) {}
	virtual void pay(float amount) const = 0;
	virtual ~PaymentMethod() = default;
};

// 支付宝支付
class Alipay : public PaymentMethod {
public:
	explicit Alipay(std::unique_ptr<PaymentChannel> channel)
		: PaymentMethod(std::move(channel)) {}

	void pay(float amount) const override {
		std::cout << "Using Alipay: ";
		channel->processPayment(amount);  // 调用支付渠道的处理逻辑
	}
};

// 微信支付
class WechatPay : public PaymentMethod {
public:
	explicit WechatPay(std::unique_ptr<PaymentChannel> channel)
		: PaymentMethod(std::move(channel)) {}

	void pay(float amount) const override {
		std::cout << "Using WechatPay: ";
		channel->processPayment(amount);  // 调用支付渠道的处理逻辑
	}
};

int main() {
	// 创建支付方式，并绑定支付渠道
	auto alipayDomestic = std::make_unique<Alipay>(std::make_unique<DomesticPayment>());
	auto wechatInternational = std::make_unique<WechatPay>(std::make_unique<InternationalPayment>());

	// 用户支付
	alipayDomestic->pay(100.0f);       // 使用支付宝进行国内支付
	wechatInternational->pay(200.0f);  // 使用微信支付进行国际支付

	return 0;
}