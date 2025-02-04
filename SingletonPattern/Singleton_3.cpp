#include <iostream>
#include <mutex>

class Singleton {
public:
	// 获取实例
	static Singleton& getInstance() {
		// 使用 call_once 确保只初始化一次
		std::call_once(initInstanceFlag, &Singleton::initSingleton);
		return *instance;
	}

	void callMethod() {
		std::cout << "Singleton method called!" << std::endl;
	}

private:
	Singleton() = default;
	~Singleton() = default;

	// 禁止拷贝和赋值
	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;

	static Singleton* instance; // 使用指针来保存单例实例
	static std::once_flag initInstanceFlag; // 标记初始化是否完成

	static void initSingleton() {
		instance = new Singleton(); // 初始化实例
	}
};

// 初始化静态成员变量
Singleton* Singleton::instance = nullptr;
std::once_flag Singleton::initInstanceFlag;

int main() {
	Singleton& singleton = Singleton::getInstance();
	singleton.callMethod();
	return 0;
}