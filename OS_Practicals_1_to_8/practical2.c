#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;

int main(void)
{
    int n, a[50], i, j, temp;
    pid_t pid;

    printf("Enter number of integers (1-50): ");
    if (scanf("%d", &n) != 1 || n < 1 || n > 50) {
        printf("Invalid count.\n");
        return 1;
    }

    printf("Enter %d integers: ", n);
    for (i = 0; i < n; i++)
        scanf("%d", &a[i]);

    pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        char count[20];
        char *args[52];

        snprintf(count, sizeof(count), "%d", n);
        args[0] = "./descending";
        args[1] = count;

        /* Pass the entered integers as command-line arguments. */
        for (i = 0; i < n; i++) {
            static char values[50][20];
            snprintf(values[i], sizeof(values[i]), "%d", a[i]);
            args[i + 2] = values[i];
        }
        args[n + 2] = NULL;

        execve("./descending", args, environ);
        perror("execve");
        _exit(1);
    }

    /* Parent sorts in ascending order. */
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (a[j] > a[j + 1]) {
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }

    printf("\nParent process (PID %d)\nAscending order: ", getpid());
    for (i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");

    wait(NULL);
    printf("Parent: child process completed.\n");
    return 0;
}
