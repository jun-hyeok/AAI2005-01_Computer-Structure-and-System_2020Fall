#include <errno.h>
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
    pid_t pid[3];
    int child_status;
    for (int i = 0; i < 3; i++) {
        if (pid[i] = Fork() == 0) {
            printf("In chlid process, PID=%d\n", getpid());
            printf("Terminating Child, PID=%d\n", getpid());
            printf("My Parent PID is, PPID=%d\n", getppid());
            exit(100 + i);
        }
    }
    for (int i = 0; i < 3; i++) {
        pid_t wpid = wait(&child_status);
        if (WIFEXITED(child_status))
            printf("Child %d terminated with exit status %d\n", wpid, WEXITSTATUS(child_status));
        else
            printf("Child %d terminate abnormally\n", wpid);
    }
}