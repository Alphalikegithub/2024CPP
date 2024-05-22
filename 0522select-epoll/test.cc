#include <sys/select.h>
struct timeval
{
    time_t      tv_sec;
    suseconds_t tv_usec;
};

int select(int nfds,fd_set *readfds,fd_set *writefds,fd_set *exceptfds,struct timeval *timeout);
int main(){

    
    return 0;
}