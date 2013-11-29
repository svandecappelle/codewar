# Ces cibles ne sont pas des vrais fichiers
.PHONY: clean, real-clean

# On desactive toutes les regles implicites
.SUFFIXES:

# Declarations de constantes 
BINFILE = CodeWar

OBJFILES = \
	CodeWar.o\
	affichage.o\
	debug.o\
	typage_operande.o\
	arguments.o\
	commandes.o\
	interpreteur.o\
	modifications.o\
	flags.o\
	debug.o\

# Constantesservant a la compilation et a l'edition de liens
CC = gcc
CFLAGS = \
	-ansi \
#	-pedantic \
	-Wall \
	-W \
	-Werror \
	-fno-builtin\
	-Wno-char-subscripts

LD = gcc
LDFLAGS = -s

# Regle explicite : $@ represente le binaire et $^ la liste des fichiers objets
$(BINFILE): $(OBJFILES)
	$(LD) $(LDFLAGS) -o $@ $^ -lm

# Regle generique : $< represente le fichier .c qu'on veut compiler
%.o: %.c
	$(CC) $(CFLAGS) -c $< 

# Regles de nettoyage des fichiers generables par make
clean:
	rm -f $(OBJFILES)

real-clean:
	make clean
	rm -f $(BINFILE)

