#include <stdio.h> // printf, fprintf, FILE, fopen
#include <stdlib.h>
#include <time.h>

#include "aes128.h" // encrypt and decrypt 128 bit blocks with aes
#include "read_ptxt.h" // how we read in plaintext

void create_IV(int8_t ***ctxt)
/***************************************************************************
 * name: create_IV
 * description: creates an IV for the CBC mode
 * parameters: the ctxt array to put it in
 * *************************************************************************/
{
	int i ;

	for(i = 0; i < BLOCK_LENGTH; i++)
	{
		(*ctxt)[0][i] = rand();	
	}
}

void cbc_aes_128(int8_t ***ptxt, int8_t ***ctxt, int8_t *key, int num_blocks)
/****************************************************************************
 * name: cbc_aes_128
 * description: the actual program lol. Everything else is written so these ten lines of code can run.
 * parameters: The plaintext, ciphertext, and number of blocks to encrypt.
 * *************************************************************************/
{
	int i = 0;

	for(i = 1; i <= num_blocks; i++)
	{
		int8_t xor[BLOCK_LENGTH];

		for(int j = 0; j < BLOCK_LENGTH; j++)
		// XOR the blocks
		{
			// ctxt is i - 1 to account for the IV
			// ptxt is i - 1 because ctxt will be 1 block longer than ptxt due to the IV
			xor[j] = (*ctxt)[i-1][j] | (*ptxt)[i-1][j];
		}

		// feed the result XOR to AES-128 bit enc
		aes128_enc(xor, (*ctxt)[i]);	
	}
}

void print_ctxt(int8_t ***ctxt, int num_blocks)
{
	int i, j;

	for(i = 0; i < num_blocks; i++)
	{
		for(j = 0; j < BLOCK_LENGTH; j++)
		{
			printf("%d", (*ctxt)[i][j]);
		}
	}

	printf("\n");

}

void write_ctxt(int8_t ***ctxt, int num_blocks)
{
	FILE *fptr = fopen("ciphertext", "w+");

	for(int i = 0; i < num_blocks; i++)
	{
		fprintf(fptr, "%s", (*ctxt)[i]);
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

	//load the key into AES
	aes128_load_key(key);	

	// read the plaintext message into memory
	num_blocks = read_plaintext(&ptxt, num_blocks, argv[1]);

	//aloc the ctxt, add one block to account for c0
	alloc_ptxt(&ctxt, num_blocks+1);

	//print ctxt before
	//print_ctxt(&ctxt, num_blocks);

	//encrypt the data
	cbc_aes_128(&ptxt, &ctxt, key, num_blocks);

	//print after to see if there is succsefull change
	//print_ctxt(&ctxt, num_blocks);
	
	//write the ciphertext to a file
	write_ctxt(&ctxt, num_blocks);

	// free the memory
	free_ptxt(&ptxt, num_blocks);
	free_ptxt(&ctxt, num_blocks+1);

	return 0;
}
