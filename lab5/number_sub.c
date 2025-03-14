#include "number.h"

struct number *number__sub(const struct number *n1, const struct number *n2)
{
    /* both numbers must be unsigned and have the same length */
    int i;
    struct number *difference;
    int size = n1->size;

    difference = number_init(size);
    for (i = 0; i < size; i++) {
        int diff = difference->digits[i] + n1->digits[i] - n2->digits[i];
        if (diff < 0) {
            diff += NUMBER_BASE;
            difference->digits[i + 1] = -1;
        }
        difference->digits[i] = diff;
    }
    return difference;
}

static struct number *number__sub_operation(const struct number *num1,
        char sign1, const struct number *num2, char sign2)
{
    struct number *difference;

    if (sign1 != sign2) {
        difference = number__add(num1, num2);
        difference->sign = sign1;
    } else {
        char sign = '+';
        if (sign2 == '-') {
            SWAP(num1, num2);
        }
        if (number__compare(num1, num2) < 0) {
            SWAP(num1, num2);
            sign = '-';
        }
        difference = number__sub(num1, num2);
        difference->sign = sign;
    }
    return difference;
}

struct number *number_sub(const struct number *n1, const struct number *n2)
{
    return number__binary_operation(number__sub_operation, n1, n2);
}
