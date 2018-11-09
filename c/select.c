#include <fcntl.h>  
#include <stdio.h>  
#include <stdlib.h>  
#include <unistd.h>  
#include <string.h>  
#include <time.h>  
#include <errno.h>  
#include <sys/types.h>
#include <sys/stat.h>

#define FIFO1 "in1"  
#define FIFO2 "in2"  
#define MAX_BUFFER_SIZE 1024  //缓冲区大小  
#define IN_FILES 3               //多路复用输入文件数目  
#define TIME_DELAY 60           //超时秒数  

#define MAX(a,b) ((a > b) ? (a) : (b))  

int main(void)  
{  
    int fds[IN_FILES];      //管道描述符  
    int i;  
    int res;  
    int real_read;  
    int maxfd;  

    char buf[MAX_BUFFER_SIZE];  

    struct timeval tv;  

    fd_set inset;  
    fd_set tmp_inset;           //文件描述符集  

    fds[0] = 0;          //终端的文件描述符  

    if(access(FIFO1,F_OK) == -1)         //创建两个有名管道  
    {  
        if((mkfifo(FIFO1,0666) < 0) && (errno != EEXIST))  
        {  
            printf("Cannot creat fifo1 file!\n");  

            exit(1);  
        }  
    }  

    if(access(FIFO2,F_OK) == -1)  
    {  
        if((mkfifo(FIFO2,0666) < 0) && (errno != EEXIST))  
        {  
            printf("Cannot creat fifo2 file\n");  

            exit(1);  
        }  
    }  

    if((fds[1] = open(FIFO1,O_RDONLY | O_NONBLOCK)) < 0)   //以只读非阻塞的方式打开两个管道文件  
    {  
        printf("open in1 error!\n");  

        return 1;  
    }  

    if((fds[2] = open(FIFO2,O_RDONLY | O_NONBLOCK)) < 0)  
    {  
        printf("open in2 error!\n");  

        return 1;  
    }  

    maxfd = MAX(MAX(fds[0],fds[1]),fds[2]);  //取出两个文件描述符中的较大者  

    //初始化读集inset,并在读文件描述符集中加入相应的描述集  
    FD_ZERO(&inset);     //将insert清零，使集合中不含任何fd  
    for(i = 0; i < IN_FILES; i++)  
    {  //将fds[i]加入inset集合  
        FD_SET(fds[i],&inset);  
    }  

    FD_SET(0,&inset);  

    tv.tv_sec = TIME_DELAY;   //设置超时60s  
    tv.tv_usec = 0;  
    //循环测试该文件描述符是否准备就绪，并调用selelct()函数对相关文件描述符做相应的操作  
    while(FD_ISSET(fds[0],&inset) || FD_ISSET(fds[1],&inset) || FD_ISSET(fds[2],&inset))  
    {    //文件描述符集的备份，以免每次都进行初始化  
        tmp_inset = inset;  
        res = select(maxfd+1,&tmp_inset,NULL,NULL,&tv);  

        switch(res)  
        {  
            case -1:  
                {  
                    printf("Select error!\n");  

                    return 1;  
                }  
                break;  

            case 0:  
                {  
                    printf("Time out!\n");  

                    return 1;  
                }  
                break;  
            default:  
                {  
                    for(i = 0; i < IN_FILES; i++)  
                    {  
                        if(FD_ISSET(fds[i],&tmp_inset))  
                        {  
                            memset(buf,0,MAX_BUFFER_SIZE);  

                            real_read = read(fds[i],buf,MAX_BUFFER_SIZE);  

                            if(real_read < 0)  
                            {  
                                if(errno != EAGAIN)  
                                {  
                                    return 1;  
                                }  
                            }  
                            else if(!real_read)  //已到达文件尾  
                            {  
                                close(fds[i]);  

                                FD_CLR(fds[i],&inset);  
                            }  
                            else  
                            {  
                                if(i == 0)  
                                {   //主程序终端控制  
                                    if((buf[0] == 'q') || (buf[0] == 'Q'))  
                                    {  
                                        return 1;  
                                    }  
                                }  
                                else  
                                {   //显示管道输入字符串  
                                    buf[real_read] = '\0';  

                                    printf("%s",buf);  
                                }  
                            }  
                        }  
                    }  
                }  
                break;  
        }  
    }  

    return 0;  
}
