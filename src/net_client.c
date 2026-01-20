#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include "net_client.h"

// 全局变量：网络客户端套接字
static int sockfd = -1;

// 初始化网络连接
int net_client_init(const char *server_ip, int server_port){
    // 创建套接字
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0){
        perror("[Net] Socket creation failedn");
        return -1;
    }

    // 设置服务器地址结构体
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    // 端口号转换为网络字节序
    server_addr.sin_port = htons(server_port);

    // 将 IP 地址从文本转换为二进制
    if(inet_pton(AF_INET, server_ip, &server_addr.sin_addr) <= 0){
        printf("[Net] Invalid address/ Address not supported. \n");
        close(sockfd);
        return -1;
    }

    // 连接到服务器
    printf("[Net] Connecting to %s:%d...\n", server_ip, server_port);
    if(connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0){
        perror("[Net] Connection Failed \n");
        close(sockfd);
        sockfd = -1;
        return -1;
    }
    printf("[Net] Connected to server successfully.\n");

    return 0;
}

// 发送传感器数据到服务器
int net_client_send_data(SensorData *data){
    // 未连接
    if(sockfd < 0){
        return -1;
    }

    // 发送数据
    char buffer[128];
    // 将数据打包为二进制格式 (4 bytes id, 4 bytes temp, 4 bytes humi)
    // 格式：#ID,Temp,Humi,Timestamp
    sprintf(buffer, "#%d,%.2f,%.2f,%ld", data->id, data->temperature, data->humidity, data->timestamp);

    // 发送数据到服务器
    int sent_bytes = send(sockfd, buffer, strlen(buffer), 0);
    if(sent_bytes < 0){
        perror("[Net] Send failed \n");
        close(sockfd);
        sockfd = -1;
        return -1;
    }

    return 0;
}