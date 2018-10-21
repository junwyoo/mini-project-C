/*
	dOOr transpiler Project
	Junwhan Yoo
	2018.10.21
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // getopt
#include <string.h> // strstr
#include "tokens.h"

#define BUFFSIZE 1024

void freePP(char** buf, int n);
void getTokens(char* buf, int n);

int main(int argc, char** argv) 
{
	//door <source> <destination>

	if(argc != 3){
		fprintf(stderr, "[ERROR] Invalid number of arguments. Usage : door <source> <destination>\n");
		return -1;
	}
	
	/*
		variable declaration
	*/
	int res, lastBytes, i;
	long f_size; //input file size in bytes
	int n_blocks; //number of BUFFSIZE chunks
	FILE* fp;
	char** buffers;
	/////////////////// parse var
	unsigned int tabs;
	
	char* src = argv[1];
	char* dst = argv[2];
	
	fp = fopen(src, "r");
	if(fp == NULL){
		fprintf(stderr, "[ERROR] could not open %s.\n", src);
		return -1;
	}
//3272
	///////////////////////////Must Free input file under this line	
	//determine the file size
	fseek(fp, 0, SEEK_END);
	f_size = ftell(fp);
	rewind(fp);
	
	n_blocks = (f_size/BUFFSIZE) + 1;
	char* blocks[n_blocks];

	res = 0;
	for(i=0; i<n_blocks; i++){
		blocks[i] = (char*) malloc (sizeof(char)*BUFFSIZE);
		if(blocks[i] == NULL){
			fprintf(stderr, "[ERROR] Memory Error\n");
			freePP(blocks, i);
			fclose(fp);
			return -1;
		}		
		res += fread (blocks[i], sizeof(char), BUFFSIZE, fp); // res = read counts
		printf("%d. res = %d\n", i, res);
	}
	
	printf("res : %d, f_size : %d\n", res, f_size);
	
	if (res == 0){
  		fprintf(stderr, "[ERROR] Could not read the file %s.\n", src);
		freePP(blocks, i);
		fclose(fp);
		return -1;
	}
	lastBytes = res;
	
	char* tokens;
	getTokens(blocks[0], lastBytes);
	
//	for(i=0; i<n_blocks; i++){
//		printf("[%d] block : \n%s\n",i+1, blocks[i]); // print out blocks of text
//	}
	
 	fclose(fp);
  	freePP(blocks, n_blocks);
	
	return 0;
}


void freePP(char** buf, int n)
{
	int i;
	for(i=0; i<n; i++){
		free(*(buf+i));
	}
}
void getTokens(char* buf, int n)
{
	int i = 0;
	char ret[n];
	for(i=0; i<n; i++){
		if(isspace(buf[i]))
			continue;
		printf("%c ", buf[i]);
	}
}

