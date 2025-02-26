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

static void array_sort(array arr, int first, int last)
{
    int i, j, x;

    i = first;
    j = last;
    x = arr[(first + last) / 2];
    do {
        while (arr[i] < x) {
            i++;
        }
        while (arr[j] > x) {
            j--;
        }

        if (i <= j) {
            if (i < j) {
                int tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
            }
            i++;
            j--;
        }
    } while (i <= j);

    if (i < last) {
        array_sort(arr, i, last);
    }
    if (first < j) {
        array_sort(arr, first,j);
    }
}

static void sort_generated_array(array_generator generator, int size)
{
    array arr = array_init(generator, size);

#ifdef PRINT
    array_print(arr, size);
    printf("\n");
#endif

    array_sort(arr, 0, size - 1);
#ifdef PRINT
    array_print(arr, size);
    printf("\n");
#else
    /* printf("%d\n", cost); */
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

/* #ifdef MIN_TIME */
/*     sort_generated_array(array_increasing_generator, size); */
/* #elifdef MAX_TIME */
/*     sort_generated_array(array_decreasing_generator, size); */
/* #else */
    sort_generated_array(array_random_generator, size);
/* #endif */
    return 0;
}
