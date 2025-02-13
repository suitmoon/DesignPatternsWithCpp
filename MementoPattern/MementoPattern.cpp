#include <iostream>
#include <string>
#include <memory>
#include <unordered_map>

// 备忘录类
class Memento {
public:
	explicit Memento(const std::string& state) : state_(state) {}
	std::string getState() const { return state_; }
private:
	std::string state_;
};

// 发起人类
class Originator {
public:
	void setState(const std::string& state) {
		state_ = state;
		std::cout << "Originator: Setting state to " << state_ << std::endl;
	}

	std::shared_ptr<Memento> saveStateToMemento() {
		std::cout << "Originator: Saving to Memento." << std::endl;
		return std::make_shared<Memento>(state_);
	}

	void getStateFromMemento(std::shared_ptr<Memento> memento) {
		state_ = memento->getState();
		std::cout << "Originator: State after restoring from Memento: " << state_ << std::endl;
	}

private:
	std::string state_;
};

// 管理员类
class Caretaker {
public:
	void addMemento(const std::string& name, std::shared_ptr<Memento> memento) {
		mementos_[name] = memento;
	}

	std::shared_ptr<Memento> getMemento(const std::string& name) {
		return mementos_.at(name);
	}

private:
	std::unordered_map<std::string, std::shared_ptr<Memento>> mementos_;
};

// 使用示例
int main() {
	Originator originator;
	Caretaker caretaker;

	originator.setState("State 1");
	caretaker.addMemento("First Save", originator.saveStateToMemento());

	originator.setState("State 2");
	caretaker.addMemento("Second Save", originator.saveStateToMemento());

	originator.setState("State 3");
	std::cout << "Current State: State 3" << std::endl;

	// 恢复到之前的状态
	originator.getStateFromMemento(caretaker.getMemento("Second Save")); // 恢复到 State 2
	originator.getStateFromMemento(caretaker.getMemento("First Save"));  // 恢复到 State 1

	return 0;
}