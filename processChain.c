#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void create_process_chain(int n) {
    if (n <= 0) {
        return;
    }

    pid_t pid = fork();

    if (pid < 0) {
        printf("Fork failed\n");
        exit(1);
    } else if (pid == 0) {
        printf("Process level %d created, PID: %d, Parent PID: %d\n", n, getpid(), getppid());
        sleep(n); // Sleep for n seconds before creating the next child process
        create_process_chain(n - 1);
    } else {
        wait(NULL);
    }

    sleep(10); // Keep all processes alive for 10 seconds before terminating
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <n>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);

    if (n < 1) {
        printf("n should be a positive integer\n");
        return 1;
    }

    printf("Creating a process chain of length %d\n", n);
    create_process_chain(n);

    return 0;
}
