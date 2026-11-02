#include <stdio.h>

int main(void)
{
    int alloc[10][10], max[10][10], need[10][10];
    int avail[10], work[10], finish[10] = {0};
    int safe[10];
    int n, m, i, j, count = 0, found;

    printf("Enter number of processes and resources: ");
    scanf("%d%d", &n, &m);

    if (n < 1 || n > 10 || m < 1 || m > 10) {
        printf("Use 1-10 processes and 1-10 resources.\n");
        return 1;
    }

    printf("Enter Allocation Matrix (%d x %d):\n", n, m);
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);

    printf("Enter Max Matrix (%d x %d):\n", n, m);
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
            if (max[i][j] < alloc[i][j]) {
                printf("Error: Max cannot be less than Allocation.\n");
                return 1;
            }
            need[i][j] = max[i][j] - alloc[i][j];
        }

    printf("Enter Available Resources: ");
    for (j = 0; j < m; j++) {
        scanf("%d", &avail[j]);
        work[j] = avail[j];
    }

    while (count < n) {
        found = 0;

        for (i = 0; i < n; i++) {
            if (!finish[i]) {
                for (j = 0; j < m; j++)
                    if (need[i][j] > work[j])
                        break;

                if (j == m) {
                    for (j = 0; j < m; j++)
                        work[j] += alloc[i][j];

                    safe[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        if (!found)
            break;
    }

    if (count == n) {
        printf("\nSystem is in SAFE state.\nSafe sequence: ");
        for (i = 0; i < n; i++) {
            printf("P%d", safe[i]);
            if (i < n - 1) printf(" -> ");
        }
        printf("\n");
    } else {
        printf("\nSystem is in UNSAFE state. No safe sequence exists.\n");
    }

    return 0;
}
