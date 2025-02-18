#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef int *array;
typedef int (*array_generator)();

static array array_init(array_generator generator, int size)
{
    int i;
    array arr = malloc(sizeof(*arr) * size);

    for (i = 0; i < size; i++) {
        arr[i] = generator();
    }

    return arr;
}

static int array_random_generator()
{
    return random() % 1000 - 500;
}

static int array_increasing_generator()
{
    static int number = 0;
    number++;
    return number - 1;
}

static int array_decreasing_generator()
{
    static int number = 0;
    number--;
    return number + 1;
}

#ifdef PRINT
static void array_print(const array arr, int size)
{
    int i;

    for (i = 0; i < size; i++) {
        printf(" %4d", arr[i]);
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

static void sort_generated_array(array_generator generator, int size)
{
    int cost;
    array arr = array_init(generator, size);

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
}

int main(int argc, char **argv)
{
    int size;

    if (argc != 2) {
        fprintf(stderr, "Expected: %s <size>\n", argv[0]);
        return 1;
    }
    size = atoi(argv[1]);

    srand(time(NULL));

#ifdef MIN_TIME
    sort_generated_array(array_increasing_generator, size);
#elifdef MAX_TIME
    sort_generated_array(array_decreasing_generator, size);
#else
    sort_generated_array(array_random_generator, size);
#endif
    return 0;
}
