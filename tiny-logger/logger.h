#pragma once

#include<stdio.h>
#include<stdarg.h>
#include<time.h>
#include<string.h>
#include<errno.h>

//使用宏简化输出语句
#define LOG_DEBUG(fmt,...) SLoggerInstance()->log(DEBUG,__FILE__,__LINE__,fmt,##__VA_ARGS__);
#define LOG_INFO(fmt,...) SLoggerInstance()->log(INFO,__FILE__,__LINE__,fmt,##__VA_ARGS__);
#define LOG_WARNING(fmt,...) SLoggerInstance()->log(WARNING,__FILE__,__LINE__,fmt,##__VA_ARGS__);
#define LOG_ERROR(fmt,...) SLoggerInstance()->log(ERROR,__FILE__,__LINE__,fmt,##__VA_ARGS__);

//日志级别
typedef enum LogLevel
{
    DEBUG,INFO,WARNING,ERROR
}loglevel;


//日志输出地址(控制台、文件、数据库、网络等)
//使用一个类对日志进行继承操作
/*日志输出位置*/
/*使用一个基类，使用C语言实现多态的方法*/
/*
typedef struct SAppender SAppender;
#define SAppender_Member \
void (*log)(SAppender* appender,loglevel level,const char* msg)

//输出的基类
typedef struct SAppender
{
    //由自己去定义输出
    SAppender_Member;
}SAppender;

//输出到控制台的方法
typedef struct SConsoleAppender
{
    SAppender_Member;
}SConsoleAppender;
SConsoleAppender* SConsoleAppender_new();

//输出到文件的方法
typedef struct SFileAppender
{
    SAppender_Member;
    char fileName[128];
    FILE* fp;
}SFileAppender;
SFileAppender* SFileAppender_new(const char* fileName);
*/

typedef struct SLogger
{
    loglevel _level;//日志输出级别
    void (*log)(loglevel level,const char *filename,int linenumber,const char* fmt,...);
    void (*setLevel)(loglevel level);//设置日志级别
    loglevel (*level)();//获取日志级别
}SLogger;
//设计一个单例方便处理
SLogger* SLoggerInstance();


