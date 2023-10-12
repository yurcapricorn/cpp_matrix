CC = g++
CFLAGS = -Wall -Wextra -Werror
FLAGS_TEST = -lgtest -lpthread -fprofile-arcs -ftest-coverage
SRC_DIR= .
TEST_DIR= .
INCLUDE_DIR= .
BUILD_DIR = ./build
SRC = s21_matrix_oop.cpp
INCLUDE = s21_matrix_oop.h
OBJS = $(SRC:%.cpp=$(BUILD_DIR)/%.o)

all: clean s21_matrix_oop.a

test: clean
	$(CC) $(CFLAGS) tests.cpp s21_matrix_oop.cpp $(FLAGS_TEST)
	./a.out

s21_matrix_oop.a: $(OBJS)
	@mkdir -p $(BUILD_DIR)
	ar rc s21_matrix_oop.a $(OBJS)
	ranlib s21_matrix_oop.a

$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@ $(LFLAGS)

clean:
	rm -f s21_matrix_oop.a
	rm -rf $(BUILD_DIR)
	rm -rf *.o *.out *.gcno *.gcda *.css *.html *.info

style:
	cp ../materials/linters/.clang-format ./
	clang-format -i *.cpp *.h
	clang-format -n *.cpp *.h
	rm .clang-format

valgrind: test
	valgrind --track-origins=yes --show-leak-kinds=all --leak-check=full ./a.out

gcov_report: test
	gcovr -r . --html --html-details -o coverage_report.html
	open coverage_report.html

push: clean style
	git fetch
	git add .
	git commit -m "$(c)"
	git push origin develop

.PHONY: all s21_matrix_oop.a style valgrind test gcov_report clean push 