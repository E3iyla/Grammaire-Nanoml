opt = -c -Wall -Wextra

all : nanoml.exe

nanoml.exe : main.o lexique.o arbre.o analyseur.o rendu.o
	gcc -o nanoml.exe main.o lexique.o arbre.o analyseur.o rendu.o

main.o : main.c
	gcc $(opt) main.c

lexique.o : lexique.c
	gcc $(opt) lexique.c

arbre.o : arbre.c
	gcc $(opt) arbre.c

analyseur.o : analyseur.c
	gcc $(opt) analyseur.c

rendu.o : rendu.c
	gcc $(opt) rendu.c

clean :
	rm -f *.o *.exeQ