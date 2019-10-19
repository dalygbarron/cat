CC = gcc
CFLAGS = -g -I src
OBJS = src/pack.o src/util.o src/write.o src/lodepng.o src/path.o
TEST_OBJS = src/test/unit.o
MAIN = main
TESTS = testUtil testPath
OUTS = $(MAIN) $(TESTS)

all: $(OUTS)

%.o: src/%.cc
	$(CC) $< -o $@ $(CFLAGS)

main: src/main.o $(OBJS)
	$(CC) $(OBJS) $< -o $@ $(CFLAGS)

testUtil: src/test/testUtil.o $(OBJS) $(TEST_OBJS)
	$(CC) $(OBJS) $(TEST_OBJS) $< -o $@ $(CFLAGS)

testPath: src/test/testPath.o $(OBJS) $(TEST_OBJS)
	$(CC) $(OBJS) $(TEST_OBJS) $< -o $@ $(CFLAGS)

clean:
	rm -f src/*.o $(OUTS)
