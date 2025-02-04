#include <iostream>
#include <mutex>
#include <memory> // 引入智能指针的头文件

class Singleton {
public:
	// 获取实例
	static std::shared_ptr<Singleton> getInstance() {
		std::call_once(initInstanceFlag, &Singleton::initSingleton);
		return instance; // 返回共享指针
	}

	void callMethod() {
		std::cout << "Singleton method called!" << std::endl;
	}

private:
	Singleton() = default; // 私有构造函数
	~Singleton() = default; // 私有析构函数

	// 禁止拷贝和赋值
	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;

	static std::shared_ptr<Singleton> instance; // 使用 std::shared_ptr 来保存单例实例
	static std::once_flag initInstanceFlag; // 标记初始化是否完成

	// 初始化单例实例的静态函数
	static void initSingleton() {		
		instance = std::shared_ptr<Singleton>(new Singleton(), [](Singleton* ptr) {
			// 自定义删除器
			std::cout << "Singleton instance is being deleted." << std::endl;
			delete ptr; // 释放实例内存
		});
	}
};

// 初始化静态成员变量
std::shared_ptr<Singleton> Singleton::instance = nullptr;
std::once_flag Singleton::initInstanceFlag;

int main() {
	std::shared_ptr<Singleton> singleton = Singleton::getInstance(); // 使用 std::shared_ptr
	singleton->callMethod(); // 调用方法
	return 0;
}