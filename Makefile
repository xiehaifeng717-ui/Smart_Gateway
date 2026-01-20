# 编译器
CC = gcc

# 编译选项：-I 指定头文件路径, -Wall 显示警告, -pthread 开启线程支持
CFLAGS = -I./inc -Wall -pthread -ldl

# 目标文件存放路径
BUILD_DIR = build

# 目标可执行文件名
TARGET = $(BUILD_DIR)/smart_gateway

# 源文件列表 
SRCS = $(wildcard src/*.c)

# 生成对应的 .o 文件名
OBJS = $(SRCS:%.c=$(BUILD_DIR)/%.o)

# 默认目标
all: $(TARGET)

# 链接规则：把 .o 链接成可执行文件
$(TARGET): $(OBJS)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(OBJS) -o $@ $(CFLAGS)
	@echo "Build Success! Run with: ./$(TARGET)"

# 编译规则：把 .c 编译成 .o
$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# 清理规则
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean