main:  main.o libreria.o Makefile
	gcc -ansi -Wall -O main.o libreria.o -o progetto

main.o: main.c libreria.h Makefile
	gcc -ansi -Wall -O -c main.c

libr.o: libreria.c libreria.h Makefile 
	gcc -ansi -Wall -O -c libreria.c
pulisci:
	rm -f main.o libreria.o
pulisci_tutto:
	rm -f main main.o libreria.o
