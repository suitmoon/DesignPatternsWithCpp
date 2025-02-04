#include <iostream>
#include <mutex>

class Singleton {
public:

	// 获取实例
	static Singleton& getInstance() {		

		/* 
		单重检查
		  在单重检查中，每次获取单例实例时都会首先检查实例是否已经被创建。
		  如果没有，直接进入锁定区域再进行创建。
		  每次调用 getInstance() 方法时，都会进行锁定，这在高频调用时会造成性能损失。
		双重检查锁定
		  可以减少对锁的占用时间，只有在实例未被创建时才会锁定，高并发下性能更好。
		  在大多数情况下，这会减少加锁的开销，提高性能。
		*/
		if (!instance) { // 第一次检查
			std::lock_guard<std::mutex> lock(mutex_); // 锁定
			if (!instance) { // 第二次检查
				instance = new Singleton(); // 创建实例
			}
		}
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

	static Singleton* instance; // 使用指针来实现懒汉式
	static std::mutex mutex_;   // 用于保护访问

};

// 初始化静态成员变量
Singleton* Singleton::instance = nullptr;
std::mutex Singleton::mutex_;


int main() {
	Singleton& singleton = Singleton::getInstance();
	singleton.callMethod();
	return 0;
}