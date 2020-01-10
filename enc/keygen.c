#include <stdio.h> // FILE, fopen, fprintf
#include <stdlib.h> //srand, rand
#include <time.h> // time
#include <stdint.h> // int8_t

int main(void)
{
	srand(time(NULL));

	int8_t key[16];
	int i;

	for(i = 0; i < 16; i++)
	{
		key[i] = rand();
	}

	FILE *fptr = fopen("key", "w+");

	fprintf(fptr, "%s", key);
}
