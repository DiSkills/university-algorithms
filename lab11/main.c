#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "graph.h"

int main(int argc, char **argv)
{
    struct graph *g;
    int d, size;
    int code = 1;

    if (argc != 2) {
        fprintf(stderr, "Expected: %s <size>\n", argv[0]);
        return 1;
    }
    srand(time(NULL));

    g = graph_init(atoi(argv[1]));
    graph_input(g);

    size = g->size;
    for (d = 1; d < size + 1; d++) {
        if (size % d == 0) {
            int res;
            struct graph *h;

            if (d > (size / d)) {
                break;
            }
            h = graph_init(size);
            graph_generate(h, d, size / d);

            res = graph_is_isomorphic(g, h);

            graph_del(h);
            free(h);

            if (res) {
                printf("%d %d\n", d, size / d);
                code = 0;
                goto clean;
            }
        }
    }
    fprintf(stderr, "Graph is not valid\n");

clean:
    graph_del(g);
    free(g);
    return code;
}
