#ifndef NUMBER_H
#define NUMBER_H

#ifndef NUMBER_BASE
#define NUMBER_BASE 16
#endif

struct number {
    char sign;
    char *digits;
    int size;
};

struct number *number_init(int size);
void number_del(struct number *n);
void number_from_string(struct number *n, const char *str);
void number_print(const struct number *n);
struct number *number_add(const struct number *n1, const struct number *n2);
struct number *number_sub(const struct number *n1, const struct number *n2);
struct number *number_shift_left(const struct number *n, int shift);

#endif
