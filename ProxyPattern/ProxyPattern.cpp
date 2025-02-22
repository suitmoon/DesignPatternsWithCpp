#include <iostream>
#include <string>

// 抽象接口：页面访问
class PageAccess {
public:
	virtual void access(const std::string& page) = 0;
	virtual ~PageAccess() = default;
};

// 真实对象：实际页面访问
class RealPageAccess : public PageAccess {
public:
	void access(const std::string& page) override {
		std::cout << "Accessing page: " << page << std::endl;
	}
};

// 代理对象：控制页面访问权限
class PageAccessProxy : public PageAccess {
private:
	RealPageAccess realPageAccess;
	std::string userType;

public:
	PageAccessProxy(const std::string& userType) : userType(userType) {}

	void access(const std::string& page) override {
		if (canAccess(page)) {
			realPageAccess.access(page);
		}
		else {
			std::cout << "Access denied: You do not have permission to access " << page << std::endl;
		}
	}

private:
	bool canAccess(const std::string& page) {
		if (page == "Index") {
			return true;  // 所有用户都可以访问主页面
		}
		else if (page == "UserCenter") {
			return userType == "User" || userType == "Admin";  // 普通用户和管理员可以访问用户中心
		}
		else if (page == "AdminPage") {
			return userType == "Admin";  // 只有管理员可以访问管理页面
		}
		return false;
	}
};

// 客户端代码
int main() {
	// 普通用户
	PageAccessProxy userProxy("User");
	userProxy.access("Index");       // 允许访问
	userProxy.access("UserCenter"); // 允许访问
	userProxy.access("AdminPage");  // 拒绝访问

	// 管理员
	PageAccessProxy adminProxy("Admin");
	adminProxy.access("Index");       // 允许访问
	adminProxy.access("UserCenter"); // 允许访问
	adminProxy.access("AdminPage");  // 允许访问

	// 游客
	PageAccessProxy guestProxy("Guest");
	guestProxy.access("Index");       // 允许访问
	guestProxy.access("UserCenter"); // 拒绝访问
	guestProxy.access("AdminPage");  // 拒绝访问

	return 0;
}