# Variables

src_dir = src
obj_dir = obj

_OBJECTS = Lexique.o Liste.o
OBJECTS = $(patsubst %,$(obj_dir)/%,$(_OBJECTS))

CFLAGS = -c -ansi -g -O2 -Wall
LDLIBS =

# Compiler

all: compil
compil: $(OBJECTS)
	gcc $(OBJECTS) $(LDLIBS) -o Lexique.exe
	@echo Compilation finie
$(obj_dir)/%.o: $(src_dir)/%.c
	gcc $(CFLAGS) $< -o $@
clean:
	rm -f obj/*.o
	rm -f data/*.L
	rm -f data/*.DICO