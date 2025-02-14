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

static void array_print(const array arr, int size)
{
    int i;

    for (i = 0; i < size; i++) {
        printf(" %3d", arr[i]);
    }
}

static void array_sort(array arr, int size)
{
    int i;

    for (i = 1; i < size; i++) {
        int key, j;

        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

int main(int argc, char **argv)
{
    int size;
    array arr;

    if (argc != 2) {
        fprintf(stderr, "Expected: %s <size>\n", argv[0]);
        return 1;
    }
    size = atoi(argv[1]);

    srand(time(NULL));
    arr = array_init_random(size);
    array_print(arr, size);
    printf("\n");

    array_sort(arr, size);
    array_print(arr, size);
    printf("\n");

    free(arr);
    return 0;
}
