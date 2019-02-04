OPT= -g -Wall -Wextra -Werror -std=c99

all: kmoyennes

testConteneur: testConteneur.o conteneur.o
	gcc $(OPT) $^ -o $@

testClasseur: testClasseur.o classeur.o conteneur.o
	gcc $(OPT) $^ -o $@

kmoyennes: kmoyennes.o image.o classeur.o conteneur.o
	gcc $(OPT) $^ -o $@

conteneur.o: conteneur.h
classeur.o: classeur.h

%.o: %.c
	gcc $(OPT) -c $<

# Génération de l'archive
.PHONY: archive
archive: algo-kmoy.tar.gz

algo-kmoy.tar.gz: $(wildcard *.c) $(wildcard *.h)
	tar cvaf $@ --transform "s,,algo-kmoy/," $^

# Ménage
clean:
	rm -f *.o testClasseur testConteneur kmoyennes

distclean: clean
	rm -f algo-kmoy.tar.gz *~
