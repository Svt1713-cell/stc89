/*
*******************************************************************************
*                     《手把手教你学51单片机(C语言版)》
*                    配套 KST-51 单片机开发板 示例源代码
*
*         (c) 版权所有 2014 金沙滩工作室/清华大学出版社 保留所有权利
*                 获取更多资料请访问：http://www.kingst.org
*
* 文件名：config.h
* 描  述：第19章 多功能电子钟 工程配置头文件
* 版本号：v1.0.0
* 备  注：
*******************************************************************************
*/

#ifndef _CONFIG_H
#define _CONFIG_H

/* 通用头文件 */
#include <reg52.h>
#include <intrins.h>

/* 数据类型定义 */
typedef  signed    char    int8;    // 8位有符号整型数
typedef  signed    int     int16;   //16位有符号整型数
typedef  signed    long    int32;   //32位有符号整型数
typedef  unsigned  char    uint8;   // 8位无符号整型数
typedef  unsigned  int     uint16;  //16位无符号整型数
typedef  unsigned  long    uint32;  //32位无符号整型数

/* 全局运行参数定义 */
#define SYS_MCLK   (11059200/12)  //系统主时钟频率，即振荡器频率÷12



#endif
