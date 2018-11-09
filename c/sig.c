#include
#include
#include
#include
#include
#include

int value=0;
sem_t sem_lock;//定义信号量

void myhandler(int signo,siginfo_t *si,void *vcontext);//进程处理函数声明

int main(){
    union sigval val;
    val.sival_int=1;
    struct sigaction oldact,newact;
    int res;
    res=sem_init(&sem_lock,0,1);
    if(res!=0){
        perror("信号量初始化失败");
    }

    newact.sa_sigaction=myhandler;
    newact.sa_flags=SA_SIGINFO;
    sigaction(SIGUSR1,&newact,&oldact);
    sem_wait(&sem_lock);
    printf("xxxx/n");
    value=1;
    sleep(10);
    sigqueue(getpid(),SIGUSR1,val);//sigqueue发送带参数的信号
    sem_post(&sem_lock);
    sleep(10);
    exit(0);
}

void myhandler(int signo,siginfo_t *si,void *vcontext){

    sem_wait(&sem_lock);
    value=0;
    sem_post(&sem_lock);

}
