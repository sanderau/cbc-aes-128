CC = gcc
CFLAGS = -g -O0 -Wall -msse2 -msse -march=native -maes
HDR = aes128.h read_ptxt.h
OBJ = aes128.o
SRC = aes128.c cbc_dec.c read_ptxt.c
MEM = valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-fds=yes

make:
	${CC} ${CFLAGS} ${SRC} ${HDR} -o cbc_dec

memcheck:
	${MEM} ./cbc_enc plaintext

clean: 
	rm cbc_dec keygen key
