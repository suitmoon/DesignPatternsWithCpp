#include <iostream>
#include <string>
#include <vector>
#include <memory>    
#include <algorithm> 

// 抽象组件：定义文件系统的公共接口
class FileSystemComponent {
public:
	virtual ~FileSystemComponent() = default;
	virtual void display(int depth = 0) const = 0; // 显示文件或目录
};

// 叶子节点：文件
class File : public FileSystemComponent {
private:
	std::string name;

public:
	File(std::string name) : name(std::move(name)) {}

	void display(int depth = 0) const override {
		std::string indent(depth, ' '); // 使用空格作为缩进
		std::cout << indent << "File: " << name << std::endl;
	}
};

// 组合节点：目录
class Directory : public FileSystemComponent {
private:
	std::string name;
	std::vector<std::unique_ptr<FileSystemComponent>> children; // 使用 unique_ptr 管理子节点

public:
	Directory(std::string name) : name(std::move(name)) {}

	// 添加子节点（转移所有权）
	void add(std::unique_ptr<FileSystemComponent> component) {
		children.push_back(std::move(component));
	}

	// 移除子节点（通过指针值查找）
	void remove(FileSystemComponent* target) {
		auto it = std::find_if(children.begin(), children.end(),
			[target](const std::unique_ptr<FileSystemComponent>& child) {
			return child.get() == target;
		});

		if (it != children.end()) {
			children.erase(it); // unique_ptr 会自动释放内存
		}
	}

	// 获取子节点
	FileSystemComponent* get_child(size_t index) {
		if (index < children.size()) {
			return children[index].get();
		}
		return nullptr;
	}

	void display(int depth = 0) const override {
		std::string indent(depth, ' '); // 使用空格作为缩进
		std::cout << indent << "Directory: " << name << std::endl;

		// 递归显示子节点
		for (const auto& child : children) {
			child->display(depth + 2);
		}
	}
};

// 客户端代码
int main() {
	// 创建根目录
	auto root = std::make_unique<Directory>("Root");

	// 创建子目录和文件
	auto subDir1 = std::make_unique<Directory>("SubDir1");
	auto subDir2 = std::make_unique<Directory>("SubDir2");
	auto file1 = std::make_unique<File>("file1.txt");
	auto file2 = std::make_unique<File>("file2.txt");
	auto file3 = std::make_unique<File>("file3.txt");

	// 构建树形结构（所有权转移）
	subDir1->add(std::move(file1));
	subDir1->add(std::move(file2));
	subDir2->add(std::move(file3));

	root->add(std::move(subDir1));
	root->add(std::move(subDir2));

	// 显示初始结构
	std::cout << "Initial structure:" << std::endl;
	root->display();

	// 移除一个文件
	auto* targetDir = dynamic_cast<Directory*>(root->get_child(0)); // 确保我们获取的是 Directory 类型
	if (targetDir) {
		auto* targetFile = targetDir->get_child(0); // 获取第一个子目录的第一个文件
		if (targetFile) {
			targetDir->remove(targetFile); // 移除文件
		}
	}

	// 显示更新后的结构
	std::cout << "\nAfter removal:" << std::endl;
	root->display();

	return 0;
}