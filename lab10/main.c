#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "graph.h"

int main(int argc, char **argv)
{
    struct graph *g, *h;

    if (argc != 2) {
        fprintf(stderr, "Expected: %s <size>\n", argv[0]);
        return 1;
    }
    srand(time(NULL));

    g = graph_init(atoi(argv[1]));
    graph_generate(g);
    h = graph_shuffle(g);

    graph_is_isomorphic(g, h);
    printf("%lld\n", counter);

    graph_del(g);
    free(g);
    graph_del(h);
    free(h);
    return 0;
}
