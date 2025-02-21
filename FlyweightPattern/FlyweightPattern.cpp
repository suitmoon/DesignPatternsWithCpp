#include <iostream>
#include <string>
#include <unordered_map>
#include <memory>

// 享元接口：字符对象
class Character {
public:
	virtual ~Character() = default;
	virtual void display(int position, const std::string& color, int size) const = 0; // 添加颜色和大小
};

// 具体享元：具体字符
class ConcreteCharacter : public Character {
private:
	char symbol; // 内部状态：字符本身

public:
	ConcreteCharacter(char symbol) : symbol(symbol) {}

	void display(int position, const std::string& color, int size) const override {
		std::cout << "Character: " << symbol
			<< ", Position: " << position
			<< ", Color: " << color
			<< ", Size: " << size << std::endl;
	}
};

// 享元工厂：管理字符对象
class CharacterFactory {
private:
	std::unordered_map<char, std::shared_ptr<Character>> characters; // 共享池

public:
	std::shared_ptr<Character> get_character(char symbol) {
		// 如果字符已存在，直接返回共享对象
		if (characters.find(symbol) != characters.end()) {
			return characters[symbol];
		}

		// 否则，创建新的字符对象并加入共享池
		auto new_character = std::make_shared<ConcreteCharacter>(symbol);
		characters[symbol] = new_character;
		return new_character;
	}
};

// 客户端代码
int main() {
	CharacterFactory factory;

	// 文本内容
	std::string text = "Hello,Flyweight!";

	// 渲染文本，设置颜色和大小
	std::string color = "red";
	int size = 25;

	for (size_t i = 0; i < text.size(); ++i) {
		char symbol = text[i];
		auto character = factory.get_character(symbol); // 获取或创建字符对象
		if (i>5)
		{
			color = "green";
			size = 10;
		}
		character->display(i, color, size); // 显示字符及其位置、颜色和大小
	}

	return 0;
}