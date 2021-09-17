#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char* argv[], char* envp[])
{
    pid_t pid;
    if (pid = fork() == 0) {
        if (execve(argv[0], argv, envp) < 0) {
            printf("%s: Command not found.\n", argv[0]);
        } else {
            printf("Command line arguments:\n");
            for (int i = 0; argv[i] != NULL; i++)
                printf("        argv[%2d]:%s\n", i, argv[i]);
            printf("\n");
            printf("Environment variables:\n");
            for (int i = 0; envp[i] != NULL; i++)
                printf("        envp[%2d]:%s\n", i, envp[i]);
            exit(0);
        }
    }
}