# Smart Gateway (基于 Linux 的工业智能网关)

## 📖 项目简介
本项目是一个运行在嵌入式 Linux 环境下的工业级智能网关原型。它采用**生产者-消费者**多线程架构，模拟了从传感器数据采集、本地 SQLite 持久化存储，到 TCP 网络实时上报的全流程业务。

## 🛠️ 技术栈
- **开发语言**: C / Makefile
- **操作系统**: Linux (Ubuntu / Embedded Linux)
- **核心技术**:
    - POSIX 多线程 (pthread)
    - 线程同步 (Mutex 互斥锁)
    - 网络编程 (TCP Socket)
    - 数据库开发 (SQLite3)

## 📂 目录结构
```text
├── inc/          # 头文件
├── src/          # 源文件 (main, producer, consumer, db, net)
├── Makefile      # 自动化编译脚本
└── README.md     # 项目说明文档