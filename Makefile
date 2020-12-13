CC	=	gcc
CFLAGS	=	-g	-Wall
DEPS	=	include/config.h
OBJ	= 	main.o	src/dir_opr.o	src/file_opr.o	
default:	BIPL

BIPL:	main.o	src/dir_opr.o	src/file_opr.o
	$(CC)	$(CFLAGS)	-o	BIPL	main.o	src/dir_opr.o	src/file_opr.o
clear:
	rm -rf src/*.o 
	rm -rf *.o

