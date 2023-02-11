# =========================================== VAR ==================================================
CC := gcc
CFLAGS := -Wall -Wextra -Werror -std=c11
GCOVFLAGS := -fprofile-arcs -ftest-coverage
HEADER := matrix.h
TESTS := test
SOURCES_ALL := $(wildcard *.c -I matrix/*.c)
SOURCES_FUN := $(shell find matrix/ -name "*.c" 2> /dev/null)
OBJECTS := $(patsubst %.c,%.o,$(SOURCES_ALL))
OBJ_LIBRARY := $(patsubst %.c,%.o,$(SOURCES_FUN))
UNAME := $(shell uname -s)

# =========================================== OS ===================================================
ifeq ($(UNAME),Linux)
	LDFLAGS=-lcheck -lm -lrt -lpthread -lsubunit
	OPEN_CM=xdg-open
endif
ifeq ($(UNAME),Darwin)
	LDFLAGS=-lcheck
	OPEN_CM=open
endif

# ========================================= TARGETS ================================================

all: matrix.a gcov_report

check:
	@checkmk clean_mode=1 matrix_test.check > matrix_test.c

%.o: %.c $(HEADER)
	@$(CC) $(CFLAGS) -c $< -o $@

test: check $(OBJ_LIBRARY)
	$(CC) $(CFLAGS) $(OBJ_LIBRARY) matrix_test.c -o $(TESTS) $(LDFLAGS)
	@rm -rf matrix/*.o
	@./$(TESTS)

matrix.a: $(OBJ_LIBRARY) $(HEADER)
	@ar rcs matrix.a $(OBJ_LIBRARY)
	@rm -rf matrix/*.o
	@ranlib matrix.a

gcov_report: check
	@$(CC) $(GCOVFLAGS) $(SOURCES_FUN) matrix_test.c $(LDFLAGS) -o report.out
	@./report.out
	@-gcov -f $(SOURCES_FUN)
	@lcov -t "gcov_report" -o Coverage_Report.info -c -d ./
	@-lcov -r Coverage_Report.info '*/matrix_test.c' -o Coverage_Report.info
	@genhtml -o ./report Coverage_Report.info
	@rm -rf *.o *.gcno *.gcda *.info *.out *.gcov matrix/*.o
	@$(OPEN_CM) ./report/index-sort-f.html

rebuild: clean all

clean:
	@rm -rf matrix/*.o *.a *.gcno *.gcda *.info *.out *.gcov test matrix_test.c report

# ========================================== STYLE =================================================

style:
	@clang-format -n matrix/*.c

correctoin_style:
	@clang-format -i matrix/*.c
