
#include "dodgeX.h"

int abs(int a){
	if(a < 0)
		return -a;
	return a;
}


int renderEnemy(char* map, Position *enemies, Position user){
	int i;
	int x_diff;
	int y_diff;
	int prob;     //probability
	srand(time(NULL)); //random seed

	for(i = 0; i < ENEMY; i++){   // move enemy
		x_diff = enemies[i].x - user.x;
		y_diff = enemies[i].y - user.y;


		switch(DIFFICULTY){
		case 0:
			prob = 3;
			break;
		case 1:
			prob = 2;
			break;
		case 2:
			prob = 1;
			break;
		default : prob=3; break;
		}

		if(rand()%10 > prob){ // 70~90% prob, chase user
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

		}else{
			switch(rand()%4){ // random direction
			case 0:
				moveCh(1, &enemies[i], map);
				break;
			case 1:
				moveCh(2, &enemies[i], map);
				break;
			case 2:
				moveCh(3, &enemies[i], map);
				break;
			case 3:
				moveCh(4, &enemies[i], map);
				break;
			default : break;
			}
		}
		if(enemies[i].x == user.x && enemies[i].y == user.y) // dead
			return 1;
	}
	return 0;
}
