#ifndef _NET_CLIENT_H
#define _NET_CLIENT_H

#include "data_type.h"

// 初始化网络连接
int net_client_init(const char *server_ip, int server_port);
// 发送传感器数据到服务器
int net_client_send_data(SensorData *data);

#endif