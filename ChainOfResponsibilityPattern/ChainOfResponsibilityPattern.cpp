#include <iostream>
#include <string>
#include <memory>


// 事件基类
class Event {
public:
	enum Type {
		MouseClick,
		MouseDoubleClick,
		KeyPress
	};

	Event(Type type) : type(type), accepted(false) {}

	Type getType() const { return type; }
	void accept() { accepted = true; }
	void ignore() { accepted = false; }
	bool isAccepted() const { return accepted; }

private:
	Type type;
	bool accepted;
};

// 自定义的鼠标点击事件
class MouseClickEvent : public Event {
public:
	MouseClickEvent() : Event(MouseClick) {}
};

// 自定义的鼠标双击事件
class MouseDoubleClickEvent : public Event {
public:
	MouseDoubleClickEvent() : Event(MouseDoubleClick) {}
};

// 自定义的键盘操作事件
class KeyPressEvent : public Event {
public:
	KeyPressEvent() : Event(KeyPress) {}
};

// 事件处理器基类
class EventHandler {
public:
	virtual ~EventHandler() {}

	void setNext(std::shared_ptr<EventHandler> nextHandler) {
		this->nextHandler = nextHandler;
	}

	virtual void handleEvent(Event* event) {
		if (nextHandler) {
			nextHandler->handleEvent(event);
		}
	}

protected:
	std::shared_ptr<EventHandler> nextHandler ;
};

// 具体的事件处理器
class HandlerA : public EventHandler {
public:
	void handleEvent(Event* event) override {
		if (event->getType() == Event::MouseClick) {
			// 处理鼠标点击事件
			std::cout << "Handler A handling Mouse Click Event." << std::endl;
			event->accept();  // 事件被处理
		}
		else {
			EventHandler::handleEvent(event);  // 传递给下一个处理器
		}
	}
};

class HandlerB : public EventHandler {
public:
	void handleEvent(Event* event) override {
		if (event->getType() == Event::MouseDoubleClick) {
			// 处理鼠标双击事件
			std::cout << "Handler B handling Mouse Double Click Event." << std::endl;
			event->accept();  // 事件被处理
		}
		else {
			EventHandler::handleEvent(event);  // 传递给下一个处理器
		}
	}
};

class HandlerC : public EventHandler {
public:
	void handleEvent(Event* event) override {
		if (event->getType() == Event::KeyPress) {
			// 处理键盘操作事件
			std::cout << "Handler C handling Key Press Event." << std::endl;
			event->accept();  // 事件被处理
		}
		else {
			EventHandler::handleEvent(event);
		}
	}
};

// 指挥者类用于发送事件
class EventDispatcher {
public:
	void dispatch(Event* event) {
		if (!event->isAccepted()) {
			// 触发事件
			firstHandler->handleEvent(event);
		}
	}

	void setFirstHandler(std::shared_ptr<EventHandler> handler) {
		firstHandler = handler;
	}

private:
	std::shared_ptr<EventHandler> firstHandler;
};

// 主函数
int main() {
	// 创建事件处理器
	std::shared_ptr<HandlerA> handlerA = std::make_shared<HandlerA>();
	std::shared_ptr<HandlerB> handlerB = std::make_shared<HandlerB>();
	std::shared_ptr<HandlerC> handlerC = std::make_shared<HandlerC>();

	// 构建责任链
	handlerA->setNext(handlerB);
	handlerB->setNext(handlerC);

	// 创建事件分发器
	EventDispatcher dispatcher;
	dispatcher.setFirstHandler(handlerA);

	// 创建并分发事件
	MouseClickEvent clickEvent;
	dispatcher.dispatch(&clickEvent);  // 处理鼠标点击事件

	MouseDoubleClickEvent doubleClickEvent;
	dispatcher.dispatch(&doubleClickEvent); // 处理鼠标双击事件

	KeyPressEvent keyPressEvent;
	dispatcher.dispatch(&keyPressEvent); // 处理键盘操作事件


	return 0;
}