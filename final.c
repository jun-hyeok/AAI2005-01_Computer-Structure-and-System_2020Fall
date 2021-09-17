// 2018311199 박준혁
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

void unix_error(char* msg)
{
    fprintf(stderr, "%s: %d\n", msg, errno);
    exit(0);
}

pid_t Fork(void)
{
    pid_t pid;
    if (pid = fork() < 0) {
        unix_error("Fork error");
        exit(0);
    }
    return pid;
}

int main()
{
    int a = 9;
    if (Fork() == 0) {
        printf("In chlid process, PID=%d, p1:a=%d\n", getpid(), a--);
        printf("Terminating Child, PID=%d\n", getpid());
        printf("My Parent PID is, PPID=%d\n", getppid());
    }
    printf("Running Parent, PID=%d\n", getpid());
    printf("p2:a=%d\n", a++);
    exit(0);
}