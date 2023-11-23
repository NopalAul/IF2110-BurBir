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
	@if ./matrix_test < $< | diff -Z -B $(word 2,$^) > /dev/null; then \
		echo "$< $(word 2, $^): TRUE"; \
	else \
		echo "$< $(word 2, $^): WRONG"; \
	fi > $@


#KICAUAN UNIT TEST
SRC_KICAUAN = lib/kicauan/kicauan.c
OBJ_KICAUAN = $(SRC_KICAUAN:.c=.o)

SRC_CHARM = lib/charmachine/charmachine.c
OBJ_CHARM = $(SRC_CHARM:.c=.o)

SRC_BALASAN = lib/reply/reply.c
OBJ_BALASAN = $(SRC_BALASAN:.c=.o)

SRC_UTAS = lib/utas/utas.c
OBJ_UTAS = $(SRC_UTAS:.c=.o)

SRC_WORD = lib/wordmachine/wordmachine.c
OBJ_WORD = $(SRC_WORD:.c=.o)

SRC_RELATION = lib/relation/relation.c
OBJ_RELATION = $(SRC_RELATION:.c=.o)

SRC_DATETIME = lib/datetime/datetime.c
OBJ_DATETIME = $(SRC_DATETIME:.c=.o)


SRC_REQUEST = lib/listRequest/listRequest.c
OBJ_REQUEST = $(SRC_REQUEST:.c=.o)

SRC_USER = lib/user/user.c
OBJ_USER = $(SRC_USER:.c=.o)

SRC_PCOLOR = lib/pcolor/pcolor.c
OBJ_PCOLOR = $(SRC_PCOLOR:.c=.o)

SRC_KICAUAN_TEST = lib/kicauan/test/kicauantest.c
OBJ_KICAUAN_TEST = $(SRC_KICAUAN_TEST:.c=.o)

TEST_KICAUAN_DIR = lib/kicauan/test
TEST_KICAUAN_CASES = $(wildcard $(TEST_KICAUAN_DIR)/*.in)
TEST_KICAUAN_OUTPUTS = $(TEST_KICAUAN_CASES:.in=.out)
TEST_KICAUAN_RESULTS = $(TEST_KICAUAN_CASES:.in=.result)


kicauan_test : $(OBJ_KICAUAN_TEST) $(OBJ_WORD) $(OBJ_CHARM) $(OBJ_KICAUAN) $(OBJ_UTAS) $(OBJ_BALASAN) $(OBJ_RELATION) $(OBJ_DATETIME) $(OBJ_USER) $(OBJ_REQUEST) $(OBJ_PCOLOR)

 #masukkan semua OBJECT file yang diperlukan untuk test ini
	$(CC) $(CFLAGS) -o $@ $^

test_kicauan : kicauan_test $(TEST_KICAUAN_RESULTS)
	@cat $(TEST_KICAUAN_RESULTS)


$(TEST_KICAUAN_RESULTS): $(TEST_KICAUAN_DIR)/%.result: $(TEST_KICAUAN_DIR)/%.in $(TEST_KICAUAN_DIR)/%.out kicauan_test
	@if ./kicauan_test < $< | diff -Z -B - $(word 2,$^) > /dev/null; then \
		echo "$< $(word 2, $^): TRUE"; \
	else \
		echo "$< $(word 2, $^): WRONG"; \
	fi > $@

# BALASAN UNIT TEST

TEST_BALASAN_DIR = lib/reply/test
TEST_BALASAN_CASES = $(wildcard $(TEST_BALASAN_DIR)/*.in)
TEST_BALASAN_OUTPUTS = $(TEST_BALASAN_CASES:.in=.out)
TEST_BALASAN_RESULTS = $(TEST_BALASAN_CASES:.in=.result)

SRC_BALASAN_TEST = lib/reply/test/replytest.c
OBJ_BALASAN_TEST = $(SRC_BALASAN_TEST:.c=.o)

balasan_test : $(OBJ_BALASAN_TEST) $(OBJ_WORD) $(OBJ_CHARM) $(OBJ_KICAUAN) $(OBJ_UTAS) $(OBJ_BALASAN) $(OBJ_RELATION) $(OBJ_DATETIME) $(OBJ_USER) $(OBJ_REQUEST) $(OBJ_PCOLOR)
	$(CC) $(CFLAGS) -o $@ $^

test_balasan : balasan_test $(TEST_BALASAN_RESULTS)
	@cat $(TEST_BALASAN_RESULTS)

$(TEST_BALASAN_RESULTS): $(TEST_BALASAN_DIR)/%.result: $(TEST_BALASAN_DIR)/%.in $(TEST_BALASAN_DIR)/%.out balasan_test
	@if ./balasan_test < $< | diff -Z -B - $(word 2,$^) > /dev/null; then \
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
