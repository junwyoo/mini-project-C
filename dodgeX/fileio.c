
#include "dodgeX.h"

static int bestScore = 0;

int loadBest(){
	printf("Loading file...\n");
	FILE* pFile = fopen("./dodgeX.txt","r");
	if(pFile){
		fscanf(pFile, "%d", &bestScore);
		fclose(pFile);
		return bestScore;
	}
	fclose(pFile);
	return -1;
}

int saveBest(int n){
	if(n>=bestScore){
		FILE* fp = fopen("./dodgeX.txt", "w");
		fprintf(fp, "%d",n);
		bestScore = n;
		fclose(fp);
		return 0;
	}
	return -1;
}
