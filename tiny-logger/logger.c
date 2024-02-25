#include"logger.h"
#include<malloc.h>
//函数声明
void lingo_logger(loglevel level,const char *filename,int linenumber,const char* fmt,...);
void setLevel(loglevel level);
loglevel level();

//由于是使用继承的方法因此可以把文件指针去掉
FILE * fp=NULL;

const char *getloglevel(loglevel level)
{
    switch (level)
    {
        #define XX(x)\
        case x:\
        return #x
        
        XX(DEBUG);
        XX(INFO);
        XX(WARNING);
        XX(ERROR);
        #undef XX
    }
    return "UNKNOWN";
}

//时间输出
const char* getTimeString()
{
    time_t time1 = time(NULL);//获取系统时间
    struct tm* tm1 = localtime(&time1);
    static char str[128];
    strftime(str,128,"%Y-%m-%d %H:%M:%S",tm1);
    return str;
}

/*
//继承后输出到控制台的方法
void SConsoleAppender_log(SConsoleAppender* appender,loglevel level,const char* msg);//声明
SConsoleAppender* SConsoleAppender_new()
{
    SConsoleAppender* a =calloc(1,sizeof(SConsoleAppender));
    if(!a)
    {
        return NULL;
    }
    //a->log=SConsoleAppender_log;
    a->log = (void (*)(SAppender*, loglevel, const char*))SConsoleAppender_log;
    return a;
}
void SConsoleAppender_log(SConsoleAppender* appender,loglevel level,const char* msg)//实现
{
    printf("%s",msg);
}

//继承后输出到文件的方法
void SFileAppender_log(SFileAppender* appender,loglevel level,const char* msg);//声明
SFileAppender* SFileAppender_new(const char* fileName)
{
    //创建对象
    SFileAppender* a =calloc(1,sizeof(SFileAppender));
    if(!a)
    {
        return NULL;
    }
    //a->log=SFileAppender_log;
    a->log = (void (*)(SFileAppender*, loglevel, const char*))SFileAppender_log;
    strcpy(a->fileName,fileName);
    a->fp=fopen(a->fileName,"a");
    if(!a->fp)
    {
        printf("SFileAppender file open failed%s",strerror(errno));
        free(a);
        return NULL;
    }
    return a;
}
void SFileAppender_log(SFileAppender* appender,loglevel level,const char* msg)//实现
{
    fprintf(appender->fp,"%s",msg);
}
*/

//单例模式
SLogger* pthis =NULL;
SLogger* SLoggerInstance()
{
    if(!pthis)
    {
        static SLogger logger;
        pthis = &logger;
        logger.log=lingo_logger;
        logger.setLevel=setLevel;
        logger.level=level;
    }
    return pthis;
}
//日志输出
void lingo_logger(loglevel level,const char *filename,int linenumber,const char* fmt,...)
{
    //当前日志小于指定值时直接退出
    if(level<pthis->_level)
    {
        return;
    }


    va_list list;
    va_start(list,fmt);
    char buf[1024];
    vsnprintf(buf,1024,fmt,list);
    va_end(list);
    char msg[2048];
    sprintf(msg,"[%s],%s,%d,%s,%s",getloglevel(level),filename,linenumber,getTimeString(),buf);//向对应区域写入信息
    
    printf("%s\n",msg);//向控制台打印信息
    if(fp)
    {
        fprintf(fp,"%s\n",msg);
    }
}
//设置日志级别
void setLevel(loglevel level)
{
    pthis->_level=level;
}
//获取日志级别
loglevel level()
{
    return pthis->_level;
}
