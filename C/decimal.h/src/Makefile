# =========================================== VAR ==================================================
CC := gcc
CFLAGS := -Wall -Wextra -Werror -std=c11
GCOVFLAGS := -fprofile-arcs -ftest-coverage
HEADER := decimal.h
TESTS := test
SOURCES_ALL := $(wildcard *.c -I decimal/*/*.c)
SOURCES_FUN := $(shell find decimal/*/ -name "*.c" 2> /dev/null)
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

all: decimal.a

check:
	@checkmk clean_mode=1 decimal_test.check > decimal_test.c

%.o: %.c $(HEADER)
	@$(CC) $(CFLAGS) -c $< -o $@

test: check $(OBJ_LIBRARY)
	@$(CC) $(CFLAGS) $(OBJ_LIBRARY) decimal_test.c -o $(TESTS) $(LDFLAGS)
	@rm -rf decimal/*/*.o
	@./$(TESTS)

decimal.a: $(OBJ_LIBRARY) $(HEADER)
	@ar rcs decimal.a $(OBJ_LIBRARY)
	@rm -rf decimal/*/*.o
	@ranlib decimal.a

gcov_report: check
	@$(CC) $(GCOVFLAGS) $(SOURCES_FUN) decimal_test.c $(LDFLAGS) -o report.out
	@./report.out
	@-gcov -f $(SOURCES_FUN)
	@lcov -t "gcov_report" -o Coverage_Report.info -c -d ./
	@-lcov -r Coverage_Report.info '*/decimal_test.c' -o Coverage_Report.info
	@genhtml -o ./report Coverage_Report.info
	@rm -rf *.o *.a *.gcno *.gcda *.info *.out *.gcov decimal/*/*.o
	@$(OPEN_CM) ./report/index-sort-f.html

rebuild: clean all

clean:
	@rm -rf decimal/*/*.o *.a *.gcno *.gcda *.info *.out *.gcov test decimal_test.c report

# ========================================== STYLE =================================================

style:
	@clang-format -n decimal/*/*.c *.h

correctoin_style:
	@clang-format -i decimal/*/*.c *.h