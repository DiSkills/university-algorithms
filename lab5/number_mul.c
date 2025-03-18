#include <stdlib.h>
#include <string.h>

#include "number.h"

static struct number *number__first(const struct number *a2,
        const struct number *b2)
{
    struct number *a2b2, *a2b2n, *a2b2n2, *res;
    int size = a2->size;

    a2b2 = number_mul(a2, b2);
    a2b2n = number_shift_left(a2b2, size * 2); counter++;
    a2b2n2 = number_shift_left(a2b2, size);

    number_del(a2b2);
    free(a2b2);

    res = number_add(a2b2n, a2b2n2);

    number_del(a2b2n);
    free(a2b2n);
    number_del(a2b2n2);
    free(a2b2n2);
    return res;
}

static struct number *number__second(const struct number *a2,
        const struct number *a1, const struct number *b2,
        const struct number *b1)
{
    struct number *a2a1, *b1b2, *a2a1b1b2, *res;
    int size = a2->size;

    a2a1 = number_sub(a2, a1);
    b1b2 = number_sub(b1, b2);
    a2a1b1b2 = number_mul(a2a1, b1b2);

    number_del(a2a1);
    free(a2a1);
    number_del(b1b2);
    free(b1b2);

    res = number_shift_left(a2a1b1b2, size);

    number_del(a2a1b1b2);
    free(a2a1b1b2);
    return res;
}

static struct number *number__third(const struct number *a1,
        const struct number *b1)
{
    struct number *a1b1, *a1b1n2, *res;
    int size = a1->size;

    a1b1 = number_mul(a1, b1);
    a1b1n2 = number_shift_left(a1b1, size);

    res = number_add(a1b1, a1b1n2);

    number_del(a1b1);
    free(a1b1);
    number_del(a1b1n2);
    free(a1b1n2);
    return res;
}

struct number *number__mul(const struct number *n1, const struct number *n2)
{
    /* both numbers must be unsigned and have the same length */
    int i, size;
    struct number *a[2], *b[2];
    struct number *first, *second, *third, *s, *res;

    counter++;
    if (n1->size == 1) {
        int mul = n1->digits[0] * n2->digits[0]; counter += 2;
        res = number_init(2);
        res->digits[0] = mul % NUMBER_BASE; counter += 2;
        res->digits[1] = mul / NUMBER_BASE; counter += 2;
        counter++;
        return res;
    }

    size = (n1->size - 1) / 2 + 1; counter += 4;
    for (i = 0; i < 2; i++) {
        a[i] = number_init(size);
        b[i] = number_init(size);
    }
    memcpy(a[0]->digits, n1->digits, size);
    memcpy(a[1]->digits, n1->digits + size, n1->size - size);
    memcpy(b[0]->digits, n2->digits, size);
    memcpy(b[1]->digits, n2->digits + size, n2->size - size);

    first = number__first(a[1], b[1]);
    second = number__second(a[1], a[0], b[1], b[0]);

    s = number_add(first, second);
    number_del(first);
    free(first);
    number_del(second);
    free(second);

    third = number__third(a[0], b[0]);
    res = number_add(third, s);
    number_del(third);
    free(third);
    number_del(s);
    free(s);

    for (i = 0; i < 2; i++) {
        number_del(a[i]);
        free(a[i]);
        number_del(b[i]);
        free(b[i]);
    }
    counter++;
    return res;
}

static struct number *number__mul_operation(const struct number *num1,
        char sign1, const struct number *num2, char sign2)
{
    char sign;
    struct number *mul;

    sign = '+'; counter++;
    if (sign1 != sign2) {
        sign = '-'; counter++;
    } counter++;

    mul = number__mul(num1, num2);
    mul->sign = sign; counter++;
    return mul;
}

struct number *number_mul(const struct number *n1, const struct number *n2)
{
    return number__binary_operation(number__mul_operation, n1, n2);
}
