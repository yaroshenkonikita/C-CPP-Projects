.PHONY: all clean test $(SOURCENAME).a

CC = g++
CFLAGS = -Wall -Werror -Wextra -std=c++17
TFLAGS = -lgtest -lgtest_main
SOURCENAME = matrix_oop

all: $(SOURCENAME).a test

$(SOURCENAME).a: $(SOURCENAME).h
	@$(CC) $(CFLAGS) -c $(SOURCENAME).cc
	@ar rc $(SOURCENAME).a $(SOURCENAME).o
	@ranlib $(SOURCENAME).a
	@rm $(SOURCENAME).o


test: $(SOURCENAME).cc test.cc $(SOURCENAME).h
	@$(CC) $(CFLAGS) $(SOURCENAME).cc test.cc -o test $(TFLAGS)
	@./test


clean:
	@-rm -rf *.o *.a test

style:
	@clang-format -style=google -n matrix_oop.cc matrix_oop.h test.cc
	@clang-format -style=google -i matrix_oop.cc matrix_oop.h test.cc
