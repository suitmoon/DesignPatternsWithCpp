# 指定 C++ 编译器
CXX = g++

# 源文件列表
SRC = CompositePattern.cpp

# 可执行文件的名称
TARGETS = $(SRC:.cpp=)

# 设置编译选项
CXXFLAGS = -Wall -Wextra -std=c++17 -pthread

# 默认目标
all: $(TARGETS)

# 独立规则：为每个源文件生成对应的可执行文件
%: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

# 清理生成的文件
clean:
	rm -f $(TARGETS)

# 声明伪目标
.PHONY: all clean
