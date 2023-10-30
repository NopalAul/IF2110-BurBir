CC = gcc
CFLAGS = -Wall -Werror -std=c11

SRC_DRIVER = main.c
OBJ_DRIVER = $(SRC_DRIVER:.c=.o)

SRC_CHARM = lib/charmachine/charmachine.c
OBJ_CHARM = $(SRC_CHARM:.c=.o)

SRC_WORD = lib/wordmachine/wordmachine.c
OBJ_WORD = $(SRC_WORD:.c=.o)
SRC_WORD_TEST = lib/wordmachine/test/wordtest.c
OBJ_WORD_TEST = $(SRC_WORD_TEST:.c=.o)

TEST_WORD_DIR = lib/wordmachine/test
TEST_WORD_CASES = $(wildcard $(TEST_WORD_DIR)/*.in)
TEST_WORD_OUTPUTS = $(TEST_WORD_CASES:.in=.out)
TEST_WORD_RESULTS = $(TEST_WORD_CASES:.in=.result)

all : main word_test

word_test : $(OBJ_WORD_TEST) $(OBJ_WORD) $(OBJ_CHARM)
	$(CC) $(CFLAGS) -o $@ $^

test_word : word_test $(TEST_WORD_RESULTS)
	@cat $(TEST_WORD_RESULTS)

$(TEST_WORD_RESULTS): $(TEST_WORD_DIR)/%.result: $(TEST_WORD_DIR)/%.in $(TEST_WORD_DIR)/%.out word_test
	@if ./word_test < $< | diff -b - $(word 2,$^) > /dev/null; then \
		echo "$< $(word 2, $^): TRUE"; \
	else \
		echo "$< $(word 2, $^): WRONG"; \
	fi > $@

SRC_USER = lib/user/user.c
OBJ_USER = $(SRC_USER:.c=.o)

SRC_PCOLOR = lib/pcolor/pcolor.c
OBJ_PCOLOR = $(SRC_PCOLOR:.c=.o)

.PHONY: main clean word_test test_word

main : $(OBJ_DRIVER) $(OBJ_WORD) $(OBJ_CHARM) $(OBJ_USER) $(OBJ_PCOLOR)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f main $(OBJ_DRIVER) $(OBJ_WORD) $(OBJ_CHARM) $(OBJ_USER) $(OBJ_PCOLOR) $(OBJ_WORD_TEST) word_test


