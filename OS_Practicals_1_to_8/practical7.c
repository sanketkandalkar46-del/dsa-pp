#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(void)
{
    int fd1[2], fd2[2], n, file;
    char path[256], buffer[1024];
    pid_t pid;

    if (pipe(fd1) == -1 || pipe(fd2) == -1) {
        perror("pipe");
        return 1;
    }

    pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        close(fd1[1]);
        close(fd2[0]);

        n = (int)read(fd1[0], path, sizeof(path) - 1);
        close(fd1[0]);

        if (n <= 0)
            _exit(1);

        path[n] = '\0';
        file = open(path, O_RDONLY);

        if (file < 0) {
            const char *message = "File not found or cannot be opened.\n";
            write(fd2[1], message, strlen(message));
        } else {
            while ((n = (int)read(file, buffer, sizeof(buffer))) > 0)
                write(fd2[1], buffer, n);
            close(file);
        }

        close(fd2[1]);
        _exit(0);
    }

    close(fd1[0]);
    close(fd2[1]);

    printf("Enter file path: ");
    fflush(stdout);

    if (fgets(path, sizeof(path), stdin) == NULL) {
        close(fd1[1]);
        close(fd2[0]);
        wait(NULL);
        return 1;
    }

    path[strcspn(path, "\n")] = '\0';
    write(fd1[1], path, strlen(path));
    close(fd1[1]);

    printf("\nFile contents:\n");
    while ((n = (int)read(fd2[0], buffer, sizeof(buffer))) > 0)
        write(STDOUT_FILENO, buffer, n);

    close(fd2[0]);
    wait(NULL);
    return 0;
}
