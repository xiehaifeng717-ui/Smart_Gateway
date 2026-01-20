#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "consumer.h"
#include "data_type.h"
#include "db_manager.h"
#include "net_client.h"

// 消费者线程函数
void *consumer_thread(void *arg){
    printf("[Consumer] thread created.\n");

    while(1){
        // 读取并打印全局数据
        pthread_mutex_lock(&g_lock);
        int last_id = g_data.id;
        float last_temp = g_data.temperature;
        float last_humi = g_data.humidity;
        long last_timestamp = g_data.timestamp;
        pthread_mutex_unlock(&g_lock);
        // 打印读取到的数据
        printf(">>[Consumer] Read Data ID: %4d, Temperature: %.2f C, Humidity: %.2f %%\n", last_id, last_temp, last_humi);

        // 将数据写入数据库
        SensorData data_to_insert;
        data_to_insert.id = last_id;
        data_to_insert.temperature = last_temp;
        data_to_insert.humidity = last_humi;
        data_to_insert.timestamp = last_timestamp;
        // 插入数据到数据库
        db_insert_data(&data_to_insert);

        // 发送数据到服务器
        SensorData data_to_send;
        data_to_send.id = last_id;
        data_to_send.temperature = last_temp;
        data_to_send.humidity = last_humi;
        data_to_send.timestamp = last_timestamp;
        net_client_send_data(&data_to_send);

        // 休眠 1 秒
        sleep(1);
    }

    return NULL;
}