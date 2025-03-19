SRCMODULES = hash_table.c
OBJMODULES = $(SRCMODULES:.c=.o)

CC = gcc
CFLAGS = -ggdb -Wall
CPPFLAGS =

ifeq (random, $(MAKECMDGOALS))
    CPPFLAGS += -DRANDOM_REHASHING
endif

%.o: %.c %.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

prog: main.c $(OBJMODULES)
	$(CC) $(CFLAGS) $(CPPFLAGS) $^ -o $@

random: main.c $(OBJMODULES)
	$(CC) $(CFLAGS) $(CPPFLAGS) $^ -o $@

ifneq (clean, $(MAKECMDGOALS))
-include deps.mk
endif

deps.mk: $(SRCMODULES)
	$(CC) -MM $^ > $@

clean:
	rm -rf prog random *.o deps.mk
