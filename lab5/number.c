#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "number.h"

#define DIGIT_TO_INT(C) ((C) - ((C) <= '9' ? '0' : 'a' - 10))
#define INT_TO_DIGIT(N) ((N) + ((N) <= 9 ? '0' : 'a' - 10))

struct number *number_init(int size)
{
    struct number *n = malloc(sizeof(*n));
    n->size = size;
    n->digits = calloc(size, sizeof(char));
    n->sign = '+';
    return n;
}

void number_del(struct number *n)
{
    free(n->digits);
    n->digits = NULL;
    n->size = 0;
    n->sign = '+';
}

struct number *number_from_string(const char *str)
{
    char *digits;
    const char *s;
    struct number *n;
    int size = strlen(str) - 1;

    n = number_init(size);
    digits = n->digits;
    for (s = str + size; s > str; s--) {
        *digits = DIGIT_TO_INT(*s);
        digits++;
    }
    n->sign = str[0];
    return n;
}

void number_print(const struct number *n)
{
    const char *digits;

    putchar(n->sign);
    for (digits = n->digits + n->size - 1; digits >= n->digits; digits--) {
        putchar(INT_TO_DIGIT(*digits));
    }
}

static void number_strip(struct number *n)
{
    int i = n->size - 1;
    while (i > 0 && n->digits[i] == 0) {
        i--;
    }
    n->size = i + 1;
    n->digits = realloc(n->digits, n->size);
}

struct number *number__binary_operation(number_binop function,
        const struct number *n1, const struct number *n2)
{
    struct number *num1, *num2, *res;
    int size = MAX(n1->size, n2->size);

    num1 = number_init(size);
    memcpy(num1->digits, n1->digits, n1->size);
    num2 = number_init(size);
    memcpy(num2->digits, n2->digits, n2->size);

    res = function(num1, n1->sign, num2, n2->sign);
    number_strip(res);

    number_del(num1);
    free(num1);
    number_del(num2);
    free(num2);
    return res;
}
