#include <iostream>
#include <memory>
#include <vector>

// 命令接口
class Command {
public:
	virtual void execute() = 0;
	virtual ~Command() = default;
};

// 接收者
class Server {
public:
	void startService() {
		std::cout << "Starting server service..." << std::endl;
	}

	void stopService() {
		std::cout << "Stopping server service..." << std::endl;
	}

	void restartService() {
		std::cout << "Restarting server service..." << std::endl;
	}
};

// 具体命令
class StartServiceCommand : public Command {
private:
	Server& server;
public:
	StartServiceCommand(Server& server) : server(server) {}

	void execute() override {
		server.startService();
	}
};

class StopServiceCommand : public Command {
private:
	Server& server;
public:
	StopServiceCommand(Server& server) : server(server) {}

	void execute() override {
		server.stopService();
	}
};

class RestartServiceCommand : public Command {
private:
	Server& server;
public:
	RestartServiceCommand(Server& server) : server(server) {}

	void execute() override {
		server.restartService();
	}
};

// 调用者（客户端）
class Client {
private:
	std::vector<std::unique_ptr<Command>> commandQueue; // 命令队列
public:
	void addCommand(std::unique_ptr<Command> cmd) {
		commandQueue.push_back(std::move(cmd));
	}

	void executeCommands() {
		for (const auto& cmd : commandQueue) {
			cmd->execute();
		}
		commandQueue.clear(); // 执行完毕后清空命令队列
	}
};

// 测试代码
int main() {
	Server server;
	Client client;

	// 添加命令到队列
	client.addCommand(std::make_unique<StartServiceCommand>(server));
	client.addCommand(std::make_unique<StopServiceCommand>(server));
	client.addCommand(std::make_unique<RestartServiceCommand>(server));

	// 执行所有命令
	client.executeCommands();

	return 0;
}