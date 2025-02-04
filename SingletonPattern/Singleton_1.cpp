#include <iostream>


class Singleton {
public:

	// 获取实例
	static Singleton& getInstance() {		
		return instance;
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

	static Singleton instance; 
};

// 静态成员变量是全局性的,必须在类外进行定义和初始化
	Singleton Singleton::instance; 

int main() {
	Singleton& singleton = Singleton::getInstance();
	singleton.callMethod();
	return 0;
}