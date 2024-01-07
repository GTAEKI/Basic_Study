#include<stdio.h>
#include<unistd.h>

int main()
{
    printf("process id is %d", getpid());
    return 0;
}