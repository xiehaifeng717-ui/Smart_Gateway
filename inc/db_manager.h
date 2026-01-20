#ifndef _DB_MANAGER_H
#define _DB_MANAGER_H

#include "data_type.h"

// 初始化数据库（建表）
int db_init(void);

// 插入传感器数据
int db_insert_data(SensorData *data);

#endif