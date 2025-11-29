ALL: 	main

main:	amedonha.o estrutura.o
	gcc amedonha.o estrutura.o -o main -lm

amedonha.o: amedonha.c estrutura.h
	gcc -c amedonha.c
estrutura.o: estrutura.c estrutura.h
	gcc -c estrutura.c

clean:
	rm -f main *.o