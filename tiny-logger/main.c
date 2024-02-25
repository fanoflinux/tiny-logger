#include"logger.h"

int main(int argc,char *argv[])
{
    SLoggerInstance()->setLevel(WARNING);
    /*使用继承的方法可以不使用这个模块*/
    extern FILE* fp;
    fp=fopen("lingo-logger.txt","a");
    if(!fp)
    {
        LOG_WARNING("打开日志文件失败%s",strerror(errno));
    }
    LOG_DEBUG("hi lingo");

    LOG_DEBUG("[test message: %s]","debug");
    LOG_INFO("[test message: %s]","info");
    LOG_WARNING("[test message: %s]","warning");
    LOG_ERROR("[test message: %s]","error");
    return 0;
}