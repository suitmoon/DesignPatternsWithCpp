#include <iostream>
#include <string>
#include <memory>
#include <vector>

// 抽象表达式
class Expression {
public:
	virtual int interpret() = 0;
	virtual ~Expression() = default;
};

// 终结符表达式：数字
class NumberExpression : public Expression {
private:
	int number;
public:
	explicit NumberExpression(int num) : number(num) {}
	int interpret() override {
		return number;
	}
};

// 非终结符表达式：加法
class AddExpression : public Expression {
private:
	std::shared_ptr<Expression> left;
	std::shared_ptr<Expression> right;
public:
	AddExpression(std::shared_ptr<Expression> l, std::shared_ptr<Expression> r)
		: left(std::move(l)), right(std::move(r)) {}
	int interpret() override {
		return left->interpret() + right->interpret();
	}
};

// 非终结符表达式：减法
class SubtractExpression : public Expression {
private:
	std::shared_ptr<Expression> left;
	std::shared_ptr<Expression> right;
public:
	SubtractExpression(std::shared_ptr<Expression> l, std::shared_ptr<Expression> r)
		: left(std::move(l)), right(std::move(r)) {}
	int interpret() override {
		return left->interpret() - right->interpret();
	}
};

// 解析器
class Parser {
private:
	std::vector<std::string> tokens;
	size_t pos = 0;

	std::shared_ptr<Expression> parseExpression() {
		auto left = parseTerm();
		while (pos < tokens.size()) {
			std::string token = tokens[pos];
			if (token == "+") {
				pos++;
				auto right = parseTerm();
				left = std::make_shared<AddExpression>(left, right);
			}
			else if (token == "-") {
				pos++;
				auto right = parseTerm();
				left = std::make_shared<SubtractExpression>(left, right);
			}
			else {
				break;
			}
		}
		return left;
	}

	std::shared_ptr<Expression> parseTerm() {
		std::string token = tokens[pos++];
		return std::make_shared<NumberExpression>(std::stoi(token));
	}

public:

	explicit Parser(const std::string& input) {
		// 简单的分词逻辑，假设输入格式正确
		size_t start = 0;
		for (size_t i = 0; i < input.size(); ++i) {
			if (input[i] == ' ') {
				if (i > start) {
					tokens.push_back(input.substr(start, i - start));
				}
				start = i + 1;
			}
			else if (input[i] == '+' || input[i] == '-') {
				if (i > start) {
					tokens.push_back(input.substr(start, i - start));
				}
				tokens.push_back(std::string(1, input[i]));
				start = i + 1;
			}
		}
		if (start < input.size()) {
			tokens.push_back(input.substr(start));
		}
	}

	std::shared_ptr<Expression> parse() {
		return parseExpression();
	}

};

int main() {
	std::string input = "1+ 2 - 13 + 1";
	Parser parser(input);
	std::shared_ptr<Expression> expression = parser.parse();
	std::cout << "Result: " << expression->interpret() << std::endl; // 输出Result
	return 0;
}