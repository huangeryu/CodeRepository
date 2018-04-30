#include<fcntl.h>
#include "lst_timer.hpp"
#define FD_LIMIT 65535
#define MAX_EVENT_NUMBER 1024
#define TIMESLOT 5
static int pipefd[2];
static sort_timer_lst timer_lst;
static int epollfd=0;
int setnonblocking(int fd)
{
    int old_option=fcntl(fd,F_GETFL);
}

