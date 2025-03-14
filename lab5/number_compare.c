#include <stdlib.h>
#include <string.h>

#include "number.h"

int number__compare(const struct number *n1, const struct number *n2)
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

int number_compare(const struct number *n1, const struct number *n2)
{
    int compare;
    struct number *num1, *num2;
    int size = MAX(n1->size, n2->size);

    num1 = number_init(size);
    memcpy(num1->digits, n1->digits, n1->size);
    num1->sign = n1->sign;

    num2 = number_init(size);
    memcpy(num2->digits, n2->digits, n2->size);
    num2->sign = n2->sign;

    compare = number__compare(num1, num2);

    number_del(num1);
    free(num1);
    number_del(num2);
    free(num2);
    return compare;
}
