#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifndef HASH_TABLE_SIZE
#define HASH_TABLE_SIZE 2000
#endif

#define MIN(A, B) ((A) < (B) ? (A) : (B))

static unsigned rank(unsigned value)
{
    unsigned rk;

    if (value == 0) {
        return sizeof(value) * 8;
    }

    rk = 0;
    while (!(value & 1)) {
        rk++;
        value >>= 1;
    }
    return rk;
}

static int generate_url(int m)
{
    return rand() % m;
}

static unsigned hash(int value, int n)
{
    unsigned res = 5381;
    do {
        res *= 33;
        res += value % 10 + '0';
        value /= 10;
    } while (value > 0);
    return res % n;
}

int main(int argc, char **argv)
{
    int m, s;
    unsigned r;
    double e, d;

    if (argc != 3) {
        fprintf(stderr, "Expected: %s <m> <s>\n", argv[0]);
        return 1;
    }
    m = atoi(argv[1]);
    s = atoi(argv[2]);

    srand(time(NULL));

    r = rank(hash(generate_url(m), HASH_TABLE_SIZE));
    for (; s > 1; s--) {
        int i = rank(hash(generate_url(m), HASH_TABLE_SIZE));
        r = MIN(r, i);
    }

    e = fabs(m - (1 << r) / 0.77351);
    d = e / m;

    printf("%f %f\n", e, d);
    return 0;
}
