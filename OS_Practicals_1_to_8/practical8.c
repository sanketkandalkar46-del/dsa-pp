#include <stdio.h>
#include <stdlib.h>

#define MAX 50

int main(void)
{
    int n, req[MAX], s[MAX], done[MAX] = {0};
    int head, cylinders, i, j, temp;
    int cur, total, min, idx;

    printf("Enter total number of cylinders: ");
    scanf("%d", &cylinders);

    if (cylinders < 1) {
        printf("Invalid cylinder count.\n");
        return 1;
    }

    printf("Enter number of requests: ");
    scanf("%d", &n);

    if (n < 1 || n > MAX) {
        printf("Enter 1 to %d requests.\n", MAX);
        return 1;
    }

    printf("Enter the request queue: ");
    for (i = 0; i < n; i++) {
        scanf("%d", &req[i]);
        if (req[i] < 0 || req[i] >= cylinders) {
            printf("Request must be between 0 and %d.\n", cylinders - 1);
            return 1;
        }
        s[i] = req[i];
    }

    printf("Enter initial head position: ");
    scanf("%d", &head);

    if (head < 0 || head >= cylinders) {
        printf("Head must be between 0 and %d.\n", cylinders - 1);
        return 1;
    }

    /* Sort requests in ascending order. */
    for (i = 0; i < n - 1; i++)
        for (j = 0; j < n - i - 1; j++)
            if (s[j] > s[j + 1]) {
                temp = s[j];
                s[j] = s[j + 1];
                s[j + 1] = temp;
            }

    /* SSTF */
    cur = head;
    total = 0;
    printf("\nSSTF Order: %d", head);

    for (i = 0; i < n; i++) {
        min = 1000000;
        idx = -1;

        for (j = 0; j < n; j++) {
            if (!done[j] && abs(req[j] - cur) < min) {
                min = abs(req[j] - cur);
                idx = j;
            }
        }

        done[idx] = 1;
        total += min;
        cur = req[idx];
        printf(" -> %d", cur);
    }
    printf("\nTotal head movement = %d\n", total);

    /* SCAN: initially move towards cylinder 0. */
    cur = head;
    total = 0;
    printf("\nSCAN Order: %d", head);

    for (i = n - 1; i >= 0; i--) {
        if (s[i] <= head) {
            total += cur - s[i];
            cur = s[i];
            printf(" -> %d", cur);
        }
    }

    if (cur != 0) {
        total += cur;
        cur = 0;
        printf(" -> 0");
    }

    for (i = 0; i < n; i++) {
        if (s[i] > head) {
            total += s[i] - cur;
            cur = s[i];
            printf(" -> %d", cur);
        }
    }
    printf("\nTotal head movement = %d\n", total);

    /* C-LOOK: move down, jump to highest request, then move down. */
    cur = head;
    total = 0;
    printf("\nC-LOOK Order: %d", head);

    for (i = n - 1; i >= 0; i--) {
        if (s[i] <= head) {
            total += cur - s[i];
            cur = s[i];
            printf(" -> %d", cur);
        }
    }

    for (i = n - 1; i >= 0; i--) {
        if (s[i] > head) {
            total += abs(cur - s[i]);
            cur = s[i];
            printf(" -> %d", cur);
        }
    }
    printf("\nTotal head movement = %d\n", total);

    return 0;
}
