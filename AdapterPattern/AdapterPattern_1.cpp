// 对象适配器（使用组合）
#include <string>
#include <memory>
#include <iostream>

class NewLogger {
public:
	virtual void log(const std::string& message) = 0;
	virtual ~NewLogger() = default;
};

class OldLogger {
public:
	void logMessage(const std::string& message) {
		std::cout<< message  << "by Old Logger " << std::endl;
	}
};
class LoggerAdapter : public NewLogger {
private:
	OldLogger oldLogger;

public:
	void log(const std::string& message) override {
		oldLogger.logMessage(message);  // 调用旧日志系统的方法
	}
};

int main() {
	// 使用新的日志接口
	std::unique_ptr<NewLogger> logger = std::make_unique<LoggerAdapter>();
	logger->log("This is a log message ");  // 通过适配器调用旧日志系统
	return 0;
}