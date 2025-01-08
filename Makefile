CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -std=c11
GCOV_FLAGS = -fprofile-arcs -ftest-coverage
CHECK_LIBS = -lcheck -lsubunit -lrt -lpthread -lm

TEST_DIR = ./tests
BUILD_DIR = ./build
OBJ_DIR = $(BUILD_DIR)/obj
STATIC_LIB = ./s21_matrix.a
TEST_SRC=$(wildcard $(TEST_DIR)/test_*.c)
SOURCES = $(wildcard s21_*.c)
OBJECTS = $(patsubst %.c, $(OBJ_DIR)/%.o, $(SOURCES))

all: $(STATIC_LIB) tests

$(STATIC_LIB): $(OBJECTS)
	@ar rcs $(STATIC_LIB) $(OBJECTS)
	@ranlib $(STATIC_LIB)

$(OBJ_DIR)/%.o: ./%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

tests: 
	${CC} $(CFLAGS) $(GCOV_FLAGS) $(SOURCES) ${TEST_SRC} $< -o unit_test $(CHECK_LIBS)
	./unit_test

valgrind_tests: $(TEST_EXECUTABLES)
	@echo "Running tests with Valgrind..."
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all --trace-children=yes -s ./unit_test 2>&1 || true;
	@echo "end"

gcov_report: tests
	@echo "Generating coverage report..."
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory ./coverage_report
	@xdg-open ./coverage_report/index.html || echo "Could not open report"

clean:
	rm -f *.o
	rm -f $(STATIC_LIB) $(TEST_EXECUTABLES) $(OBJ_DIR)/*.o coverage.info
	rm -f $(TEST_DIR)/*.gcno $(TEST_DIR)/*.gcda 
	rm -f *.gcno *.gcda unit_test
	rm -rf $(OBJ_DIR) coverage_report

clean_tests:
	rm -f $(TEST_EXECUTABLES)

.PHONY: all tests gcov_report clean clean_tests