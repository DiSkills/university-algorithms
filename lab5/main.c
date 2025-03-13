#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX(A, B) ((A) > (B) ? (A) : (B))

#include "number.h"

typedef struct number *(*operation)(const struct number *n1,
        const struct number *n2);

static void demo_operation(operation op, char c,
        const struct number *n1, const struct number *n2)
{
    struct number *res;

    number_print(n1);
    printf(" %c ", c);
    number_print(n2);
    printf(" = ");
    res = op(n1, n2);
    number_print(res);
    putchar('\n');

    number_del(res);
    free(res);
}

static void demo(const char *s1, const char *s2)
{
    int shift;
    struct number *n1, *n2, *sh;
    int len = MAX(strlen(s1), strlen(s2)) - 1;

    n1 = number_init(len);
    number_from_string(n1, s1);

    n2 = number_init(len);
    number_from_string(n2, s2);

    demo_operation(number_add, '+', n1, n2);
    demo_operation(number_sub, '-', n1, n2);

    shift = 3;
    number_print(n1);
    printf(" << %d = ", shift);
    sh = number_shift_left(n1, shift);
    number_print(sh);
    putchar('\n');

    number_del(n1);
    free(n1);
    number_del(n2);
    free(n2);
    number_del(sh);
    free(sh);
}

int main(int argc, char **argv)
{
    if (argc != 3) {
        fprintf(stderr, "Expected: %s <number> <number>\n", argv[0]);
        return 1;
    }

    demo(argv[1], argv[2]);
    return 0;
}
