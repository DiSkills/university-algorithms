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

static void picture_print(picture pic, int size)
{
    int i;
    for (i = 0; i < size; i++) {
        int j;
        for (j = 0; j < size; j++) {
            printf("%c%c", pic[i][j], j != size - 1 ? ' ' : '\n');
        }
    }
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
    int size;
    picture pic;

    if (argc != 2) {
        fprintf(stderr, "Expected: %s <size>\n", argv[0]);
        return 1;
    }
    size = atoi(argv[1]);

    srand(time(NULL));

    pic = picture_init(size);
    picture_print(pic, size);
    picture_del(pic, size);
    free(pic);
    return 0;
}
