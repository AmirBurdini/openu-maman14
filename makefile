<<<<<<< HEAD
encode: encode.o
	gcc -g -ansi -Wall -pedantic encode.o -o encode
encode.o : encode.c
	gcc -c -ansi -Wall -pedantic encode.c -o encode.o
=======

	

all:   data.h preProccesor.c  sharedStates.c  exportFiles.c  errors.c utils.c helpers.c parse.c operations.c tables.c memory.c firstRun.c secondRun.c compiler.c
	gcc -ansi -Wall -pedantic -g data.h preProccesor.c sharedStates.c   exportFiles.c errors.c utils.c helpers.c parse.c operations.c tables.c  memory.c secondRun.c firstRun.c compiler.c -o compiler -lm
>>>>>>> dd6bd0b869908a40e384b285d9cd6e890cc515a9
