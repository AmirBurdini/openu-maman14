encode: encode.o
	gcc -g -ansi -Wall -pedantic encode.o -o encode
encode.o : encode.c
	gcc -c -ansi -Wall -pedantic encode.c -o encode.o