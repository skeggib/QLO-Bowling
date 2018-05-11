CC=g++

CFLAGS=-Wfatal-errors -std=c++11
LFLAGS=

EXE=bowling.exe
TEST=tests.exe

EXE_O=\
	bowling.o\
	main.o

TEST_O=\
	test.o\
	bowling.o\
	bowling_test.o

all: $(EXE)

run: all
	./$(EXE)

tests: $(TEST)

runtests: tests
	./$(TEST)

$(EXE): $(EXE_O)
	$(CC) $^ -o $@ $(LFLAGS)

$(TEST): $(TEST_O)
	$(CC) $^ -o $@ $(LFLAGS)

%.o: %.cpp
	$(CC) -c $^ -o $@ $(CFLAGS)

clean:
	rm -f $(TEST_O)

distclean: clean
	rm -f $(TEST)