/*
 * SPDX文件版权文本：2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */
#pragma once

/* 常用LCD面板命令*/
#define LCD_CMD_NOP          0x00 // 此命令为空命令
#define LCD_CMD_SWRESET      0x01 // 软件复位寄存器（内置帧缓冲区不受影响）
#define LCD_CMD_RDDID        0x04 // 读取24位显示ID
#define LCD_CMD_RDDST        0x09 // 读取显示状态
#define LCD_CMD_RDDPM        0x0A // 读取显示电源模式
#define LCD_CMD_RDD_MADCTL   0x0B // 读取显示MADCTL
#define LCD_CMD_RDD_COLMOD   0x0C // 读取显示像素格式
#define LCD_CMD_RDDIM        0x0D // 读取显示图像模式
#define LCD_CMD_RDDSM        0x0E // 读取显示信号模式
#define LCD_CMD_RDDSR        0x0F // 读取显示自诊断结果
#define LCD_CMD_SLPIN        0x10 // 进入睡眠模式（DC/DC，振荡器，扫描停止，但内存保留内容）
#define LCD_CMD_SLPOUT       0x11 // 退出睡眠模式
#define LCD_CMD_PTLON        0x12 // 打开部分显示模式
#define LCD_CMD_NORON        0x13 // 打开正常显示模式
#define LCD_CMD_INVOFF       0x20 // 从显示反转模式恢复
#define LCD_CMD_INVON        0x21 // 进入显示反转模式
#define LCD_CMD_GAMSET       0x26 // 选择当前显示的Gamma曲线
#define LCD_CMD_DISPOFF      0x28 // 显示关闭（禁用帧缓冲输出）
#define LCD_CMD_DISPON       0x29 // 显示打开（启用帧缓冲输出）
#define LCD_CMD_CASET        0x2A // 设置列地址
#define LCD_CMD_RASET        0x2B // 设置行地址
#define LCD_CMD_RAMWR        0x2C // 写入帧存储器
#define LCD_CMD_RAMRD        0x2E // 读取帧内存
#define LCD_CMD_PTLAR        0x30 // 定义局部区域
#define LCD_CMD_VSCRDEF      0x33 // 垂直滚动定义
#define LCD_CMD_TEOFF        0x34 // 撕裂效应的匝数
#define LCD_CMD_TEON         0x35 // 打开撕裂效果

#define LCD_CMD_MADCTL       0x36     // 内存数据访问控制
#define LCD_CMD_MH_BIT       (1 << 2) // 显示数据锁存顺序，0：从左到右刷新，1：从右到左刷新
#define LCD_CMD_BGR_BIT      (1 << 3) // RGB/BGR顺序，0:RGB，1:BGR
#define LCD_CMD_ML_BIT       (1 << 4) // 行地址顺序，0：从上到下刷新，1：从下到上刷新
#define LCD_CMD_MV_BIT       (1 << 5) // 行/列顺序，0：正常模式，1：反向模式
#define LCD_CMD_MX_BIT       (1 << 6) // 列地址顺序，0：从左到右，1：从右到左
#define LCD_CMD_MY_BIT       (1 << 7) // 行地址顺序，0：从上到下，1：从下到上

#define LCD_CMD_VSCSAD       0x37 // 垂直滚动起始地址
#define LCD_CMD_IDMOFF       0x38 // 从IDLE模式恢复
#define LCD_CMD_IDMON        0x39 // 进入空闲模式（显示8色深度）
#define LCD_CMD_COLMOD       0x3A // 定义RGB图片数据的格式
#define LCD_CMD_RAMWRC       0x3C // 内存写入继续
#define LCD_CMD_RAMRDC       0x3E // 内存读取继续
#define LCD_CMD_STE          0x44 // 设置撕裂扫描线，当显示模块到达N线时，撕裂效果输出信号
#define LCD_CMD_GDCAN        0x45 // 获取扫描线
#define LCD_CMD_WRDISBV      0x51 // 写入显示亮度
#define LCD_CMD_RDDISBV      0x52 // 读取显示亮度值

