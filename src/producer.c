#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "producer.h"
#include "data_type.h"

// 生产者线程函数
void *producer_thread(void *arg){
    printf("[Producer] thread created.\n");

    while(1){
        // 模拟温湿度数据
        float temp = 20.0 + (rand() % 100) / 10.0; // 20.0 to 30.0
        float humi = 30.0 + (rand() % 100) / 10.0; // 30.0 to 40.0

        // 加锁，写入全局数据
        pthread_mutex_lock(&g_lock);
        g_data.id++;
        g_data.temperature = temp;
        g_data.humidity = humi;
        g_data.timestamp = time(NULL);
        pthread_mutex_unlock(&g_lock);

        // 打印温湿度数据
        // printf("[Producer] Temperature: %.2f C, Humidity: %.2f %%\n", temp, humi);

        // 休眠1秒
        sleep(1);
    }

    return NULL;
}