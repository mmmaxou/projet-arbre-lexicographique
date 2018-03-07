# Variables

src_dir = src
obj_dir = obj

# _OBJECTS = main.o UListe.o Monde.o Unite.o Affichage.o Utils.o Sauvegarde.o AffichageMLV.o
_OBJECTS = main.o
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