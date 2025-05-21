#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static int *array_input(int len)
{
    int i;
    int *arr = malloc(sizeof(*arr) * len);
    arr[0] = rand() % 100;
    for (i = 1; i < len; i++) {
        arr[i] = arr[i - 1] + rand() % 50;
    }
    return arr;
}

static int max(int a, int b)
{
    return (a > b) ? a : b;
}

static int min(int a, int b)
{
    return (a < b) ? a : b;
}

static int median(int *a, int m, int *b, int n)
{
    int left, right;
    int counter = 0;

    counter++;
    if (m > n) {
        int tmplen, *tmparr;

        tmparr = a; counter++;
        a = b; counter++;
        b = tmparr; counter++;

        tmplen = m; counter++;
        m = n; counter++;
        n = tmplen; counter++;
    }

    left = 0; counter++;
    right = m; counter++;

    while (left <= right) { counter++;
        int partition1, partition2, mla, mra, mlb, mrb;

        partition1 = (left + right) / 2; counter += 3;
        partition2 = (m + n + 1) / 2 - partition1; counter += 5;

        counter++;
        if (partition1 == 0) {
            mla = INT_MIN; counter++;
        } else {
            mla = a[partition1 - 1]; counter += 2;
        }

        counter++;
        if (partition1 == m) {
            mra = INT_MAX; counter++;
        } else {
            mra = a[partition1]; counter++;
        }

        counter++;
        if (partition2 == 0) {
            mlb = INT_MIN; counter++;
        } else {
            mlb = b[partition2 - 1]; counter += 2;
        }

        counter++;
        if (partition2 == n) {
            mrb = INT_MAX; counter++;
        } else {
            mrb = b[partition2]; counter++;
        }

        if (mla <= mrb && mlb <= mra) { counter += 2;
            counter += 3;
            if ((m + n) % 2 == 0) {
                counter += 4;
                /* return (double)(max(mla, mlb) + min(mra, mrb)) / 2; */
                return counter;
            }
            counter++;
            /* return max(mla, mlb); */
            return counter;
        }
        counter += (mla <= mrb) ? 2 : 1;

        counter++;
        if (mla > mrb) {
            right = partition1 - 1; counter += 2;
        } else {
            left = partition1 + 1; counter += 2;
        }
    }
    /* return 0; */
    counter++;
    return counter;
}

int main(int argc, char **argv)
{
    int *a, *b, m, n;

    if (argc != 3) {
        fprintf(stderr, "Expected: %s <size1> <size2>\n", argv[0]);
        return 1;
    }
    srand(time(NULL));
    m = atoi(argv[1]);
    n = atoi(argv[2]);

    a = array_input(m);
    b = array_input(n);

    printf("%d\n", median(a, m, b, n));

    free(a);
    free(b);
    return 0;
}
