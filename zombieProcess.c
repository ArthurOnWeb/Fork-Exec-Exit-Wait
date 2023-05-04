#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        printf("Fork failed\n");
        exit(1);
    } else if (pid == 0) {
        printf("Child process created, PID: %d, Parent PID: %d\n", getpid(), getppid());
        exit(0); // Child process terminates immediately
    } else {
        printf("Parent process, PID: %d, created child with PID: %d\n", getpid(), pid);
        sleep(10);
	printf("Parent process sleeps for 10 seconds before calling wait\n");
        wait(NULL); 
        printf("Parent process collected the termination status of child process\n");
	sleep(10);
    }

    return 0;
}
