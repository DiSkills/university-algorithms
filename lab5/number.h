#ifndef NUMBER_H
#define NUMBER_H

#ifndef NUMBER_BASE
#define NUMBER_BASE 16
#endif

#define MAX(A, B) ((A) > (B) ? (A) : (B))

#define SWAP(A, B)                                                           \
    do {                                                                     \
        const void *tmp = (A);                                               \
        (A) = (B);                                                           \
        (B) = tmp;                                                           \
    } while (0)

extern long long counter; /* Bad, very bad... I hate myself!!! */
/* https://www.youtube.com/watch?v=lIX3hecWFAY */

struct number {
    char sign;
    char *digits;
    int size;
};

typedef struct number *(*number_binop)(const struct number *n1,
        char sign1, const struct number *n2, char sign2);

struct number *number_init(int size);
void number_del(struct number *n);
struct number *number_from_string(const char *str);
void number_print(const struct number *n);

struct number *number__binary_operation(number_binop function,
        const struct number *n1, const struct number *n2);
struct number *number__add(const struct number *n1, const struct number *n2);
struct number *number__sub(const struct number *n1, const struct number *n2);
int number__compare(const struct number *n1, const struct number *n2);
struct number *number__mul(const struct number *n1, const struct number *n2);

struct number *number_add(const struct number *n1, const struct number *n2);
struct number *number_sub(const struct number *n1, const struct number *n2);
int number_compare(const struct number *n1, const struct number *n2);
struct number *number_shift_left(const struct number *n, int shift);
struct number *number_mul(const struct number *n1, const struct number *n2);

#endif
