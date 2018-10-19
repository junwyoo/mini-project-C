#ifndef DODGEX_H_
#define DODGEX_H_

#include <stdio.h>
#include <stdlib.h> // srand()
#include <time.h> // time()

#define ROW 10
#define COL 40
#define OBSTACLE 10
#define ENEMY 3
#define BONUS 5
#define DIFFICULTY 0 // 0 ~ 2


typedef struct{
	int x;
	int y;
}Position;

int renderEnemy(char* map, Position *enemies, Position user);
int moveCh(int command, Position* ch, char* map);
int loadBest();
int saveBest(int n);

#endif // #ifndef DODGEX_H_
