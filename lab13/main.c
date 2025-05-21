#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static int *array_input(int len)
{
    int i;
    int *arr = malloc(sizeof(*arr) * len);
    for (i = 0; i < len; i++) {
        scanf("%d", arr + i);
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

static double median(int *a, int m, int *b, int n)
{
    int left, right;

    if (m > n) {
        int tmplen, *tmparr;

        tmparr = a;
        a = b;
        b = tmparr;

        tmplen = m;
        m = n;
        n = tmplen;
    }

    left = 0;
    right = m;

    while (left <= right) {
        int partition1, partition2, mla, mra, mlb, mrb;

        partition1 = (left + right) / 2;
        partition2 = (m + n + 1) / 2 - partition1;

        mla = (partition1 == 0) ? INT_MIN : a[partition1 - 1];
        mra = (partition1 == m) ? INT_MAX : a[partition1];
        mlb = (partition2 == 0) ? INT_MIN : b[partition2 - 1];
        mrb = (partition2 == n) ? INT_MAX : b[partition2];

        if (mla <= mrb && mlb <= mra) {
            if ((m + n) % 2 == 0) {
                return (double)(max(mla, mlb) + min(mra, mrb)) / 2;
            }
            return max(mla, mlb);
        }

        if (mla > mrb) {
            right = partition1 - 1;
        } else {
            left = partition1 + 1;
        }
    }
    return 0;
}

int main(int argc, char **argv)
{
    int *a, *b, m, n;

    if (argc != 3) {
        fprintf(stderr, "Expected: %s <size1> <size2>\n", argv[0]);
        return 1;
    }
    m = atoi(argv[1]);
    n = atoi(argv[2]);

    a = array_input(m);
    b = array_input(n);

    printf("%f\n", median(a, m, b, n));

    free(a);
    free(b);
    return 0;
}
