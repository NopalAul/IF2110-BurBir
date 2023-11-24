CC = gcc
CFLAGS = -Wall -Werror -std=c17

SRC_DIR = lib
SRC_MAIN = main.c

# Find all directories in SRC_DIR
DIRECTORIES = $(wildcard $(SRC_DIR)/*)

# Filter source files that have the same name as their parent folders
SRCS = $(foreach dir,$(DIRECTORIES),$(wildcard $(dir)/$(notdir $(dir)).c))
OBJS = $(SRCS:.c=.o)

.PHONY: run all_clean

run: main
	@./$^

main: $(SRC_MAIN) $(OBJS)
	@$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	@$(CC) $(CFLAGS) -c -o $@ $<

clean:
	@rm -f main $(OBJS) word_test $(OBJ_WORD_TEST)


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


all : main 

test_all: test_balasan test_charm test_datetime test_draft test_kicauan test_matrix test_relation test_req test_user test_utas test_word

all_clean: clean_balasan clean_charm clean_datetime clean_draft clean_kicauan clean_matrix clean_relation clean_req clean_user clean_utas clean_word
	@rm -f $(OBJS) main

word_test : $(OBJ_WORD_TEST) $(OBJ_WORD) $(OBJ_CHARM) #masukkan semua OBJECT file yang diperlukan untuk test ini
	@$(CC) $(CFLAGS) -o $@ $^

test_word : word_test $(TEST_WORD_RESULTS)
	@cat $(TEST_WORD_RESULTS)


$(TEST_WORD_RESULTS): $(TEST_WORD_DIR)/%.result: $(TEST_WORD_DIR)/%.in $(TEST_WORD_DIR)/%.out word_test
	@if ./word_test < $< | diff -Z -B - $(word 2,$^) > /dev/null; then \
		echo "$< $(word 2, $^): TRUE"; \
	else \
		echo "$< $(word 2, $^): WRONG"; \
	fi > $@

clean_word:
	@rm -f word_test $(OBJ_WORD_TEST) $(OBJ_WORD) $(OBJ_CHARM)

# MATRIKS UNIT TEST
SRC_MATRIX = lib/matrix/matrix.c
OBJ_MATRIX = $(SRC_MATRIX:.c=.o)

SRC_MATRIX_TEST = lib/matrix/test/matrix_test.c

TEST_MATRIX_DIR = lib/matrix/test
TEST_MATRIX_CASES = $(wildcard $(TEST_MATRIX_DIR)/*.in)
TEST_MATRIX_OUPUTS = $(TEST_MATRIX_CASES:.in=.out)
TEST_MATRIX_RESULTS = $(TEST_MATRIX_CASES:.in=.result)


matrix_test : $(SRC_MATRIX_TEST) $(SRC_MATRIX)
	@$(CC) $(CFLAGS) -o $@ $^

test_matrix : matrix_test $(TEST_MATRIX_RESULTS)
	@cat $(TEST_MATRIX_RESULTS)

$(TEST_MATRIX_RESULTS) : $(TEST_MATRIX_DIR)/%.result: $(TEST_MATRIX_DIR)/%.in $(TEST_MATRIX_DIR)/%.out matrix_test
	@if ./matrix_test < $< | diff -Z -B - $(word 2,$^) > /dev/null; then \
		echo "$< $(word 2, $^): TRUE"; \
	else \
		echo "$< $(word 2, $^): WRONG"; \
	fi > $@

clean_matrix:
	@rm -f matrix_test $(OBJ_MATRIX_TEST) $(OBJ_MATRIX)

#KICAUAN UNIT TEST
SRC_KICAUAN = lib/kicauan/kicauan.c
OBJ_KICAUAN = $(SRC_KICAUAN:.c=.o)

SRC_CHARM = lib/charmachine/charmachine.c
OBJ_CHARM = $(SRC_CHARM:.c=.o)

SRC_DRAFT = lib/draft/draft.c
OBJ_DRAFT = $(SRC_DRAFT:.c=.o)

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
	@$(CC) $(CFLAGS) -o $@ $^

test_kicauan : kicauan_test $(TEST_KICAUAN_RESULTS)
	@cat $(TEST_KICAUAN_RESULTS)


$(TEST_KICAUAN_RESULTS): $(TEST_KICAUAN_DIR)/%.result: $(TEST_KICAUAN_DIR)/%.in $(TEST_KICAUAN_DIR)/%.out kicauan_test
	@if ./kicauan_test < $< | diff -Z -B - $(word 2,$^) > /dev/null; then \
		echo "$< $(word 2, $^): TRUE"; \
	else \
		echo "$< $(word 2, $^): WRONG"; \
	fi > $@

clean_kicauan:
	@rm -f kicauan_test $(OBJ_KICAUAN_TEST) $(OBJ_WORD) $(OBJ_CHARM) $(OBJ_KICAUAN) $(OBJ_UTAS) $(OBJ_BALASAN) $(OBJ_RELATION) $(OBJ_DATETIME) $(OBJ_USER) $(OBJ_REQUEST) $(OBJ_PCOLOR)

# BALASAN UNIT TEST

TEST_BALASAN_DIR = lib/reply/test
TEST_BALASAN_CASES = $(wildcard $(TEST_BALASAN_DIR)/*.in)
TEST_BALASAN_OUTPUTS = $(TEST_BALASAN_CASES:.in=.out)
TEST_BALASAN_RESULTS = $(TEST_BALASAN_CASES:.in=.result)

SRC_BALASAN_TEST = lib/reply/test/replytest.c
OBJ_BALASAN_TEST = $(SRC_BALASAN_TEST:.c=.o)

balasan_test : $(OBJ_BALASAN_TEST) $(OBJ_WORD) $(OBJ_CHARM) $(OBJ_KICAUAN) $(OBJ_UTAS) $(OBJ_BALASAN) $(OBJ_RELATION) $(OBJ_DATETIME) $(OBJ_USER) $(OBJ_REQUEST) $(OBJ_PCOLOR)
	@$(CC) $(CFLAGS) -o $@ $^

test_balasan : balasan_test $(TEST_BALASAN_RESULTS)
	@cat $(TEST_BALASAN_RESULTS)

$(TEST_BALASAN_RESULTS): $(TEST_BALASAN_DIR)/%.result: $(TEST_BALASAN_DIR)/%.in $(TEST_BALASAN_DIR)/%.out balasan_test
	@if ./balasan_test < $< | diff -Z -B - $(word 2,$^) > /dev/null; then \
		echo "$< $(word 2, $^): TRUE"; \
	else \
		echo "$< $(word 2, $^): WRONG"; \
	fi > $@

clean_balasan:
	@rm -f balasan_test $(OBJ_BALASAN_TEST) $(OBJ_WORD) $(OBJ_CHARM) $(OBJ_KICAUAN) $(OBJ_UTAS) $(OBJ_BALASAN) $(OBJ_RELATION) $(OBJ_DATETIME) $(OBJ_USER) $(OBJ_REQUEST) $(OBJ_PCOLOR)

# UTAS UNIT TEST
TEST_UTAS_DIR = lib/utas/test
TEST_UTAS_CASES = $(wildcard $(TEST_UTAS_DIR)/*.in)
TEST_UTAS_OUTPUTS = $(TEST_UTAS_CASES:.in=.out)
TEST_UTAS_RESULTS = $(TEST_UTAS_CASES:.in=.result)

SRC_UTAS_TEST = lib/utas/test/utastest.c
OBJ_UTAS_TEST = $(SRC_UTAS_TEST:.c=.o)

utas_test : $(OBJ_UTAS_TEST) $(OBJ_WORD) $(OBJ_CHARM) $(OBJ_KICAUAN) $(OBJ_UTAS) $(OBJ_BALASAN) $(OBJ_RELATION) $(OBJ_DATETIME) $(OBJ_USER) $(OBJ_REQUEST) $(OBJ_PCOLOR)
	@$(CC) $(CFLAGS) -o $@ $^

test_utas : utas_test $(TEST_UTAS_RESULTS)
	@cat $(TEST_UTAS_RESULTS)

$(TEST_UTAS_RESULTS): $(TEST_UTAS_DIR)/%.result: $(TEST_UTAS_DIR)/%.in $(TEST_UTAS_DIR)/%.out utas_test
	@if ./utas_test < $< | diff -Z -B - $(word 2,$^) > /dev/null; then \
		echo "$< $(word 2, $^): TRUE"; \
	else \
		echo "$< $(word 2, $^): WRONG"; \
	fi > $@

clean_utas:
	@rm -f utas_test $(OBJ_UTAS_TEST) $(OBJ_WORD) $(OBJ_CHARM) $(OBJ_KICAUAN) $(OBJ_UTAS) $(OBJ_BALASAN) $(OBJ_RELATION) $(OBJ_DATETIME) $(OBJ_USER) $(OBJ_REQUEST) $(OBJ_PCOLOR)

# DRAFT UNIT TEST
TEST_DRAFT_DIR = lib/draft/test
TEST_DRAFT_CASES = $(wildcard $(TEST_DRAFT_DIR)/*.in)
TEST_DRAFT_OUTPUTS = $(TEST_DRAFT_CASES:.in=.out)
TEST_DRAFT_RESULTS = $(TEST_DRAFT_CASES:.in=.result)

SRC_DRAFT_TEST = lib/draft/test/draft_test.c
OBJ_DRAFT_TEST = $(SRC_DRAFT_TEST:.c=.o)

draft_test : $(OBJ_DRAFT_TEST) $(OBJ_WORD) $(OBJ_CHARM) $(OBJ_KICAUAN) $(OBJ_UTAS) $(OBJ_BALASAN) $(OBJ_RELATION) $(OBJ_DATETIME) $(OBJ_USER) $(OBJ_REQUEST) $(OBJ_PCOLOR) $(OBJ_DRAFT)
	@$(CC) $(CFLAGS) -o $@ $^

test_draft : draft_test $(TEST_DRAFT_RESULTS)
	@cat $(TEST_DRAFT_RESULTS)

$(TEST_DRAFT_RESULTS): $(TEST_DRAFT_DIR)/%.result: $(TEST_DRAFT_DIR)/%.in $(TEST_DRAFT_DIR)/%.out draft_test
	@if ./draft_test < $< | diff -Z -B - $(word 2,$^) > /dev/null; then \
		echo "$< $(word 2, $^): TRUE"; \
	else \
		echo "$< $(word 2, $^): WRONG"; \
	fi > $@

clean_draft:
	@rm -f draft_test $(OBJ_DRAFT_TEST) $(OBJ_WORD) $(OBJ_CHARM) $(OBJ_KICAUAN) $(OBJ_UTAS) $(OBJ_BALASAN) $(OBJ_RELATION) $(OBJ_DATETIME) $(OBJ_USER) $(OBJ_REQUEST) $(OBJ_PCOLOR) $(OBJ_DRAFT)

# DATETIME UNIT TEST

TEST_DATETIME_DIR = lib/datetime/test
TEST_DATETIME_CASES = $(wildcard $(TEST_DATETIME_DIR)/*.in)
TEST_DATETIME_OUTPUTS = $(TEST_DATETIME_CASES:.in=.out)
TEST_DATETIME_RESULTS = $(TEST_DATETIME_CASES:.in=.result)

SRC_DATETIME_TEST = lib/datetime/test/datetime_test.c
OBJ_DATETIME_TEST = $(SRC_DATETIME_TEST:.c=.o)

datetime_test : $(OBJ_DATETIME_TEST) $(OBJ_DATETIME)
	@$(CC) $(CFLAGS) -o $@ $^

test_datetime : datetime_test $(TEST_DATETIME_RESULTS)
	@cat $(TEST_DATETIME_RESULTS)

$(TEST_DATETIME_RESULTS): $(TEST_DATETIME_DIR)/%.result: $(TEST_DATETIME_DIR)/%.in $(TEST_DATETIME_DIR)/%.out datetime_test
	@if ./datetime_test < $< | diff -Z -B - $(word 2,$^) > /dev/null; then \
		echo "$< $(word 2, $^): TRUE"; \
	else \
		echo "$< $(word 2, $^): WRONG"; \
	fi > $@

clean_datetime:
	@rm -f datetime_test $(OBJ_DATETIME_TEST) $(OBJ_DATETIME)

#CHARMACHINE UNIT TEST
SRC_CHARM_TEST = lib/charmachine/test/char_test.c
OBJ_CHARM_TEST = $(SRC_CHARM_TEST:.c=.o)

TEST_CHARM_DIR = lib/charmachine/test
TEST_CHARM_CASES = $(wildcard $(TEST_CHARM_DIR)/*.in)
TEST_CHARM_OUTPUTS = $(TEST_CHARM_CASES:.in=.out)
TEST_CHARM_RESULTS = $(TEST_CHARM_CASES:.in=.result)

clean_charm:
	@rm -f charm_test $(OBJ_CHARM_TEST) $(OBJ_CHARM)

charm_test: $(OBJ_CHARM_TEST) $(OBJ_CHARM)
	@$(CC) $(CFLAGS) -o $@ $^

test_charm: charm_test $(TEST_CHARM_RESULTS)
	@cat $(TEST_CHARM_RESULTS)

$(TEST_CHARM_RESULTS): $(TEST_CHARM_DIR)/%.result: $(TEST_CHARM_DIR)/%.in $(TEST_CHARM_DIR)/%.out charm_test
	@if ./charm_test < $< | diff -Z -B - $(word 2,$^) > /dev/null; then \
		echo "$< $(word 2, $^): TRUE"; \
	else \
		echo "$< $(word 2, $^): WRONG"; \
	fi > $@


#RELATION UNIT TEST
SRC_RELATION_TEST = lib/relation/test/relation_test.c
OBJ_RELATION_TEST = $(SRC_RELATION_TEST:.c=.o)


TEST_RELATION_DIR = lib/relation/test
TEST_RELATION_CASES = $(wildcard $(TEST_RELATION_DIR)/*.in)
TEST_RELATION_RESULTS = $(TEST_RELATION_CASES:.in=.result)

clean_relation:
	@rm -f relation_test $(OBJ_RELATION_TEST) $(OBJ_RELATION)

relation_test: $(OBJ_RELATION_TEST) $(OBJ_RELATION)
	@$(CC) $(CFLAGS) -o $@ $^

test_relation: relation_test $(TEST_RELATION_RESULTS)
	@cat $(TEST_RELATION_RESULTS)

$(TEST_RELATION_RESULTS): $(TEST_RELATION_DIR)/%.result: $(TEST_RELATION_DIR)/%.in $(TEST_RELATION_DIR)/%.out relation_test
	@if ./relation_test < $< | diff -Z -B - $(word 2,$^) > /dev/null; then \
		echo "$< $(word 2, $^): TRUE"; \
	else \
		echo "$< $(word 2, $^): WRONG"; \
	fi > $@


#ListRequest UNIT TEST
SRC_REQ_TEST = lib/listRequest/test/req_test.c
OBJ_REQ_TEST = $(SRC_REQ_TEST:.c=.o)

TEST_REQ_DIR = lib/listRequest/test
TEST_REQ_CASES = $(wildcard $(TEST_REQ_DIR)/*.in)
TEST_REQ_RESULTS = $(TEST_REQ_CASES:.in=.result)

clean_req:
	@rm -f req_test $(OBJ_REQ_TEST) $(OBJ_REQUEST) $(OBJ_RELATION)

req_test: $(OBJ_REQ_TEST) $(OBJ_REQUEST) $(OBJ_RELATION)
	@$(CC) $(CFLAGS) -o $@ $^

test_req: req_test $(TEST_REQ_RESULTS)
	@cat $(TEST_REQ_RESULTS)

$(TEST_REQ_RESULTS): $(TEST_REQ_DIR)/%.result: $(TEST_REQ_DIR)/%.in $(TEST_REQ_DIR)/%.out req_test
	@if ./req_test < $< | diff -Z -B - $(word 2,$^) > /dev/null; then \
		echo "$< $(word 2, $^): TRUE"; \
	else \
		echo "$< $(word 2, $^): WRONG"; \
	fi > $@

#USER UNIT TEST
SRC_USER_TEST = lib/user/test/user_test.c
OBJ_USER_TEST = $(SRC_USER_TEST:.c=.o)

TEST_USER_DIR = lib/user/test
TEST_USER_CASES = $(wildcard $(TEST_USER_DIR)/*.in)
TEST_USER_RESULTS = $(TEST_USER_CASES:.in=.result)

clean_user:
	@rm -f user_test $(OBJ_USER_TEST) $(OBJ_USER) $(OBJ_MATRIX) $(OBJ_WORD) $(OBJ_CHARM) $(OBJ_PCOLOR) $(OBJ_REQUEST) $(OBJ_RELATION)

user_test: $(OBJ_USER_TEST) $(OBJ_USER) $(OBJ_MATRIX) $(OBJ_WORD) $(OBJ_CHARM) $(OBJ_PCOLOR) $(OBJ_REQUEST) $(OBJ_RELATION)
	@$(CC) $(CFLAGS) -o $@ $^

test_user: user_test $(TEST_USER_RESULTS)
	@cat $(TEST_USER_RESULTS)

$(TEST_USER_RESULTS): $(TEST_USER_DIR)/%.result: $(TEST_USER_DIR)/%.in $(TEST_USER_DIR)/%.out user_test
	@if ./user_test < $< | diff -Z -B - $(word 2,$^) > /dev/null; then \
		echo "$< $(word 2, $^): TRUE"; \
	else \
		echo "$< $(word 2, $^): WRONG"; \
	fi > $@