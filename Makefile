SOURCES = $(shell find . -type f -name '*.c')
HEADERS = $(shell find . -type f -name '*.h')
OBJECTS = $(SOURCES:.c=.o)

EXE_NAME = simple_interpreter

.PHONY: all clean

all: $(OBJECTS) $(HEADERS)
	gcc $^ -o $(EXE_NAME)

clean:
	rm -rf $(OBJECTS)
	rm -f out

%.o: %.c 
	gcc -c $< -o $@ 