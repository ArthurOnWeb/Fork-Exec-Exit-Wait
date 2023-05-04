#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();
    int status;

    if (pid < 0) {
        printf("Fork failed\n");
        exit(1);
    } else if (pid == 0) {
        printf("Child process created, PID: %d, Parent PID: %d\n", getpid(), getppid());
        int value;
        printf("Enter a value: ");
        scanf("%d", &value);
        exit(value); // Child process returns the value by calling exit with it
    } else {
        printf("Parent process, PID: %d, waiting for child process with PID: %d\n", getpid(), pid);
        wait(&status); // Parent process waits for the child process to complete
        int returned_value = WEXITSTATUS(status); // Get the returned value from the child process
        printf("Parent process collected the termination status of child process\n");
        printf("Returned value: %d\n", returned_value);
    }

    return 0;
}
