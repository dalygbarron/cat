CC = gcc
CFLAGS = -g -I src
OBJS = src/pack.o src/util.o src/write.o src/lodepng.o
TEST_OBJS = src/test/unit.o
MAIN = main
TEST = test
OUTS = $(MAIN) $(TEST)

all: $(OUTS)

%.o: src/%.cc
	$(CC) $< -o $@ $(CFLAGS)

main: src/main.o $(OBJS)
	$(CC) $(OBJS) $< -o $@ $(CFLAGS)

test: src/test/testUtil.o $(OBJS) $(TEST_OBJS)
	$(CC) $(OBJS) $(TEST_OBJS) $< -o $@ $(CFLAGS)

clean:
	rm -f src/*.o $(OUTS)
