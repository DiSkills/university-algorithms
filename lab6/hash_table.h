#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#ifndef HASH_TABLE_SIZE
#define HASH_TABLE_SIZE 2000
#endif

typedef int (*hash_function)(const char *);

struct hash_table {
    char *data[HASH_TABLE_SIZE];
    int size;
    hash_function hash;
#ifdef RANDOM_REHASHING
    int indexes[HASH_TABLE_SIZE];
#endif
};

struct hash_table *hash_table_init();
void hash_table_del(struct hash_table *table);
void hash_table_print(const struct hash_table *table);
int hash_table_add_counting(struct hash_table *table, char *s, int *pcounter);
int hash_table_add(struct hash_table *table, char *s);

#endif
