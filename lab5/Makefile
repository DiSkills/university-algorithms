SRCMODULES = number.c number_add.c number_sub.c number_compare.c number_shift.c
OBJMODULES = $(SRCMODULES:.c=.o)

CC = gcc
CFLAGS = -ggdb -Wall

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@

prog: main.c $(OBJMODULES)
	$(CC) $(CFLAGS) $^ -o $@

add: main.c $(OBJMODULES)
	$(CC) $(CFLAGS) $^ -o $@ -DADD

sub: main.c $(OBJMODULES)
	$(CC) $(CFLAGS) $^ -o $@ -DSUB

shl: main.c $(OBJMODULES)
	$(CC) $(CFLAGS) $^ -o $@ -DSHL

ifneq (clean, $(MAKECMDGOALS))
-include deps.mk
endif

deps.mk: $(SRCMODULES)
	$(CC) -MM $^ > $@

clean:
	rm -rf prog *.o deps.mk add sub shl
