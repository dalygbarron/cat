# define installation directory
ifeq ($(PREFIX),)
    PREFIX := /usr/local
endif

# constants
CC = gcc
CFLAGS = -g -I src
OBJS = src/pack.o src/util.o src/write.o src/lodepng.o src/path.o
TEST_OBJS = src/test/unit.o
MAIN = rat
TESTS = testUtil testPath
OUTS = $(MAIN) $(TESTS)

# recipes
all: $(OUTS)

install: $(MAIN)
	install -m 755 $(MAIN) $(PREFIX)/bin/

%.o: src/%.cc
	$(CC) $< -o $@ $(CFLAGS)

rat: src/main.o $(OBJS)
	$(CC) $(OBJS) $< -o $@ $(CFLAGS)

testUtil: src/test/testUtil.o $(OBJS) $(TEST_OBJS)
	$(CC) $(OBJS) $(TEST_OBJS) $< -o $@ $(CFLAGS)

testPath: src/test/testPath.o $(OBJS) $(TEST_OBJS)
	$(CC) $(OBJS) $(TEST_OBJS) $< -o $@ $(CFLAGS)

clean:
	rm -f src/*.o $(OUTS)
