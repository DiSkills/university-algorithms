#ifndef GRAPH_H
#define GRAPH_H

struct graph {
    int **matrix;
    int size;
};

extern long long counter; /* Bad, very bad... I hate myself!!! */
/* https://www.youtube.com/watch?v=lIX3hecWFAY */

struct graph *graph_init(int size);
void graph_generate(struct graph *g);
void graph_print(const struct graph *g);
void graph_del(struct graph *g);
struct graph *graph_shuffle(const struct graph *g);
int graph_is_isomorphic(const struct graph *g, const struct graph *h);

#endif
