//#include <unistd.h>
#include <stdio.h>

int main(void)
{
    int counter;
//    alarm(3);
    for(counter=0; counter<5; counter++)
        printf("counter=%d ", counter);
    return 0;
}
