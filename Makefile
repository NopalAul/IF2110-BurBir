CC = gcc
CFLAGS = -Wall -Werror -std=c17

SRC_DIR = lib
SRC_MAIN = main.c

# Find all directories in SRC_DIR
DIRECTORIES = $(wildcard $(SRC_DIR)/*)

# Filter source files that have the same name as their parent folders
SRCS = $(foreach dir,$(DIRECTORIES),$(wildcard $(dir)/$(notdir $(dir)).c))
OBJS = $(SRCS:.c=.o)

main: $(SRC_MAIN) $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f main $(OBJS) word_test $(OBJ_WORD_TEST)


# UNIT_TEST for WORD MACHINE
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


#CHARMACHINE UNIT TEST
SRC_WORD_TEST = lib/charmachine/test/.c
OBJ_WORD_TEST = $(SRC_WORD_TEST:.c=.o)

TEST_WORD_DIR = lib/wordmachine/test
TEST_WORD_CASES = $(wildcard $(TEST_WORD_DIR)/*.in)
TEST_WORD_OUTPUTS = $(TEST_WORD_CASES:.in=.out)
TEST_WORD_RESULTS = $(TEST_WORD_CASES:.in=.result)
TEMP_STDOUT_FILES = $(addprefix temp_stdout_,$(notdir $(TEST_WORD_CASES:.in=.txt)))
