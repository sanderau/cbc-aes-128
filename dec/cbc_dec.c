#include "stdio.h"
#include "stdlib.h"
#include "time.h"

#include "aes128.h"
#include "read_ptxt.h"
/*
 *void read_key(int8_t *key);
 *int read(int8_t ***ptxt, int num_blocks, char *file);
 */

void decrypt_cbc_aes(int8_t ***ptxt, int8_t ***ctxt, int num_blocks)
{
	int i,j;

	for(i = 0; i < num_blocks; i++)
	{
		int8_t plain[16];

		aes128_dec((*ctxt)[i+1], plain);

		for(j = 0; j < BLOCK_LENGTH; j++)
		{
			(*ptxt)[i][j] = (*ctxt)[i][j] | plain[j];
		}
	}
}


int main(int argc, char *argv[])
{

	if(argc != 2) {
		fprintf(stderr, "Did not include the correct number of args.\n./cbc_dec <ctxt>\nExiting...");
		return 1;
	}

	srand(time(NULL));

	int8_t key[16]; // key for aes
	int8_t **ptxt; // plain text
	int8_t **ctxt; // cipher text 
	int num_blocks = 0;

	//load up that ciphertext
	num_blocks = read(&ctxt, num_blocks, argv[1]);

	//alloc plain
	alloc_ptxt(&ptxt, num_blocks-1);

	//read key and load it into aes
	read_key(key); 
	aes128_load_key(key);

	//decrypt that jazz
	//decrypt_cbc_aes(&ptxt, &ctxt, num_blocks);

	//print that shit out
	//print_ptxt(ptxt, num_blocks);

	return 0;
}
