#include <stdio.h>
#include <stdlib.h>

#include "number.h"

#undef BINARY_OPERATION
#undef UNARY_OPERATION

#if defined(ADD) || defined(SUB) || defined(MUL)
#define BINARY_OPERATION
#elif defined(SHL)
#define UNARY_OPERATION
#endif

#ifdef BINARY_OPERATION
typedef struct number *(*binop)(const struct number *n1,
        const struct number *n2);
static void demo_binary_operation(binop function, char c,
        const char *s1, const char *s2)
{
    struct number *n1, *n2, *res;

    n1 = number_from_string(s1);
    n2 = number_from_string(s2);

    number_print(n1);
    printf(" %c ", c);
    number_print(n2);
    printf(" = ");
    res = function(n1, n2);
    number_print(res);
    putchar('\n');

    number_del(n1);
    free(n1);
    number_del(n2);
    free(n2);
    number_del(res);
    free(res);
}
#endif

#ifdef UNARY_OPERATION
typedef struct number *(*unop)(const struct number *num, int n);
static void demo_unary_operation(unop function, const char *c,
        const char *s, int n)
{
    struct number *num, *res;

    num = number_from_string(s);

    number_print(num);
    printf(" %s %d = ", c, n);
    res = function(num, n);
    number_print(res);
    putchar('\n');

    number_del(num);
    free(num);
    number_del(res);
    free(res);
}
#endif

int main(int argc, char **argv)
{
#ifdef BINARY_OPERATION
    binop operation;
    char c;
#endif
#ifdef UNARY_OPERATION
    unop operation;
    const char *c;
#endif

    if (argc != 3) {
        fprintf(stderr, "Expected: %s <number> <number>\n", argv[0]);
        return 1;
    }

#ifdef BINARY_OPERATION
#   ifdef ADD
    operation = number_add;
    c = '+';
#   elif defined(SUB)
    operation = number_sub;
    c = '-';
#   elif defined(MUL)
    operation = number_mul;
    c = '*';
#   endif
    demo_binary_operation(operation, c, argv[1], argv[2]);
#endif
#ifdef UNARY_OPERATION
#   ifdef SHL
    operation = number_shift_left;
    c = "<<";
#   endif
    demo_unary_operation(operation, c, argv[1], atoi(argv[2]));
#endif
    return 0;
}
