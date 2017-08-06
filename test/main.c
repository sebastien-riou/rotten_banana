

#include <stdlib.h>
#include <string.h>

#include "bytes_utils.h"
void AES_128_encrypt(unsigned char *out, unsigned char *in);
int main(int argc, char *argv[]){
	uint8_t in[16] = {0x32, 0x43, 0xf6, 0xa8, 0x88, 0x5a, 0x30, 0x8d, 0x31, 0x31, 0x98, 0xa2, 0xe0, 0x37, 0x07, 0x34};
	uint8_t out[16];
	uint8_t ref_out[16];
	uint8_t len = 0;
	if (argc>1)
		len=strlen(argv[1]);

	if(len>32){
		printf("input too long\n");
		exit(-1);
	}

	if(len > 0) 
		hexstr_to_bytes(len/2,in,argv[1]);

	println_128("input:    ",in);

	AES_128_encrypt((unsigned char *)out, (unsigned char *)in);
	println_128("output:   ",out);
	return 0;
}
