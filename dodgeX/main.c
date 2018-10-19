#include <stdlib.h>
#include <conio.h>
#include "dodgeX.h"

int charToInt(char c);
int max(int a, int b);
void renderMap(char* map);
void displayMap(char* map);
int showMenu();
int moveCh(int command, Position* ch, char* map);
int renderEnemy(char* map, Position* enemies, Position user);
void renderBonus(char* map, Position* bonuses);
void removeBonus(Position user, int i);
Position generateEnemy(char* map);
int gameOver();

static unsigned int moves = 0;
static unsigned int currScore = 0;
static int n_bonus = 0;
static int bestScore;

int main(){

	int i;
	int dead; // GAME OVER if 1

	char map[ROW][COL];
	Position user = {ROW/2, COL/2};
	Position enemies[ENEMY];
	Position bonuses[BONUS];
	int menuChoice;
	bestScore = loadBest();
	if(bestScore <0){ // no file
		saveBest(0);
		bestScore = 0;
		fprintf(stderr,"Failed to load best score. Continue? (press Enter)");
		getchar();
		fflush(stdin);
	}


	while(1){ // game setup
		srand(time(NULL)); // random seed
		dead = 0;
		renderMap(&map[0][0]);
		user.x = ROW/2;
		user.y = COL/2;
		map[user.x][user.y] = 'o'; //initial position

		for(i=0; i<ENEMY; i++){  // generate enemies
			enemies[i] = generateEnemy(&map[0][0]);
		}
		for(i=0; i<BONUS; i++){
			bonuses[i].x = 0;
			bonuses[i].y = 0;
		}
		n_bonus = 0;
		moves = 0;
		currScore = 0;
		renderBonus(&map[0][0], bonuses);


		puts("*** Game Started ***");
			while(1){ // start game
				system("cls");
				displayMap(&map[0][0]);

				if(dead){                    // enemy pos == user pos
					if(gameOver()){ // true if continue
						break;
					}else{
						if(saveBest(bestScore)){
							fprintf(stderr, "Failed to save best score\n");
						}
						fflush(stdin);
						printf("Press Enter to Exit");
						getchar();
						return 0;
					}
				}

				menuChoice = showMenu();
				if(menuChoice < 1 || menuChoice > 5){
					printf("\r잘못 입력하셨습니다.\n");
					continue;
				}else if(menuChoice == 5){
					dead = 1;
					continue;
				}

				dead = moveCh(menuChoice, &user, &map[0][0]) || renderEnemy(&map[0][0], &enemies[0], user);
				moves += 1;
				if(n_bonus < BONUS)
					renderBonus(&map[0][0], bonuses);

			}
		puts("Re-rendering...");
	}

	return 0;
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
		do{
			x = rand()%(ROW-2);
			y = rand()%(COL-2);
		}while(((x == ROW/2) && (y == COL/2)) || *(map+(COL)*x+y) == '*'); // user or obstacle

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
	if(bestScore<currScore)
		bestScore = currScore;
	printf("Moves : %u, Score : %u, Best Score : %u\n", moves, currScore, bestScore);
}

int showMenu(){
	char input;
	while(1){
		printf("\r[왼쪽 : 1, a] [오른쪽 : 2, d] [위 : 3, w] [아래 : 4, s] [자살 : 5] : ");
		fflush(stdin);
//		input = getchar();
		while(1){
			if (kbhit()){
				input = getch();
				break;
			}
		}

		if(input == 'a')
			return 1;
		if(input == 's')
			return 4;
		if(input == 'd')
			return 2;
		if(input == 'w')
			return 3;

		if( input<'1' || input>'5' ){
			fflush(stdin);
			return -1;
		}
		else
			break;
	}
	return input-48;
}

int moveCh(int command, Position* ch, char* map){
	int user = 0;
	int infFlag;
	if(*(map+COL*(ch->x)+ch->y) == 'o')
		user = 1; // user

	*(map+COL*(ch->x)+ch->y) = '.';
	if(user){
		if(command == 1){
			if(*(map+COL*(ch->x)+ch->y-1) != '*'){
				if(*(map+COL*(ch->x)+ch->y-1) == '$'){
					n_bonus--;
					currScore++;
				}
				ch->y -= 1;
			}
		}else if(command==2){
			if(*(map+COL*(ch->x)+ch->y+1) != '*'){
				if(*(map+COL*(ch->x)+ch->y+1) == '$'){
					n_bonus--;
					currScore++;
				}
				ch->y += 1;
			}
		}else if(command==3){
			if(*(map+COL*(ch->x-1)+ch->y) != '*'){
				if(*(map+COL*(ch->x-1)+ch->y) == '$'){
					n_bonus--;
					currScore++;
				}
				ch->x -= 1;
			}
		}else if(command==4){
			if(*(map+COL*(ch->x+1)+ch->y) != '*'){
				if(*(map+COL*(ch->x+1)+ch->y) == '$'){
					n_bonus--;
					currScore++;
				}
				ch->x += 1;
			}
		}
	} else{
		infFlag = 0;
		while(1){
			if(command == 1){
				if(*(map+COL*(ch->x)+ch->y-1) != '*'){
					ch->y -= 1;
					break;
				}
				command = 2;
				infFlag++;
			}else if(command==2){
				if(*(map+COL*(ch->x)+ch->y+1) != '*'){
					ch->y += 1;
					break;
				}
				command = 3;
				infFlag++;
			}else if(command==3){
				if(*(map+COL*(ch->x-1)+ch->y) != '*'){
					ch->x -= 1;
					break;
				}
				command = 4;
				infFlag++;
			}else if(command==4){
				if(*(map+COL*(ch->x+1)+ch->y-1) != '*'){
					ch->x += 1;
					break;
				}
				command = 1;
				infFlag++;
			}
			if(infFlag > 3){
				infFlag = 0;
				break;
			}
		}
	}

	//DEBUG PURPOSE
	if(*(map+COL*(ch->x)+ch->y) == '*'){ // current location is on obstacle
		*(map+COL*(ch->x)+ch->y) = '#';
		return 0;
	}
	//DEBUG PURPOSE END

	if(user)
		if(*(map+COL*(ch->x)+ch->y) == 'x')
			return 1;
		else
			*(map+COL*(ch->x)+ch->y) = 'o';
	else{ //enemy
		if(*(map+COL*(ch->x)+ch->y) == 'o')
			return 1;
		else
			*(map+COL*(ch->x)+ch->y) = 'x';
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

void renderBonus(char* map, Position* bonuses){
	int i = 0;
	while(i<BONUS){
		if(*(map+COL*bonuses[i].x+bonuses[i].y) == '$'){ // if already a bonus
			i++;//next bonus
			continue;
		}
		bonuses[i].x = rand()%(ROW-2) +1;
		bonuses[i].y = rand()%(COL-2) +1;
		if(*(map+COL*bonuses[i].x+bonuses[i].y) == '.'){
			*(map+COL*bonuses[i].x+bonuses[i].y) = '$';
		}else{
			continue; // re-run
		}
		i++; // next bonus
	}
	return;
}

int gameOver(){
	char input;
	while(1){
		if(bestScore < currScore)
			bestScore = currScore;
		printf("GAME OVER. Continue? (Y/N) : ");
		fflush(stdin);
		input = getchar();

		if(input == 'n' || input == 'N')
			return 0;
		else if(input == 'y' || input == 'Y')
			return 1;
		else
			printf("Wrong Input!\n");
	}
}

int max(int a, int b){
	if(a>b)
		return a;
	return b;
}
