#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int n, a[50], i, j, temp;

    if (argc < 2) {
        fprintf(stderr, "Missing input values.\n");
        return 1;
    }

    n = atoi(argv[1]);
    if (n < 1 || n > 50 || argc != n + 2) {
        fprintf(stderr, "Invalid input values.\n");
        return 1;
    }

    for (i = 0; i < n; i++)
        a[i] = atoi(argv[i + 2]);

    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (a[j] < a[j + 1]) {
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }

    printf("Child process (PID %d)\nDescending order: ", getpid());
    for (i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");

    return 0;
}
