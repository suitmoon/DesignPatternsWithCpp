#include <iostream>
#include <memory>

// 状态接口
class State {
public:
	virtual void read() = 0;     // 读取操作
	virtual void write() = 0;    // 写入操作
};

// 具体状态：只读状态
class ReadOnlyState : public State {
public:
	void read() override {
		std::cout << "Reading from the file..." << std::endl;
	}

	void write() override {
		std::cout << "Cannot write: The file is in read-only mode." << std::endl;
	}
};

// 具体状态：独写状态
class WriteOnlyState : public State {
public:
	void read() override {
		std::cout << "Cannot read: The file is in write-only mode." << std::endl;
	}

	void write() override {
		std::cout << "Writing to the file..." << std::endl;
	}
};

// 具体状态：读写状态
class ReadWriteState : public State {
public:
	void read() override {
		std::cout << "Reading from the file..." << std::endl;
	}

	void write() override {
		std::cout << "Writing to the file..." << std::endl;
	}
};

// 上下文类：文件
class File {
private:
	std::unique_ptr<State> currentState;  // 当前状态

public:
	File(std::unique_ptr<State> initialState) : currentState(std::move(initialState)) {}

	void setState(std::unique_ptr<State> newState) {
		currentState = std::move(newState);
	}

	void read() {
		currentState->read(); // 调用当前状态的读取行为
	}

	void write() {
		currentState->write(); // 调用当前状态的写入行为
	}
};

int main() {
	// 创建文件，初始状态为只读
	File file(std::make_unique<ReadOnlyState>());

	file.read();   // 输出: Reading from the file...
	file.write();  // 输出: Cannot write: The file is in read-only mode.

	// 切换到独写状态
	file.setState(std::make_unique<WriteOnlyState>());
	file.read();   // 输出: Cannot read: The file is in write-only mode.
	file.write();  // 输出: Writing to the file...

	// 切换到读写状态
	file.setState(std::make_unique<ReadWriteState>());
	file.read();   // 输出: Reading from the file...
	file.write();  // 输出: Writing to the file...

	return 0;
}