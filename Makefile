CC = gcc
CFLAGS = -Wall -Werror -std=c17

SRC_DRIVER = main.c
OBJ_DRIVER = $(SRC_DRIVER:.c=.o)

SRC_CHARM = lib/charmachine/charmachine.c
OBJ_CHARM = $(SRC_CHARM:.c=.o)

SRC_WORD = lib/wordmachine/wordmachine.c
OBJ_WORD = $(SRC_WORD:.c=.o)

.PHONY: driver clean

main : $(OBJ_DRIVER) $(OBJ_WORD) $(OBJ_CHARM)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f main $(OBJ_DRIVER) $(OBJ_WORD) $(OBJ_CHARM)