CC=g++

CFLAGS=
LFLAGS=

TEST=tests.exe

TEST_O=\
	main.o\
	api.o\
	api_test.o

test: $(TEST)
	./$(TEST)

$(TEST): $(TEST_O)
	$(CC) $^ -o $@ $(LFLAGS)

%.o: %.cpp
	$(CC) -c $^ -o $@ $(CFLAGS)

clean:
	rm -f $(TEST_O)

distclean: clean
	rm -f $(TEST)