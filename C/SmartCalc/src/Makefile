.PHONY: all install uninstall clean dvi dist test gcov_report s21_calc.a generate_make
# =========================================== VAR ==================================================
CC := gcc
CFLAGS := -Wall -Wextra -Werror -std=c11
GCOVFLAGS := -fprofile-arcs -ftest-coverage
HEADER := calc.h
TESTS := test
SOURCES_ALL := $(wildcard calc.c stack.c -I calc.c stack.c)
SOURCES_FUN := $(shell find . -name "calc.c stack.c" 2> /dev/null)
OBJECTS := $(patsubst %.c,%.o,$(SOURCES_ALL))
OBJ_LIBRARY := $(patsubst %.c,%.o,$(SOURCES_FUN))
UNAME := $(shell uname -s)

BUILD_DIR=build
QT_PROJECT_NAME = SmartCalc-C
QT_PROJECT_FOLDER = ./$(QT_PROJECT_NAME)
QT_PRO = $(QT_PROJECT_NAME).pro
QT_MAKEFILE = $(QT_PROJECT_NAME)_Makefile
QT_BUILD_FOLDER = build
QT_APP_FOLDER = app
TAR_DIR = SmartCalc_v1.0-0_Archive
SRC  := $(shell find . -name "s21*.c" | sed -e 's/\.\///')

# =========================================== OS ===================================================


ifeq ($(UNAME),Linux)
	LDFLAGS = -pthread -lcheck_pic -pthread -lrt -lm -lsubunit
	OPEN_CM = xdg-open
endif
ifeq ($(UNAME),Darwin)
	LDFLAGS = -lcheck
	OPEN_CM = open
endif


# ========================================= TARGETS ================================================


all: install gcov_report clean


generate_make:
	@qmake $(QT_PROJECT_FOLDER)/$(QT_PRO) -o ./$(QT_BUILD_FOLDER)/$(QT_MAKEFILE)


install: generate_make
	@echo "Building application..."
	@cd ./$(QT_BUILD_FOLDER) && make -sf $(QT_MAKEFILE)
	@echo "Application builded."
	@echo -n "Moving application to folder \"$(QT_APP_FOLDER)\"..."
	@mkdir ./$(QT_APP_FOLDER)
ifeq ($(OS), Darwin)
	@mv ./$(QT_BUILD_FOLDER)/$(QT_PROJECT_NAME).app/Contents/MacOS/SmartCalc ./$(QT_APP_FOLDER)/$(QT_PROJECT_NAME).app
else
	@mv ./$(QT_BUILD_FOLDER)/$(QT_PROJECT_NAME) ./$(QT_APP_FOLDER)/$(QT_PROJECT_NAME)
endif
	@echo "\nDone."
	@echo -n "Deleting build folder..."
	@rm -rf $(QT_BUILD_FOLDER)
	@echo "\nDone."
	@echo "Installation complete!"


uninstall:
	@echo -n "Uninstalling application..."
	@rm -rf $(QT_APP_FOLDER)
	@echo "\nDone."


dist: generate_make
	@rm -rf $(TAR_DIR) tar
	@mkdir $(TAR_DIR)
	@mkdir $(TAR_DIR)/src
	@mkdir tar
	@cp -r *.c *.h SmartCalc-C $(TAR_DIR)/src
	@tar cvzf $(TAR_DIR).tgz $(TAR_DIR)
	@mv $(TAR_DIR).tgz ./tar/
	@rm -Rf $(TAR_DIR) $(QT_BUILD_FOLDER)


dvi:
	@-rm -rf html latex
	@doxygen Doxyfile
	@-$(OPEN_CM) html/index.html


clean: 
	rm -f *.gcda *.gcov *.o *.gcno *.tgz
	rm -f s21_calc.a s21_calc_test.c test
	rm -rf $(BUILD_DIR) $(GCOV_DIR) $(QT_APP_FOLDER)
	rm -rf *out *info report tar
	rm -rf $(TAR_DIR) html latex


%.o: %.c $(HEADER)
	@$(CC) $(CFLAGS) -c $< -o $@


check:
	@checkmk clean_mode=1 s21_calc_test.check > s21_calc_test.c


test: check 
	@$(CC) calc.c stack.c s21_calc_test.c $(LDFLAGS) -o $(TESTS)
	@./$(TESTS)


s21_calc.a: $(OBJ_LIBRARY) $(HEADER)
	@ar rcs s21_calc.a $(OBJ_LIBRARY)
	@rm -rf *.o
	@ranlib s21_calc.a


gcov_report: check
	@$(CC) $(GCOVFLAGS) calc.c stack.c s21_calc_test.c $(LDFLAGS) -o report.out
	@./report.out
	@lcov -t "gcov_report" -o Coverage_Report.info -c -d ./
	@-lcov -r Coverage_Report.info 'calc.c stack.c' -o Coverage_Report.info
	@genhtml -o ./report Coverage_Report.info
	@rm -rf *.o *.gcno *.gcda *.info *.out *.gcov s21_matrix/*.o
	@-$(OPEN_CM) ./report/index-sort-f.html


rebuild: clean all


# ========================================== STYLE =================================================


style:
	@clang-format -n *.c *.h */*.cpp */*.h */*/*.cpp */*/*.h


correctoin_style:
	@clang-format -i *.c *.h */*.cpp */*.h */*/*.cpp */*/*.h
