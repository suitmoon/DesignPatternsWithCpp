#include <iostream>
#include <memory>
#include <string>

// 策略接口
class Strategy {
public:
	virtual void execute() = 0;  // 纯虚函数
	virtual ~Strategy() = default;  // 虚析构函数
};

// 具体策略 Linux
class LinuxStrategy : public Strategy {
public:
	void execute() override {
		std::cout << "Executing strategy for Linux" << std::endl;
	}
};

// 具体策略 Windows
class WindowsStrategy : public Strategy {
public:
	void execute() override {
		std::cout << "Executing strategy for Windows" << std::endl;
	}
};

// 具体策略 macOS
class MacOSStrategy : public Strategy {
public:
	void execute() override {
		std::cout << "Executing strategy for macOS" << std::endl;
	}
};

// 上下文
class Context {
private:
	std::unique_ptr<Strategy> strategy;  // 策略持有者

public:
	void setStrategy(std::unique_ptr<Strategy> new_strategy) {
		strategy = std::move(new_strategy);
	}

	void executeStrategy() {
		if (strategy) {
			strategy->execute();
		}
		else {
			std::cout << "Strategy not set!" << std::endl;
		}
	}
};

// 根据操作系统选择策略
std::unique_ptr<Strategy> createStrategy() {
#ifdef _WIN32
	return std::make_unique<WindowsStrategy>();
#elif __APPLE__
	return std::make_unique<MacOSStrategy>();
#elif __linux__
	return std::make_unique<LinuxStrategy>();
#else
	return nullptr; // 未知平台
#endif
}

int main() {
	Context context;

	// 根据当前平台选择策略
	std::unique_ptr<Strategy> strategy = createStrategy();
	context.setStrategy(std::move(strategy));

	// 执行策略
	context.executeStrategy();

	return 0;
}