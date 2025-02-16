#include <iostream>
#include <string>
#include <vector>
#include <memory>

// 中介接口
class Mediator;

// 同事类接口
class Colleague {
public:
	virtual void setMediator(Mediator* mediator) = 0;
	virtual void sendMessage(const std::string& message) = 0;
	virtual void receiveMessage(const std::string& message) = 0;
	virtual ~Colleague() = default; // 添加虚析构函数以正确释放派生类
};

// 中介者接口
class Mediator {
public:
	virtual void sendMessage(Colleague* colleague, const std::string& message) = 0;
	virtual void addColleague(std::shared_ptr<Colleague> colleague) = 0;
	virtual ~Mediator() = default; // 添加虚析构函数以正确释放派生类
};

// 具体同事类A
class ConcreteColleagueA : public Colleague {
private:
	Mediator* mediator;
public:
	void setMediator(Mediator* mediator) override {
		this->mediator = mediator;
	}

	void sendMessage(const std::string& message) override {
		std::cout << "ConcreteColleagueA sends message: " << message << std::endl;
		mediator->sendMessage(this, message);
	}

	void receiveMessage(const std::string& message) override {
		std::cout << "ConcreteColleagueA receives message: " << message << std::endl;
	}
};

// 具体同事类B
class ConcreteColleagueB : public Colleague {
private:
	Mediator* mediator;
public:
	void setMediator(Mediator* mediator) override {
		this->mediator = mediator;
	}

	void sendMessage(const std::string& message) override {
		std::cout << "ConcreteColleagueB sends message: " << message << std::endl;
		mediator->sendMessage(this, message);
	}

	void receiveMessage(const std::string& message) override {
		std::cout << "ConcreteColleagueB receives message: " << message << std::endl;
	}
};

// 具体中介
class ConcreteMediator : public Mediator {
private:
	std::vector<std::shared_ptr<Colleague>> colleagues;
public:
	void addColleague(std::shared_ptr<Colleague> colleague) override {
		colleagues.push_back(colleague);
		colleague->setMediator(this);
	}

	void sendMessage(Colleague* sender, const std::string& message) override {
		for (const auto& colleague : colleagues) {
			// 不发送给发送者自己
			if (colleague.get() != sender) {
				colleague->receiveMessage(message);
			}
		}
	}
};

int main() {
	

	// 创建中介者
	auto mediator = std::make_shared<ConcreteMediator>();

	// 创建同事并进行协作
	auto colleagueA = std::make_shared<ConcreteColleagueA>();
	auto colleagueB = std::make_shared<ConcreteColleagueB>();

	mediator->addColleague(colleagueA);
	mediator->addColleague(colleagueB);

	colleagueA->sendMessage("Hello, B!");
	colleagueB->sendMessage("Hello, A!");

	return 0;
}