#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<assert.h>
#include<stdio.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include<fcntl.h>
#define BUFFER_SIZE 4096
/*主状态机的状态*/
enum CHECK_STATE
{
    CHECK_STATE_REQUESTLINE=0,/*处理状态行中*/
    CHECK_STATE_HEADER      /*处理请求头部*/
};
/*请求行的状态*/
enum LINE_STATUS
{
    LINE_OK=0,  /*请求行ok*/
    LINE_BAD,   /*请求行异常*/
    LINE_OPEN   /*等待数据,数据不完整*/
};
enum HTTP_CODE
{
    NO_REQUEST,         /*请求不完整,需要继续读取数据*/
    GET_REQUEST,        /*获的完整的客户端请求*/
    BAD_REQUEST,        /*客户端请求有误*/
    FORBIDDEN_REQUEST,  /*客户端没有足够的权限*/
    INTERNAL_ERROR,     /*服务器内部错误*/
    CLOSED_CONNECTION   /*连接已关闭*/
};
static const char* szret[]={"I get a correct result\n","something wrong\n"};


