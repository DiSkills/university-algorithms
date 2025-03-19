#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "hash_table.h"

static const char printable[] = "0123456789"
    "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ \t\n";

static char *generate()
{
    int i;
    char *s;
    int size = rand() % (20 - 5 + 1) + 5;

    s = malloc(size + 1);
    for (i = 0; i < size; i++) {
        s[i] = printable[rand() % (sizeof(printable) - 1)];
    }
    s[size] = '\0';
    return s;
}

static void fill(struct hash_table *table, double load_factor)
{
    while ((double)table->size / HASH_TABLE_SIZE < load_factor) {
        char *s = generate();
        hash_table_add(table, s);
    }
}

int main(int argc, char **argv)
{
    double load_factor;
    struct hash_table *table;
    int counter = 0;

    if (argc != 2) {
        fprintf(stderr, "Expected: %s <load-factor>\n", argv[0]);
        return 1;
    }
    load_factor = atof(argv[1]);

    srand(time(NULL));

    table = hash_table_init();
    fill(table, load_factor);

    hash_table_add_counting(table, generate(), &counter);
    printf("%d\n", counter);

    hash_table_del(table);
    free(table);
    return 0;
}
