CC=gcc
PKGCONFIG = $(shell which pkg-config) 
CFLAGS=-Wall -Wextra -Werror $(shell $(PKGCONFIG) --cflags gtk4)
SOURCES=controller/*
TEST_SOURCES=controller/*.cc tests/*.cpp
UNAME_S=$(shell uname -s)
GCOV_FLAGS=

ifeq ($(UNAME_S),Linux)
LDFLAGS= -lm -lcheck -lpthread -lsubunit
endif
ifeq ($(UNAME_S),Darwin)
LDFLAGS= -lm -lcheck -lpthread
endif

all: install

test:
	$(CC) $(CFLAGS) $(TEST_SOURCES) $(LDFLAGS) $(GCOV_FLAGS) -o test

gcov_report: GCOV_FLAGS += -fprofile-arcs -ftest-coverage
gcov_report: test
	./test > /dev/null
	lcov -c -d . -o report.info --no-external
	genhtml -o "html_report" report.info
	open html_report/index.html

install:
	rm -rf smartСalc
	mkdir smartСalc
	qmake view/calculator.pro -o smartСalc
	cd smartСalc && make && cd ../
	chmod +x smartСalc/calculator.app
	ln -s ${PWD}/smartСalc/calculator.app ${HOME}/Desktop/Calculator

uninstall:
	rm -rf smartСalc
	rm ${HOME}/Desktop/Calculator

dvi:
	open README.html

dist: install
	tar -czf smartСalc.tar.gz --directory=smartСalc/ .

style:
	clang-format -style=google -i src/model/ calc_functions/*.h
	clang-format -style=google -i qt_smart_calc/*.h qt_smart_calc/*.cpp
	clang-format -style=google -n calc_functions/*.c calc_functions/*.h
	clang-format -style=google -n qt_smart_calc/*.h qt_smart_calc/*.cpp

clean:
	rm -rf obj *.a test html_report report.info program *.o *.gch calc_functions/*.gch *.gcno *.gcda smartСalc.tar.gz smartСalc
	
lib:
	$(CC) -c $(SOURCES) $(LDFLAGS)
	ar -rc libcalc.a *.o
	ranlib libcalc.a

.PHONY: all test clean lib gcov_report
