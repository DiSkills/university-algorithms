#include "number.h"

struct number *number__add(const struct number *n1, const struct number *n2)
{
    /* both numbers must be unsigned and have the same length */
    int i;
    struct number *sum;
    int size = n1->size;

    sum = number_init(size + 1);
    for (i = 0; i < size; i++) {
        int s = sum->digits[i] + n1->digits[i] + n2->digits[i];
        sum->digits[i] = s % NUMBER_BASE;
        sum->digits[i + 1] = s / NUMBER_BASE;
    }
    return sum;
}

static struct number *number__add_operation(const struct number *num1,
        char sign1, const struct number *num2, char sign2)
{
    struct number *sum;

    if (sign1 != sign2) {
        char sign = '+';
        if (sign1 == '-') {
            SWAP(num1, num2);
        }
        if (number__compare(num1, num2) < 0) {
            SWAP(num1, num2);
            sign = '-';
        }
        sum = number__sub(num1, num2);
        sum->sign = sign;
    } else {
        sum = number__add(num1, num2);
        sum->sign = sign1;
    }
    return sum;
}

struct number *number_add(const struct number *n1, const struct number *n2)
{
    return number__binary_operation(number__add_operation, n1, n2);
}
