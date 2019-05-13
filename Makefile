CC = c++
CFLAGS = -std=c++17
LFLAGS = -lsfml-graphics -lsfml-window -lsfml-system
OBJS = main.o ImageNode.o
OUT = main

%.o: src/%.cc
	@g++ -MD -c -o $@ $< $(CFLAGS) -g
	@cp $*.d $*.P; \
	sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
	-e '/^$$/ d' -e 's/$$/ :/' < $*.d >> $*.P; \
	rm -f $*.d

-include *.P

all: $(OBJS)
	$(CC) $(OBJS) $(LFLAGS) -o $(OUT) $(CFLAGS) -g

run: all
	./$(OUT)

clean:
	rm -f *.o *.P $(OUT)
