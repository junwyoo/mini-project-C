#include <stdio.h>

#include <stdlib.h>
#include <time.h>

#define MAX 10
#define MIN 0



void getInput();
int findMinHours(int n, int m,  int min);

//global variables
int N,M;
int inputs[10][10];
int isUsed[10];

int main(){
  int i,j;

    srand(time(NULL));
    scanf(" %d",&N);
    fflush(stdin);

    // getInput();

    M = MAX;
    for(i=0; i<N; i++){
      for(j=0; j<N; j++){
        inputs[i][j] = rand()%10+1;
        printf("%d ",inputs[i][j]);
      }
      puts("");
    }
    printf("N=%d %d hours\n",N,findMinHours(N, M*N, 0));

  return 0;
}


void getInput()
{
  int i,j;
  scanf("%d %d",&N, &M);
  fflush(stdin);
  for(i=0; i<N; i++){
    for(j=0; j<N; j++){
      scanf("%d",&inputs[i][j]);
    }
  }
}

int findMinHours(int n, int m, int min)
{
  int j, temp;
  int res = m;



  printf("\n------------function with n : %d----------\n", n);

  for(j=0; j<N; j++){
    if(isUsed[j] == 0){ // if available at j
      if(n == 1){ // exit
        return inputs[n-1][j] + min;
      }else{
        isUsed[j] = 1; //check j and pass down
        temp = findMinHours(n-1, m, inputs[n-1][j] + min);
        isUsed[j] = 0; //uncheck

        if(temp < res){
          res = temp;
        }
      }
    }
  }
  if(res == m){
    return min;
  }else
    return res;
}
