#include <stdio.h>
#include <stdlib.h> // srand()
#include <time.h> // time()

#define ROW 10
#define COL 40
#define OBSTACLE 10
#define ENEMY 3

typedef struct{
	int x;
	int y;
}Position;

int max(int a, int b);
void renderMap(char* map);
void displayMap(char* map);
int showMenu();
int moveCh(int command, Position* ch, char* map);
int renderEnemy(char* map, Position* enemies, Position user);
Position generateEnemy(char* map);
int gameOver();

int main(){

	int i;
	int dead; // GAME OVER if 1


	char map[ROW][COL];
	Position user = {ROW/2, COL/2};
	Position enemies[ENEMY];
	int menuChoice;

	while(1){ // game setup
		srand(time(NULL)); // random seed
		dead = 0;
		renderMap(&map[0][0]);
		map[user.x][user.y] = 'o'; //initial position
		for(i=0; i<ENEMY; i++){  // generate enemies
			enemies[i] = generateEnemy(&map[0][0]);
		}
		puts("start");
			while(1){ // start game

				displayMap(&map[0][0]);

				if(dead){                    // enemy pos == user pos
					if(gameOver()){ // true if continue
						break;
					}else{
						return 0;
					}
				}

				menuChoice = showMenu();
				if(menuChoice < 1 || menuChoice > 5){
					printf("\r잘못 입력하셨습니다.\n");
				}else if(menuChoice == 5){
					return 0;
				}

				dead = moveCh(menuChoice, &user, &map[0][0]) || renderEnemy(&map[0][0], &enemies[0], user);

			}
		puts("Re-rendering...");
	}

	return 0;
}

int max(int a, int b){
	if(a>b)
		return a;
	return b;
}

void renderMap(char * map){
	int i, j;
	int x, y;

	for(i=0; i<ROW; i++){
		for(j=0; j<COL; j++){
			if(i==0 || j==0 || i==(ROW-1) || j==(COL-1)){
				*(map+(COL)*i+j) = '*';
			}else{
				*(map+(COL)*i+j) = '.';
			}
		}
	}

	// obstacle
	for(i=0; i<OBSTACLE; i++){
		x = rand()%(ROW-2);
		y = rand()%(COL-2);
		*(map+(COL)*x+y) = '*';
	}
	return;
}

void displayMap(char* map){
	int i, j;
	for(i=0; i<ROW; i++){
			for(j=0; j<COL; j++){
				printf("%c",*(map+COL*i+j));
			}
			puts("");
		}
}

int showMenu(){
	int ret = 0;
	while(1){
		printf("\r[왼쪽 : 1] [오른쪽 : 2] [위 : 3] [아래 : 4] [종료 : 5] : ");
		scanf(" %d", &ret);
		if( ret<1 || ret>5 )
			return -1;
		else
			break;
	}
	return ret;
}

int moveCh(int command, Position* ch, char* map){
	int user = 0;
	if(*(map+COL*(ch->x)+ch->y) == 'o')
		user = 1; // user

	*(map+COL*(ch->x)+ch->y) = '.';

	if(command == 1){
		if(*(map+COL*(ch->x)+ch->y-1) != '*')
			ch->y -= 1;
	}else if(command==2){
		if(*(map+COL*(ch->x)+ch->y+1) != '*')
			ch->y += 1;
	}else if(command==3){
		if(*(map+COL*(ch->x-1)+ch->y) != '*')
			ch->x -= 1;
	}else if(command==4){
		if(*(map+COL*(ch->x+1)+ch->y-1) != '*')
			ch->x += 1;
	}

	if(user)
		if(*(map+COL*(ch->x)+ch->y) == 'x')
			return 1;
		else
			*(map+COL*(ch->x)+ch->y) = 'o';
	else{
		if(*(map+COL*(ch->x)+ch->y) == 'o')
			return 1;
		else
			*(map+COL*(ch->x)+ch->y) = 'x';
	}
	return 0;
}

int renderEnemy(char* map, Position *enemies, Position user){
	int i;
	int x_diff;
	int y_diff;
	for(i = 0; i < ENEMY; i++){
		x_diff = enemies[i].x - user.x;
		y_diff = enemies[i].y - user.y;
		// Hard version
		if(abs(y_diff) > abs(x_diff)){
			if(y_diff >0)

				moveCh(1, &enemies[i], map);
			else

				moveCh(2, &enemies[i], map);
		}else{
			if(x_diff >0)

				moveCh(3, &enemies[i], map);
			else

				moveCh(4, &enemies[i], map);
		}
		if(enemies[i].x == user.x && enemies[i].y == user.y)
			return 1;
	}
	return 0;
}

Position generateEnemy(char* map){
	Position enemy= {0, 0};
	while(1){
		enemy.x = rand()%(ROW-2) + 1;
		enemy.y = rand()%(COL-2) + 1;
		if(*(map+COL*enemy.x+enemy.y) == '.'){  //  only in empty field
			*(map+COL*enemy.x+enemy.y) = 'x';
			return enemy;
			break;
		}
	}
}

int gameOver(){
	char input;
	printf("\rGAME OVER. Continue? (Y/N) : ");
	fflush(stdin);
	input = getchar();

	if(input == 'y' || input == 'Y')
		return 1;
	else
		return 0;
}
