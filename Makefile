CC = c++
CFLAGS = -std=c++17
LFLAGS = -lsfml-graphics -lsfml-window -lsfml-system
OBJS = ImageNode.o File.o
OUT = main.x86
READER = reader.x86
OUTS = $(OUT) $(READER)

%.o: src/%.cc
	@g++ -MD -c -o $@ $< $(CFLAGS)
	@cp $*.d $*.P; \
	sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
	-e '/^$$/ d' -e 's/$$/ :/' < $*.d >> $*.P; \
	rm -f $*.d

%.x86: %.o $(OBJS)
	$(CC) $(OBJS) $< $(LFLAGS) -o $@ $(CFLAGS)

-include *.P

all: $(OUTS)

clean:
	rm -f *.o *.P $(OUTS)
