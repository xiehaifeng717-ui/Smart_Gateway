#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "data_type.h"
#include "producer.h"
#include "consumer.h"
#include "db_manager.h"
#include "net_client.h"

//全局变量
SensorData g_data;      //全局传感器数据
pthread_mutex_t g_lock; //全局互斥锁

int main(void){
    printf("-----------------------------\n");
    printf("Linux Smart Gateway Started...    \n");
    printf("-----------------------------\n");

    //初始化互斥锁
    pthread_mutex_init(&g_lock, NULL);

    //定义线程 ID 变量
    pthread_t prod_tid; //生产者线程
    pthread_t cons_tid; //消费者线程

    //初始化数据库
    if(db_init() != 0){
        printf("Failed to init database\n");
        return -1;
    }

    //初始化网络客户端
    if(net_client_init("192.168.1.4", 8080) != 0){
        printf("Warning: Failed to init network client\n");
    }

    //创建生产者线程和消费者线程
    //参数列表：线程 ID 指针，线程属性(NULL为默认)，线程函数，传递给线程函数的参数(NULL代表无参数)
    pthread_create(&prod_tid, NULL, producer_thread, NULL);
    pthread_create(&cons_tid, NULL, consumer_thread, NULL);

    //等待线程结束
    pthread_join(prod_tid, NULL); 
    pthread_join(cons_tid, NULL);

    //销毁互斥锁
    pthread_mutex_destroy(&g_lock);

    printf("Gateway Stopped.\n");
    return 0;
}