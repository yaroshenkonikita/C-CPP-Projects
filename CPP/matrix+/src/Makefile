.PHONY: all clean test $(SOURCENAME).a

CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c++17 -lstdc++
TFLAGS = -lgtest
SOURCENAME = matrix_oop

ifeq ($(shell uname -s),Linux)
	CC = g++
endif


all: $(SOURCENAME).a test

$(SOURCENAME).a: $(SOURCENAME).h
	@$(CC) $(CFLAGS) -c $(SOURCENAME).cpp
	@ar rc $(SOURCENAME).a $(SOURCENAME).o
	@ranlib $(SOURCENAME).a
	@rm $(SOURCENAME).o


test: $(SOURCENAME).cpp test.cpp $(SOURCENAME).h
	@$(CC) $(CFLAGS) $(SOURCENAME).cpp test.cpp -o test $(TFLAGS)
	@./test


clean:
	@-rm -rf *.o *.a test

style:
	@clang-format -style=google -n matrix_oop.cpp matrix_oop.h test.cpp
	@clang-format -style=google -i matrix_oop.cpp matrix_oop.h test.cpp
