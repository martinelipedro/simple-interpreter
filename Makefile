SOURCES = $(shell find . -type f -name '*.c')
HEADERS = $(shell find . -type f -name '*.h')
OBJECTS = $(SOURCES:.c=.o)

.PHONY: all clean

all: $(OBJECTS) $(HEADERS)
	gcc $^ -o scomp

clean:
	rm -rf $(OBJECTS)
	rm -f out

%.o: %.c 
	gcc -c $< -o $@ 