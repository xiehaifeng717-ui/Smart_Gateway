# Linux Smart Gateway Demo (学习项目)

## 📖 项目介绍
这是一个基于 Linux C 的多线程网关练习项目。
通过这个项目，我从零开始学习并实践了 Linux 环境下的系统编程。它模拟了一个简易的物联网网关，能够在一个线程中生成数据，在另一个线程中处理数据，并同时保存到数据库和发送到网络。

## 🎯 学习成果
这个项目帮助我掌握了以下核心知识点：
- **多线程编程**: 理解了 `pthread` 的创建与回收，以及生产者-消费者模型。
- **线程同步**: 实践了 `Mutex` 互斥锁，解决了数据竞争问题。
- **数据持久化**: 学会了将 SQLite3 数据库移植到 C 项目中。
- **网络通信**: 掌握了 Linux 下的 Socket TCP 客户端编程。
- **工程管理**: 学会了编写 Makefile 来管理多文件编译。

## 📂 代码结构
- `src/`: 源代码 (main, producer, consumer, db_manager, net_client)
- `inc/`: 头文件
- `Makefile`: 编译脚本

## 🚀 如何运行
1. **编译**: 
   ```bash
   make
2. **运行**
   ```bash
   ./build/smart_gateway
3. **清理**
   ```bash
   make clean