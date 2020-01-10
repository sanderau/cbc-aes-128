#include <stdio.h> // printf, fprintf, FILE, fopen
#include <stdlib.h>
#include <time.h>

#include "aes128.h" // encrypt and decrypt 128 bit blocks with aes
#include "read_ptxt.h" // how we read in plaintext

void create_IV(int8_t ***ctxt)
{
	int i ;

	for(i = 0; i < BLOCK_LENGTH; i++)
	{
		(*ctxt)[0][i] = rand();	
	}
}

void cbc_aes_128(int8_t ***ptxt, int8_t ***ctxt, int8_t *key, int num_blocks)
{
	int i = 0;

	for(i = 1; i <= num_blocks; i++)
	{
		
	}
}

int main(int argc, char *argv[])
{
	// exit program if they forgot to include ptxt
	if(argc < 2 || argc > 2)
	{
		fatal_error("Need to include the plaintext. (./cbc_enc <plaintext filename>)", 2);
	}

	srand( time( NULL ) );

	//initialize all data needed for program
	int8_t key[16];
	int8_t **ptxt;
	int8_t **ctxt;
	int num_blocks = 1;

	//read the key
	read_key(key);

	// read the plaintext message into memory
	num_blocks = read_plaintext(&ptxt, num_blocks, argv[1]);

	//aloc the ctxt, add one block to account for c0
	alloc_ptxt(&ctxt, num_blocks+1);

	//encrypt the data
	cbc_aes_128(&ptxt, &ctxt, key, num_blocks);

	// free the memory
	free_ptxt(&ptxt, num_blocks);
	free_ptxt(&ctxt, num_blocks+1);

	return 0;
}
