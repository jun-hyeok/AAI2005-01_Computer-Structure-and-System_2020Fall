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

int main1()
{
    int a = 9;
    if (Fork() == 0)
        printf("In chlid process, p1:a=%d\n", a--);
    printf("p2:a=%d\n", a++);
    exit(0);
}

int main2()
{
    int a = 9;
    if (Fork() == 0) {
        printf("In chlid process, PID=%d, p1:a=%d\n", getpid(), a--);
        printf("Terminating Child, PID=%d\n", getpid());
        exit(0);
    } else {
        printf("Running Parent, PID=%d\n", getpid());
        printf("p2:a=%d\n", a++);
        exit(0);
    }
}

int main3()
{
    int a = 9;
    if (Fork() == 0) {
        printf("In chlid process, PID=%d, p1:a=%d\n", getpid(), a--);
        printf("Terminating Child, PID=%d\n", getpid());
        printf("My Parent PID is, PPID=%d\n", getppid());
        exit(0);
    } else {
        printf("Running Parent, PID=%d\n", getpid());
        printf("p2:a=%d\n", a++);
        exit(0);
    }
}

int main4()
{ //Zombie
    int a = 9;
    if (Fork() == 0) {
        printf("In chlid process, PID=%d, p1:a=%d\n", getpid(), a--);
        printf("Terminating Child, PID=%d\n", getpid());
        printf("My Parent PID is, PPID=%d\n", getppid());
        exit(0);
    } else {
        printf("Running Parent, PID=%d\n", getpid());
        printf("p2:a=%d\n", a++);
        while (1)
            ;
    }
}

void fork8()
{ //Nonterminating Child
    if (fork() == 0) {
        printf("Running Parent, PID=%d\n", getpid());
        while (1)
            ;
    } else {
        printf("Terminating Parent, PID=%d\n", getpid());
        exit(0);
    }
}

void fork9()
{
    int child_status;
    if (fork() == 0) {
        printf("HC: hello from child\n");
        exit(0);
    } else {
        printf("HP: hello from parent\n");
        wait(&child_status);
        printf("CT: child has terminated\n");
    }
    printf("Bye\n");
}

void fork10()
{ //wait
    pid_t pid[3];
    int i, child_status;
    for (i = 0; i < 3; i++)
        if (pid[i] = fork() == 0) {
            exit(100 + i);
        }
    for (i = 0; i < 3; i++) {
        pid_t wpid = wait(&child_status);
        if (WIFEXITED(child_status))
            printf("Child %d terminated with exit status %d\n", wpid, WEXITSTATUS(child_status));
        else
            printf("Child %d terminate abnormally\n", wpid);
    }
}
void fork11()
{ //waitpid
    pid_t pid[3];
    int child_status;
    for (int i = 0; i < 3; i++) {
        if (pid[i] = fork() == 0)
            exit(100 + i);
    }
    for (int i = 2; i >= 0; i--) {
        pid_t wpid = waitpid(pid[i], &child_status, 0);
        if (WIFEXITED(child_status)) {
            printf("Child %d terminated with exit status %d\n", wpid, WEXITSTATUS(child_status));
        } else {
            printf("Child %d terminate abnormally\n", wpid);
        }
    }
}