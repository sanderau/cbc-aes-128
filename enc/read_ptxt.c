#include <stdio.h> // printf, fprintf, FILE, fopen
#include <stdlib.h>

#include "read_ptxt.h"

void fatal_error(char *msg, int exit_code)
/*
 * Function: fatal_error
 * Parameters: string containing error message, exit code
 * Description: If a fatal error is encountered, then this function
 * will print the error message and exit with the corresponding code
 */
{
	fprintf(stderr, "Fatal error: %s\nExiting...\n", msg);

	exit(exit_code);
}

void free_ptxt(int8_t ***ptxt, int num_blocks)
/*
 * Description: Frees the memory of the plaintext array
 * Parameters:
 * 	ptxt: reference by pointer to the plaintext array
 * 	num_blocks: number of blocks in plaintext array
 */
{
	int i;

	for(i = 0; i < num_blocks; i++)
	{
		free((*ptxt)[i]);
	}

	free(*ptxt);
}


void read_key(int8_t *key)
/*
 * Function: read_key
 * Parameter: 16 byte int8_t array
 * Description: Loads a pregenerated key into memory
 */
{
	int i = 0;
	int8_t index;
	FILE *keyptr = fopen("key", "r");

	if(keyptr == NULL)
	{
		fatal_error("No key found.", 1);
	}

	while((index = fgetc(keyptr)) != EOF)
	{
		key[i] = index;
		i++;
	}
}

void add_padding(int8_t ***ptxt, int null_bytes, int last_block)
/*
 * Function: add_padding
 * Description: Adds padding to the last block of the plain text
 * adheres to the ansi X.923 standard
 * Parameters:
 * 	ptxt: the plaintext
 * 	null_bytes: the number of null bytes in the last block
 * 	last_block: the index of the last block in ptxt
 */
{
	int i;

	for(i=15; i < (15 - null_bytes); i--)
	{
		if(i == 15) {
			(*ptxt)[last_block][i] = null_bytes;
		} else {
			(*ptxt)[last_block][i] = 0x00;
		}
	}
}

void alloc_ptxt(int8_t ***ptxt, int num_blocks)
/*
 * Description:
 * Parameters:
 * 	ptxt: pointer reference to 2d array of plaintext
 * 	num_blocks: number of blocks to allocate
 */
{
		int i;

		*ptxt = (int8_t **)malloc(num_blocks * sizeof(int8_t *));

		for(i = 0; i < num_blocks; i++)
		{
			(*ptxt)[i] = (int8_t *)malloc(BLOCK_LENGTH * sizeof(int8_t));
		}
}

void copy_array(int8_t ***copy, int8_t **data, int num_blocks)
/*
 * Description: copy the contents of the second array into the first array
 * Parameters:
 * 	Data: the array to copy data from
 * 	copy: the array to copy data into
 * 	num_blocks: number of blocks
 */
{
	int i,j;

	for(i = 0; i < num_blocks; i++)
	{
		for(j = 0; j < BLOCK_LENGTH; j++)
		{
			(*copy)[i][j] = data[i][j];
		}

	}
}

int add_block(int8_t ***ptxt, int num_blocks)
/*
 * Description: This will add a 128 bit block to the plaintext
 * Parameters:
 * 	ptxt: pass the plaintext 2d array by pointer
 * 	num_blocks: the current number of blocks
 *
 */
{
	num_blocks++;

	// create a temporary array, and allocate memory for it
	int8_t **temp;
	alloc_ptxt(&temp, num_blocks);

	copy_array(&temp, *ptxt, num_blocks-1); //copy data from plaintext array into temp array

	free_ptxt(ptxt, num_blocks-1); // free the plaintext array

	alloc_ptxt(ptxt, num_blocks); // re initialize ptxt with one more block

	copy_array(ptxt, temp, num_blocks); // copy data back into ptxt

	free_ptxt(&temp, num_blocks); //free the temp array

	return num_blocks;
}

int read_plaintext(int8_t ***ptxt, int num_blocks, char *filename)
{
	// check to see if the file exists
	FILE *fptr = fopen(filename, "r");
	int8_t c;
	int index = 0;

	if(fptr == NULL)
	{
		fatal_error("Plaintext file does not exist", 3);
	}

	// first allocate memory to the first block
	alloc_ptxt(ptxt, num_blocks);

	// read file by character
	while((c = fgetc(fptr)) != EOF)
	{
		if(index >= 15)
		{
			num_blocks = add_block(ptxt, num_blocks);
			index = 0;
		}

		(*ptxt)[num_blocks-1][index] = c;
		index++;
	}

	if(index < 15) {
		add_padding(ptxt, 15-index, num_blocks-1);
	}

	return num_blocks;
}

void print_ptxt(int8_t **ptxt, int num_blocks)
// not to be actually used
// just used in testing
{
	int i, j;

	for(i = 0; i < num_blocks; i++)
	{
		for(j = 0; j < BLOCK_LENGTH; j++)
		{
			printf("%c", ptxt[i][j]);
		}
	}
}
