#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>

int main(void)
{
    char sentence[1024], result[256];
    int fd, n, i, characters, words, lines, in_word;
    FILE *file;

    while (1) {
        fd = open("pipe1", O_RDONLY);
        if (fd < 0) {
            perror("open pipe1");
            return 1;
        }

        n = read(fd, sentence, sizeof(sentence) - 1);
        close(fd);

        if (n <= 0)
            continue;

        sentence[n] = '\0';

        characters = n;
        words = 0;
        lines = 0;
        in_word = 0;

        for (i = 0; i < n; i++) {
            if (sentence[i] == '\n')
                lines++;

            if (isspace((unsigned char)sentence[i])) {
                in_word = 0;
            } else if (!in_word) {
                words++;
                in_word = 1;
            }
        }

        file = fopen("result.txt", "w");
        if (file == NULL) {
            perror("fopen result.txt");
            return 1;
        }

        fprintf(file, "Characters: %d\nWords: %d\nLines: %d\n",
                characters, words, lines);
        fclose(file);

        file = fopen("result.txt", "r");
        if (file == NULL) {
            perror("fopen result.txt");
            return 1;
        }

        n = (int)fread(result, 1, sizeof(result) - 1, file);
        result[n] = '\0';
        fclose(file);

        fd = open("pipe2", O_WRONLY);
        if (fd < 0) {
            perror("open pipe2");
            return 1;
        }
        write(fd, result, strlen(result) + 1);
        close(fd);
    }

    return 0;
}
