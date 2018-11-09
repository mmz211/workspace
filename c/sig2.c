int main(){
    sigset_t initset;
    int i;
    sigemptyset(&initset);//初始化信号集合为空集合
    sigaddset(&initset,SIGINT);//将SIGINT信号加入到此集合中去
    while(1){
        sigprocmask(SIG_BLOCK,&initset,NULL);//将信号集合加入到进程的阻塞集合中去
        fprintf(stdout,"SIGINT singal blocked/n");
        for(i=0;i<10;i++){

            sleep(1);//每1秒输出
            fprintf(stdout,"block %d/n",i);
        }
        //在这时按一下Ctrl+C不会终止
        sigprocmask(SIG_UNBLOCK,&initset,NULL);//从进程的阻塞集合中去删除信号集合
        fprintf(stdout,"SIGINT SINGAL unblokced/n");
        for(i=0;i<10;i++){

            sleep(1);
            fprintf(stdout,"unblock %d/n",i);
        }

    }
    exit(0);
}


