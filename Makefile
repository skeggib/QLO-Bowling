CC=g++

CFLAGS=-Wfatal-errors -std=c++11
LFLAGS=

TEST=tests.exe

TEST_O=\
	test.o\
	bowling.o\
	bowling_test.o

tests: $(TEST)

runtests: tests
	./$(TEST)

$(TEST): $(TEST_O)
	$(CC) $^ -o $@ $(LFLAGS)

%.o: %.cpp
	$(CC) -c $^ -o $@ $(CFLAGS)

clean:
	rm -f $(TEST_O)

distclean: clean
	rm -f $(TEST)