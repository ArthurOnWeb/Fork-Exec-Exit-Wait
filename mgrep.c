#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s pattern file-list\n", argv[0]);
        exit(1);
    }

    const char *pattern = argv[1];

    printf("Pattern: %s\n", pattern);
    printf("Files:\n");

    for (int i = 2; i < argc; i++) {
        printf("%s\n", argv[i]);

        pid_t pid = fork();

        if (pid < 0) {
            perror("Fork failed");
            exit(1);
        } else if (pid == 0) {
            execlp("grep", "grep", pattern, argv[i], NULL);
            perror("execlp failed");
            exit(1);
        }
    }

    for (int i = 2; i < argc; i++) {
        wait(NULL);
    }

    return 0;
}
