#include <iostream>
#include <memory>
#include <string>


// 屏幕类
class Screen {
public:
	void display(const std::string& source, const std::string& resolution) {
		std::cout << "Displaying output on screen from: " << source
			<< " at resolution: " << resolution << std::endl;
	}
};

// 显卡类（外部显卡）
class GraphicsCard {
private:
	std::string resolution;
	bool isActive = false; // 默认为不工作状态

public:
	void setResolution(const std::string& res) {
		resolution = res;
		std::cout << "External GraphicsCard: Resolution set to " << resolution << std::endl;
	}

	std::string getResolution() const {
		return resolution;
	}

	void activate() {
		isActive = true;
		std::cout << "External GraphicsCard activated." << std::endl;
	}

	void deactivate() {
		isActive = false;
		std::cout << "External GraphicsCard deactivated." << std::endl;
	}

	bool isWorking() const {
		return isActive;
	}

	void processGraphics(Screen& screen);
};

// CPU 类（包括集成显卡）
class CPU {
private:
	std::string integratedResolution;

public:
	void setIntegratedGraphicsResolution(const std::string& resolution) {
		integratedResolution = resolution;
		std::cout << "Integrated Graphics: Resolution set to " << integratedResolution << std::endl;
	}

	void processGraphics(Screen& screen) {
		std::cout << "Forwarding output from Integrated Graphics to the screen at resolution " << integratedResolution << std::endl;
		screen.display("Integrated Graphics", integratedResolution);
	}

	std::string getIntegratedResolution() const {
		return integratedResolution;
	}
};


// 昔卡处理图形
void GraphicsCard::processGraphics(Screen& screen) {
	if (isActive) {
		std::cout << "Processing graphics on External GraphicsCard." << std::endl;
		screen.display("External GraphicsCard", resolution);
	}
}

// 外观类
class ComputerFacade {
private:
	std::unique_ptr<GraphicsCard> graphicsCard; // 外部显卡
	std::unique_ptr<CPU> cpu;                    // CPU
	std::unique_ptr<Screen> screen;              // 屏幕

public:
	ComputerFacade()
		: graphicsCard(std::make_unique<GraphicsCard>()),
		cpu(std::make_unique<CPU>()),
		screen(std::make_unique<Screen>()) {}

	// 调整分辨率和电源模式
	void configureSettings(const std::string& resolution, const std::string& powerMode) {
		std::cout << "Configuring computer settings..." << std::endl;

		if (powerMode == "Power Saving") {
			// 省电模式：使用集成显卡
			cpu->setIntegratedGraphicsResolution(resolution);
			graphicsCard->deactivate();  // 关闭独立显卡
			cpu->processGraphics(*screen);
		}
		else if (powerMode == "Balanced") {
			// 均衡模式：使用外部显卡处理图形，然后直接显示
			graphicsCard->setResolution(resolution);
			graphicsCard->activate(); // 启动独立显卡
			graphicsCard->processGraphics(*screen); // 独立显卡处理图形并显示
		}
		else if (powerMode == "Performance") {
			// 性能模式：全交给外部独立显卡来处理与显示
			graphicsCard->setResolution(resolution);
			graphicsCard->activate(); // 启动独立显卡
			graphicsCard->processGraphics(*screen); // 独立显卡处理图形并显示
		}

		std::cout << "Power mode set to: " << powerMode << std::endl;
	}
};

int main() {
	std::unique_ptr<ComputerFacade> computer = std::make_unique<ComputerFacade>();

	// 调整为省电模式，使用集成显卡输出
	computer->configureSettings("1920x1080", "Power Saving");

	// 调整为均衡模式，通过独立显卡处理图形，直接显示
	computer->configureSettings("2560x1440", "Balanced");

	// 调整为性能模式，全部交给外部显卡处理与显示
	computer->configureSettings("3840x2160", "Performance");

	return 0;
}