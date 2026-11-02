#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main(void)
{
    char sentence[1024], result[1024];
    int fd, n;

    while (1) {
        printf("Enter a sentence (type exit to stop): ");
        fflush(stdout);

        if (fgets(sentence, sizeof(sentence), stdin) == NULL)
            break;

        if (strcmp(sentence, "exit\n") == 0)
            break;

        fd = open("pipe1", O_WRONLY);
        if (fd < 0) {
            perror("open pipe1");
            return 1;
        }
        write(fd, sentence, strlen(sentence));
        close(fd);

        fd = open("pipe2", O_RDONLY);
        if (fd < 0) {
            perror("open pipe2");
            return 1;
        }

        n = read(fd, result, sizeof(result) - 1);
        close(fd);

        if (n > 0) {
            result[n] = '\0';
            printf("\nResults from Process 2:\n%s\n", result);
        }
    }

    return 0;
}
