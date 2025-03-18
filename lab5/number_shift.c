#include <string.h>

#include "number.h"

struct number *number_shift_left(const struct number *n, int shift)
{
    struct number *sh = number_init(n->size + shift); counter += 1;
    sh->sign = n->sign; counter += 1;
    memcpy(sh->digits + shift, n->digits, n->size); counter += n->size + 1;
    return sh;
}
