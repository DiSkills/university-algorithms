#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash_table.h"

static int hash(const char *s)
{
    int sum = 0;
    for (; *s; sum += *s, s++)
        {}
    return sum;
}

#ifdef RANDOM_REHASHING
static void shuffle(int *arr, int size)
{
    int i;
    for (i = size - 1; i > 0; i--) {
        int tmp;
        int j = rand() % (i + 1);

        tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
    }
}
#endif

struct hash_table *hash_table_init()
{
#ifdef RANDOM_REHASHING
    int i;
#endif
    struct hash_table *table = malloc(sizeof(*table));

    memset(table, 0, sizeof(*table));
    table->hash = hash;
#ifdef RANDOM_REHASHING
    for (i = 0; i < HASH_TABLE_SIZE; i++) {
        table->indexes[i] = i;
    }
    shuffle(table->indexes, HASH_TABLE_SIZE);
#endif
    return table;
}

void hash_table_del(struct hash_table *table)
{
    int i;
    for (i = 0; i < HASH_TABLE_SIZE; i++) {
        if (table->data[i]) {
            free(table->data[i]);
            table->data[i] = NULL;
        }
    }
    table->size = 0;
}

void hash_table_print(const struct hash_table *table)
{
    int i;
    for (i = 0; i < HASH_TABLE_SIZE; i++) {
        if (table->data[i]) {
            puts(table->data[i]);
        }
    }
}

int hash_table_add_counting(struct hash_table *table, char *s, int *pcounter)
{
    int i, h;

    h = table->hash(s) % HASH_TABLE_SIZE;
    for (i = 0; i < HASH_TABLE_SIZE; i++) {
        int index;
#ifdef RANDOM_REHASHING
        index = (h + table->indexes[i]) % HASH_TABLE_SIZE;
#else
        index = (h + i) % HASH_TABLE_SIZE;
#endif
        if (!table->data[index]) {
            table->data[index] = s;
            table->size++;
            return 1;
        }
        (*pcounter)++;
    }
    return 0;
}

int hash_table_add(struct hash_table *table, char *s)
{
    int counter = 0;
    return hash_table_add_counting(table, s, &counter);
}
