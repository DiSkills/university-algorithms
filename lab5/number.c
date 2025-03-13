#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "number.h"

static int digit_to_int(char c)
{
    return c - (c <= '9' ? '0' : 'a' - 10);
}

static char int_to_digit(int n)
{
    return n + (n <= 9 ? '0' : 'a' - 10);
}

static int number_compare(const struct number *n1, const struct number *n2)
{
    int i, size;

    if (n1->sign != n2->sign) {
        return (n1->sign == '-') ? -1 : 1;
    }
    size = n1->size;

    for (i = size - 1; i >= 0; i--) {
        if (n1->digits[i] != n2->digits[i]) {
            return n1->digits[i] < n2->digits[i] ? -1 : 1;
        }
    }
    return 0;
}

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

void number_from_string(struct number *n, const char *str)
{
    char *digits;
    const char *s;

    digits = n->digits;
    s = str + strlen(str) - 1;
    while (s > str) {
        *digits = digit_to_int(*s);
        digits++;
        s--;
    }
    n->sign = str[0];
}

void number_print(const struct number *n)
{
    const char *digits;

    putchar(n->sign);
    for (digits = n->digits + n->size - 1; digits >= n->digits; digits--) {
        putchar(int_to_digit(*digits));
    }
}

struct number *number_add(const struct number *n1, const struct number *n2)
{
    int i, carry, size;
    struct number *sum;

    if (n1->sign != n2->sign) {
        struct number tmp = n1->sign == '-' ? *n1 : *n2;
        tmp.sign = '+';
        return number_sub(n1->sign == '+' ? n1 : n2, &tmp);
    }
    size = n1->size;
    sum = number_init(size + 1);

    carry = 0;
    for (i = 0; i < size; i++) {
        int s = n1->digits[i] + n2->digits[i] + carry;
        sum->digits[i] = s % NUMBER_BASE;
        carry = s / NUMBER_BASE;
    }
    sum->digits[i] = carry;
    sum->sign = n1->sign;
    return sum;
}

struct number *number_sub(const struct number *n1, const struct number *n2)
{
    int i, size;
    struct number *difference;

    if (n1->sign != n2->sign) {
        struct number tmp = *n2;
        tmp.sign = n1->sign;
        return number_add(n1, &tmp);
    } else if (n2->sign == '-') {
        struct number tmp1 = *n1, tmp2 = *n2;
        tmp1.sign = '+';
        tmp2.sign = '+';
        return number_sub(&tmp2, &tmp1);
    }
    size = n1->size;
    difference = number_init(size + 1);

    if (number_compare(n1, n2) < 0) {
        const struct number *tmp = n1;
        n1 = n2;
        n2 = tmp;
        difference->sign = '-';
    }

    for (i = 0; i < size; i++) {
        int diff = difference->digits[i] + n1->digits[i] - n2->digits[i];
        if (diff < 0) {
            diff += NUMBER_BASE;
            difference->digits[i + 1] -= 1;
        }
        difference->digits[i] = diff;
    }
    return difference;
}

struct number *number_shift_left(const struct number *n, int shift)
{
    struct number *sh = number_init(n->size + shift);
    sh->sign = n->sign;
    memcpy(sh->digits + shift, n->digits, n->size);
    return sh;
}
