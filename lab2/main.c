#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef int *array;

static array array_init_random(int size)
{
    int i;
    array arr = malloc(sizeof(*arr) * size);

    for (i = 0; i < size; i++) {
        arr[i] = rand() % 100;
    }

    return arr;
}

#ifdef PRINT
static void array_print(const array arr, int size)
{
    int i;

    for (i = 0; i < size; i++) {
        printf(" %3d", arr[i]);
    }
}
#endif

static int array_sort_cost(array arr, int size)
{
    int i;
    int counter = 0;

    for (i = 1; i < size; i++) {
        int key, j;

        key = arr[i]; counter++;
        j = i - 1; counter += 2;
        while (j >= 0 && arr[j] > key) { counter += 2;
            arr[j + 1] = arr[j]; counter += 2;
            j--; counter++;
        } counter += (j >= 0) ? 2 : 1;
        arr[j + 1] = key; counter += 2;
    }

    return counter;
}

int main(int argc, char **argv)
{
    array arr;
    int size, cost;

    if (argc != 2) {
        fprintf(stderr, "Expected: %s <size>\n", argv[0]);
        return 1;
    }
    size = atoi(argv[1]);

    srand(time(NULL));
    arr = array_init_random(size);
#ifdef PRINT
    array_print(arr, size);
    printf("\n");
#endif

    cost = array_sort_cost(arr, size);
#ifdef PRINT
    array_print(arr, size);
    printf("\n");
#else
    printf("%d\n", cost);
#endif

    free(arr);
    return 0;
}
