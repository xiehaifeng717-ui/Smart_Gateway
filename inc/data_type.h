#ifndef _DATA_TYPE_H
#define _DATA_TYPE_H

#include <pthread.h>

// 定义传感器数据结构体
typedef struct{
    int id;                     //数据ID
    float temperature;          //温度值
    float humidity;             //湿度值
    long timestamp;             //时间戳
} SensorData;

// 声明全局变量
extern SensorData g_data;       //全局传感器数据
extern pthread_mutex_t g_lock;  //全局互斥锁

#endif