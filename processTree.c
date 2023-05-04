#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void create_process_tree(int n) {
    if (n <= 0) {
        return;
    }

    for (int i = 0; i < 2; i++) {
        pid_t pid = fork();

        if (pid < 0) {
            printf("Fork failed\n");
            exit(1);
        } else if (pid == 0) {
            printf("Child process created at depth %d, PID: %d, Parent PID: %d\n", n, getpid(), getppid());
            create_process_tree(n - 1);
            sleep(10); // Keep the process alive for 10 seconds before terminating
            exit(0);
        } else {
            wait(NULL);
        }
    }
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

    printf("Creating a binary process tree of depth %d\n", n);
    create_process_tree(n);

    return 0;
}
