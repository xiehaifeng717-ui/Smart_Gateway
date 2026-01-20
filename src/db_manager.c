#include <stdio.h>
#include <stdlib.h>
#include "sqlite3.h"
#include "db_manager.h"

#define DB_NAME "sensor_data.db"

static sqlite3 *db = NULL;

// 初始化数据库（建表）
int db_init(void){
    int rc;
    char *err_msg = NULL;

    // 打开/创建数据库
    rc = sqlite3_open(DB_NAME, &db);
    if(rc){
        printf("[DB] Error opening DB: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    // 创建传感器数据表
    const char *sql_create = "CREATE TABLE IF NOT EXISTS records (" \
                             "id INTEGER PRIMARY KEY AUTOINCREMENT, " \
                             "timestamp INTEGER, " \
                             "temp REAL, " \
                             "humi REAL);";

    // 执行建表语句
    rc = sqlite3_exec(db, sql_create, NULL, 0, &err_msg);
    if(rc != SQLITE_OK){
        printf("[DB] SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        return -1;
    }

    printf("[DB] Database initialized successfully.\n");
    return 0;
}

// 插入传感器数据
int db_insert_data(SensorData *data){
    if(db == NULL){
        return -1; // 数据库未初始化
    }

    char sql[256];
    char *err_msg = NULL;

    // SQL 插入语句
    sprintf(sql, "INSERT INTO records (timestamp, temp, humi) VALUES (%ld, %.2f, %.2f);",
            data->timestamp, data->temperature, data->humidity);
    
    // 执行插入操作
    int rc = sqlite3_exec(db, sql, NULL, 0, &err_msg);
    if(rc != SQLITE_OK){
        printf("[DB] Insert error: %s\n", err_msg);
        sqlite3_free(err_msg);
        return -1;
    }

    // 调试语句
    // printf("[DB] Inserted one record.\n");

    return 0;
}