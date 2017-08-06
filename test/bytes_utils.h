
#ifndef __BYTES_UTILS_H__
#define __BYTES_UTILS_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>



static void print_bytes_sep(const char *msg,const unsigned char *buf, unsigned int size, const char m2[], const char sep[]){
    unsigned int i;
    printf("%s",msg);
    for(i=0;i<size-1;i++) printf("%02X%s",buf[i],sep);
    if(i<size) printf("%02X",buf[i]);
    printf("%s", m2);
}
static void print_bytes(const char m[],const uint8_t *buf, unsigned int size, const char m2[]){print_bytes_sep(m,buf,size,m2," ");}
static void println_bytes(const char m[],const uint8_t *buf, unsigned int size){print_bytes(m,buf,size,"\n");}
static void print_128(const char m[], const uint8_t a[16], const char m2[]){
	print_bytes_sep( m,a   ,4,"_","");
	print_bytes_sep("",a+4 ,4,"_","");
	print_bytes_sep("",a+8 ,4,"_","");
	print_bytes_sep("",a+12,4,m2 ,"");
}
static void println_128(const char m[], const uint8_t a[16]){print_128(m,a,"\n");}

static int hexdigit_value(char c){
	int nibble = -1;
	if(('0'<=c) && (c<='9')) nibble = c-'0';
	if(('a'<=c) && (c<='f')) nibble = c-'a' + 10;
	if(('A'<=c) && (c<='F')) nibble = c-'A' + 10;
	return nibble;
}

static int is_hex_digit(char c){
	return -1!=hexdigit_value(c);
}

static void hexstr_to_bytes(unsigned int size_in_bytes, void *dst, const char * const hexstr){
	unsigned int char_index = 0;
	unsigned int hexdigit_cnt=0;
	uint8_t* dst_bytes = (uint8_t*)dst;
	memset(dst,0,size_in_bytes);
	while(hexdigit_cnt<size_in_bytes*2){
		char c = hexstr[char_index++];
		if(0==c) {
			printf("\nERROR: could not find %d hex digits in string '%s'.\n",size_in_bytes*2,hexstr);
			printf("char_index=%d, hexdigit_cnt=%d\n",char_index,hexdigit_cnt);
			exit(-1);
		}
		if(is_hex_digit(c)) {
			unsigned int shift = 4 - 4*(hexdigit_cnt & 1);
			uint8_t nibble = hexdigit_value(c);
			dst_bytes[hexdigit_cnt/2] |= nibble << shift;
			hexdigit_cnt++;
		}
	}
}

static void xor_bytes( uint8_t *d, const uint8_t *s, size_t size ){
    for(size_t i=0;i<size;i++)
		d[i] ^= s[i];
}

#endif
