#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef char **picture;

struct point {
    int x, y;
};

static int randint(int a, int b)
{
    return rand() % (b - a + 1) + a;
}

static picture picture_init(int size)
{
    int i, s, x, y;
    picture pic = malloc(size * sizeof(*pic));

    for (i = 0; i < size; i++) {
        int j;

        pic[i] = malloc(size * sizeof(*pic[i]));
        for (j = 0; j < size; j++) {
            pic[i][j] = '0';
        }
    }

    s = randint(5, size);
    if (s % 2 == 0) {
        s--;
    }
    x = randint(0, size - s / 2);
    y = randint(0, size - s);

    for (i = 0; i < s; i++) {
        pic[y + i][x + s / 2 - 1] = '1';
        if (i > s / 2) {
            pic[y + i][x + i - s / 2 - 1] = '1';
        }
    }
    return pic;
}

static void picture_print(picture pic, int size)
{
    int i, j;
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            printf("%c%c", pic[i][j], j != size - 1 ? ' ' : '\n');
        }
    }
}

static void strip(char *arr, int size, int *start, int *end)
{
    *start = 0;
    while (*start < size && arr[*start] == 0) {
        (*start)++;
    }
    *end = size - 1;
    while (*end >= 0 && arr[*end] == 0) {
        (*end)--;
    }
}

static int rectangle(picture pic, int size, int *x1, int *y1, int *x2, int *y2)
{
    int exists, i, j;
    char *strs, *cols;

    strs = calloc(size, sizeof(*strs));
    cols = calloc(size, sizeof(*cols));

    exists = 0;
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            if (pic[i][j] == '1') {
                strs[i] = 1;
                cols[j] = 1;
                exists = 1;
            }
        }
    }
    if (exists) {
        strip(cols, size, x1, x2);
        strip(strs, size, y1, y2);
    }
    free(strs);
    free(cols);
    return exists;
}

static int picture_recognize(picture pic, int size,
        struct point *p1, struct point *p2)
{
    int s, i, j, exists, x1, y1, x2, y2;

    exists = rectangle(pic, size, &x1, &y1, &x2, &y2);
    if (!exists) {
        return 0;
    }

    s = y2 - y1 + 1;
    for (i = y1; i <= y2; i++) {
        for (j = x1; j < x2; j++) {
            if (i - y1 > s / 2 && j == x1 + i - y1 - s / 2 - 1) {
                if (pic[i][j] != '1') {
                    return 0;
                }
            } else if (pic[i][j] != '0') {
                return 0;
            }
        }

        if (pic[i][x2] != '1') {
            return 0;
        }
    }
    p1->x = x1;
    p1->y = y1;

    p2->x = x2;
    p2->y = y2;
    return 1;
}

static void picture_del(picture pic, int size)
{
    int i;
    for (i = 0; i < size; i++) {
        free(pic[i]);
    }
}

int main(int argc, char **argv)
{
    int size, exists;
    picture pic;
    struct point p1, p2;

    if (argc != 2) {
        fprintf(stderr, "Expected: %s <size>\n", argv[0]);
        return 1;
    }
    size = atoi(argv[1]);

    srand(time(NULL));

    pic = picture_init(size);

    picture_print(pic, size);

    exists = picture_recognize(pic, size, &p1, &p2);
    if (exists) {
        printf("%d %d %d %d\n", p1.x, p1.y, p2.x, p2.y);
    } else {
        printf("The image is not found\n");
    }

    picture_del(pic, size);
    free(pic);
    return 0;
}
