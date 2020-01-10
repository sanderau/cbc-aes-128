#include <stdint.h>

#ifndef READ_PTXT_H
#define READ_PTXT_H

#define BLOCK_LENGTH 16

//declare all the functions in this program. Will maybe put them in their own source and header file.
//more realistically I will probably forgot about this project tomorrow, and never touch it again.
void fatal_error(char *msg, int exit_code);
void free_ptxt(int8_t ***ptxt, int num_blocks);
void read_key(int8_t *key);
void add_padding(int8_t ***ptxt, int null_bytes, int last_block);
void alloc_ptxt(int8_t ***ptxt, int num_blocks);
void copy_array(int8_t ***copy, int8_t **data, int num_blocks);
void alloc_ptxt(int8_t ***ptxt, int num_blocks);
void copy_array(int8_t ***copy, int8_t **data, int num_blocks);
void print_ptxt(int8_t **, int);
int add_block(int8_t ***ptxt, int num_blocks);
int read_plaintext(int8_t ***ptxt, int num_blocks, char *file);

#endif
