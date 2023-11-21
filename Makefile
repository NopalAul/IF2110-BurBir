CC = gcc
CFLAGS = -Wall -Werror -std=c17

SRC_DRIVER = main.c
OBJ_DRIVER = $(SRC_DRIVER:.c=.o)

SRC_CHARM = lib/charmachine/charmachine.c
OBJ_CHARM = $(SRC_CHARM:.c=.o)

SRC_WORD = lib/wordmachine/wordmachine.c
OBJ_WORD = $(SRC_WORD:.c=.o)

#UNIT TEST of WORDMACHINE
SRC_WORD_TEST = lib/wordmachine/test/wordtest.c
OBJ_WORD_TEST = $(SRC_WORD_TEST:.c=.o)

TEST_WORD_DIR = lib/wordmachine/test
TEST_WORD_CASES = $(wildcard $(TEST_WORD_DIR)/*.in)
TEST_WORD_OUTPUTS = $(TEST_WORD_CASES:.in=.out)
TEST_WORD_RESULTS = $(TEST_WORD_CASES:.in=.result)
TEMP_STDOUT_FILES = $(addprefix temp_stdout_,$(notdir $(TEST_WORD_CASES:.in=.txt)))


all : main word_test

word_test : $(OBJ_WORD_TEST) $(OBJ_WORD) $(OBJ_CHARM) #masukkan semua OBJECT file yang diperlukan untuk test ini
	$(CC) $(CFLAGS) -o $@ $^

test_word : word_test $(TEST_WORD_RESULTS)
	@cat $(TEST_WORD_RESULTS)


$(TEST_WORD_RESULTS): $(TEST_WORD_DIR)/%.result: $(TEST_WORD_DIR)/%.in $(TEST_WORD_DIR)/%.out word_test
	@if ./word_test < $< | diff -Z -B - $(word 2,$^) > /dev/null; then \
		echo "$< $(word 2, $^): TRUE"; \
	else \
		echo "$< $(word 2, $^): WRONG"; \
	fi > $@

create_stdout: $(TEMP_STDOUT_FILES)

$(TEMP_STDOUT_FILES): temp_stdout_%.txt: $(TEST_WORD_DIR)/%.in word_test
	@./word_test < $(word 1,$^) | tr '\r' '\n' > $@

# MATRIKS UNIT TEST
SRC_MATRIX = lib/matrix/matrix.c
OBJ_MATRIX = $(SRC_MATRIX:.c=.o)

SRC_MATRIX_TEST = lib/matrix/test/matrix_test.c

TEST_MATRIX_DIR = lib/matrix/test
TEST_MATRIX_CASES = $(wildcard $(TEST_MATRIX_DIR)/*.in)
TEST_MATRIX_OUPUTS = $(TEST_MATRIX_CASES:.in=.out)
TEST_MATRIX_RESULTS = $(TEST_MATRIX_CASES:.in=.result)


matrix_test : $(SRC_MATRIX_TEST) $(SRC_MATRIX)
	$(CC) $(CFLAGS) -o $@ $^

test_matrix : matrix_test $(TEST_MATRIX_RESULTS)
	@cat $(TEST_MATRIX_RESULTS)

$(TEST_MATRIX_RESULTS) : $(TEST_MATRIX_DIR)/%.result: $(TEST_MATRIX_DIR)/%.in $(TEST_MATRIX_DIR)/%.out matrix_test
	@if ./matrix_test < $< | diff -Z - $(word 2,$^) > /dev/null; then \
		echo "$< $(word 2, $^): TRUE"; \
	else \
		echo "$< $(word 2, $^): WRONG"; \
	fi > $@

%.clear : %
	rm -f $*


SRC_USER = lib/user/user.c
OBJ_USER = $(SRC_USER:.c=.o)

SRC_PCOLOR = lib/pcolor/pcolor.c
OBJ_PCOLOR = $(SRC_PCOLOR:.c=.o)

SRC_RELATION = lib/relation/relation.c
OBJ_RELATION = $(SRC_RELATION:.c=.o)

.PHONY: main clean word_test test_word

main : $(OBJ_DRIVER) $(OBJ_WORD) $(OBJ_CHARM) $(OBJ_USER) $(OBJ_PCOLOR) $(OBJ_RELATION)
SRC_KICAUAN = lib/kicauan/kicauan.c
OBJ_KICAUAN = $(SRC_KICAUAN:.c=.o)

SRC_DATETIME = lib/datetime/datetime.c
OBJ_DATETIME = $(SRC_DATETIME:.c=.o)

.PHONY: main clean

main : $(OBJ_DRIVER) $(OBJ_WORD) $(OBJ_CHARM) $(OBJ_USER) $(OBJ_PCOLOR) $(OBJ_KICAUAN) $(OBJ_DATETIME) $(OBJ_RELATION) $(OBJ_MATRIX)
	$(CC) $(CFLAGS) -o $@ $^

#%.run : %
#	./$*

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f main $(OBJ_DRIVER) $(OBJ_WORD) $(OBJ_CHARM) $(OBJ_USER) $(OBJ_PCOLOR) $(OBJ_WORD_TEST) word_test $(OBJ_RELATION) $(OBJ_KICAUAN) $(OBJ_DATETIME) $(OBJ_RELATION) $(OBJ_MATRIX)
