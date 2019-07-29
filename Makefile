CC = c++
CFLAGS = -std=c++17
LFLAGS = -lsfml-graphics -lsfml-window -lsfml-system
OBJS = ImageNode.o File.o
OUT = main
READER = reader
OUTS = $(OUT) $(READER)

%.o: src/%.cc
	$(CC) $< -o $@ $(CFLAGS)

main: main.o $(OBJS)
	$(CC) $(OBJS) $< $(LFLAGS) -o $@ $(CFLAGS)

reader: reader.o $(OBJS)
	$(CC) $(OBJS) $< $(LFLAGS) -o $@ $(CFLAGS)

all: $(OUTS)

clean:
	rm -f *.o *.P $(OUTS)
