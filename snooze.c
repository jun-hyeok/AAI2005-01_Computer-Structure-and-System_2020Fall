#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

void unix_error(char* msg)
{
    fprintf(stderr, "%s : %d\n", msg, errno);
    exit(0);
}

void handler(int sig)
{
    return;
}

unsigned int snooze(unsigned int secs)
{
    unsigned int rc = sleep(secs);

    printf("Slept for %d of %d secs.\n", secs - rc, secs);
    return rc;
}

int main(int argc, char** argv)
{
    if (argc != 2) {
        fprintf(stderr, "usage: %s <secs>\n", argv[0]);
        exit(0);
    }
    if (signal(SIGINT, handler) == SIG_ERR)
        unix_error("signal error\n");
    (void)snooze(atoi(argv[1]));
    exit(0);
}