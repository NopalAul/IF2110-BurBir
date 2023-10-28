CC = gcc
CFLAGS = -Wall -Werror -std=c17

SRC_DRIVER = main.c
OBJ_DRIVER = $(SRC_DRIVER:.c=.o)

SRC_CHARM = lib/charmachine/charmachine.c
OBJ_CHARM = $(SRC_CHARM:.c=.o)

SRC_WORD = lib/wordmachine/wordmachine.c
OBJ_WORD = $(SRC_WORD:.c=.o)

SRC_USER = lib/user/user.c
OBJ_USER = $(SRC_USER:.c=.o)

SRC_PCOLOR = lib/pcolor/pcolor.c
OBJ_PCOLOR = $(SRC_PCOLOR:.c=.o)

.PHONY: main clean

main : $(OBJ_DRIVER) $(OBJ_WORD) $(OBJ_CHARM) $(OBJ_USER) $(OBJ_PCOLOR)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f main $(OBJ_DRIVER) $(OBJ_WORD) $(OBJ_CHARM) $(OBJ_USER) $(OBJ_PCOLOR)