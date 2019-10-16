CC = gcc
OBJS = src/pack.o src/util.o src/lodepng.o
OUT = main
OUTS = $(OUT)

all: $(OUTS)

%.o: src/%.cc
	$(CC) $< -o $@ $(CFLAGS)

main: src/main.o $(OBJS)
	$(CC) $(OBJS) $< -o $@

clean:
	rm -f *.o *.P $(OUTS)
