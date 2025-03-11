#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef char **picture;

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

static int strip(char *arr, int size, int *start, int *end)
{
    int counter = 0;

    *start = 0; counter++;
    while (*start < size && arr[*start] == 0) { counter += 2;
        (*start)++; counter++;
    } counter += (*start < size) ? 2 : 1;

    *end = size - 1; counter += 2;
    while (*end >= 0 && arr[*end] == 0) { counter += 2;
        (*end)--; counter++;
    } counter += (*end >= 0) ? 2 : 1;

    return counter;
}

static int rectangle(picture pic, int size,
        int *x1, int *y1, int *x2, int *y2, int *pcounter)
{
    int counter = 0;
    int exists, i, j;
    char *strs, *cols;

    strs = calloc(size, sizeof(*strs)); counter += size;
    cols = calloc(size, sizeof(*cols)); counter += size;

    exists = 0; counter++;
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            if (pic[i][j] == '1') {
                strs[i] = 1; counter++;
                cols[j] = 1; counter++;
                exists = 1; counter++;
            } counter++;
        }
    }
    if (exists) {
        counter += strip(cols, size, x1, x2);
        counter += strip(strs, size, y1, y2);
    } counter++;
    free(strs);
    free(cols);
    *pcounter += counter;
    return exists;
}

static int picture_recognize(picture pic, int size, int *pcounter)
{
    int counter = 0;
    int s, i, j, exists, x1, y1, x2, y2;

    exists = rectangle(pic, size, &x1, &y1, &x2, &y2, pcounter);
    if (!exists) {
        return 0;
    }

    s = y2 - y1 + 1; counter += 3;
    for (i = y1; i <= y2; i++) {
        for (j = x1; j < x2; j++) {
            counter += 10;
            if (i - y1 > s / 2 && j == x1 + i - y1 - s / 2 - 1) {
                if (pic[i][j] != '1') {
                    return 0;
                }
            } else if (pic[i][j] != '0') {
                return 0;
            }
        }

        counter++;
        if (pic[i][x2] != '1') {
            return 0;
        }
    }
    *pcounter += counter;
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
    int counter = 0;
    int size;
    picture pic;

    if (argc != 2) {
        fprintf(stderr, "Expected: %s <size>\n", argv[0]);
        return 1;
    }
    size = atoi(argv[1]);

    srand(time(NULL));

    pic = picture_init(size);

    picture_recognize(pic, size, &counter);
    printf("%d\n", counter);

    picture_del(pic, size);
    free(pic);
    return 0;
}
