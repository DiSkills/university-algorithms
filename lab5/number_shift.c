#include <string.h>

#include "number.h"

struct number *number_shift_left(const struct number *n, int shift)
{
    struct number *sh = number_init(n->size + shift);
    sh->sign = n->sign;
    memcpy(sh->digits + shift, n->digits, n->size);
    return sh;
}
