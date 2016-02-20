// main.c
// snake
//
//Created by Jianjie Luo on 15-12-27
// this edition can go , accelerate.
// compared with 4.0, it can impove the direction-changed bug

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#include<windows.h>

#define SNAKE_MAX_LENGTH 20
#define SNAKE_HEAD 'H'
#define SNAKE_BODY 'X'
#define BLANK_CELL ''
#define SNAKE_FOOD '$'
#define WALL_CELL '*'

// snake stepping: dy = -1(up) 1(dowm) 0(no move); dx = -1(left), 1(right), 0(no move)
void snakemove(int, int); //to write dowm the current location of the snake 
void put_money(void); 
void output(void); // to put the current map on the pingmu
void initial_the_game(void);
void put_accelerate(void);// @ is a special food which can speed up your snake.
int judge(int, int);  // when it comes to ai, it is used to judge whether the next step is movable.
int dis(int, int);  // when it coomes to ai, it is used to calculate the current distence between the snake head and the food.
void welcome(void);  //  the game introduction.
void gameover(void);  
void edition_handed(void);   // the edition in which you can play by yourself.
void edition_presentation(void);  // the edition in which the snake can go automatically.

char map[12][12] = 
    {"************",
    "*XXXXH     *",
    "*          *",
    "*          *",
    "*          *",
    "*          *",
    "*     $    *",
    "*          *",
    "*   @      *",
    "*          *",
    "*          *",
    "************"};
	
// define vars for snake,notice name of vars in c 
int snakeX[SNAKE_MAX_LENGTH] = {1, 2, 3, 4, 5};
int snakeY[SNAKE_MAX_LENGTH] = {1, 1, 1, 1, 1};
int snakeLength = 5;
int gamestate = 1;
int current_speed = 600;
int score = 0;
char edition_choose; // for player to choose the edition.
int con = 1; // to judge the initial state of the game;
int energy = 0; // write down the condition to accelerate by eating $.

//the following part is to realize the simple ai .
const char movable[4] = {'a', 'd', 's', 'w'};
int distance[4] = {9999, 9999, 9999, 9999};
int fx = 6, fy = 6; // the coordinate of the food $

int main() {
	while (con) {
	    welcome();
	    int flag = 1;
	    while (flag) {
        	edition_choose = getch();  //choose the edition
	        if (edition_choose == 'h') {
	            edition_handed();
	            flag = 0;
	        }
        	else if (edition_choose == 'p') {
	            edition_presentation();
	            flag = 0;
	        }
        	else {
	            printf("Please press the correct bottom -,- ...\n");
	        }
		}
	    gameover();
    }  
    return 0;
}
    
void edition_handed(void) {
	system("cls");
    output();
	char ch = 'd';
   	while (gamestate) {
		switch (ch) {
		    case 'a': // go left
		    	while (1) {
			    	snakemove(-1, 0);
		        	Sleep(current_speed);
		       		if (gamestate == 0) // to break the loop if the snake hit the wall or itself.
		       		    break;
		       		if (kbhit() != 0) { // to change the direction
					    ch = getch();
					if (ch == 's' || ch == 'w')
					    break;
				    else 
				        ch = 'a';
					}
		        }
		        break;
			case 'd': // go right
	    		while (1) {
			        snakemove(1, 0);
		        	Sleep(current_speed);
		        	if (gamestate == 0)
		        	    break;
		        	if (kbhit() != 0)
					    ch = getch();
					if (ch == 's' || ch == 'w')
					    break;
				    else 
				        ch = 'd';
		        } 
		        break;
			case 's': // go down
				while (1) {
			        snakemove(0, 1);
		        	Sleep(current_speed);
		        	if (gamestate == 0)
		        	    break;
		        	if (kbhit() != 0)
						ch = getch();
					if (ch == 'a' || ch == 'd')
					    break;
				    else 
				        ch = 's';
		        }
		        break;
	    	case 'w': // go up
		        while (1) {
			   	    snakemove(0, -1);
		       		Sleep(current_speed);
		       		if (gamestate == 0)
		       		    break;
		        	if (kbhit() != 0)
					    ch = getch();
					if (ch == 'a' || ch == 'd')
					    break;
				    else 
				        ch = 'w';
		        }
		        break;
	    }
	    if (gamestate == 0)
	        break;
    } 
	return;
}

void welcome(void) {   // just for some introduction
	printf("WELCOME TO THE SNAKE'S WORLD !!!!\n");
	printf("\n");
	printf("\n");
	printf("Please choose the edition you want.\n");
	printf("\n");
	printf("\n");
	printf("The 'h' is for the hand-operated and the 'p' is for the simple presentation\n");
	printf("\n");
	printf("\n");
	printf("Attention:  the presentation still has a liitle bug, while it can be moving right for a period of time...\n ");
	return;
}

void gameover(void) { // give you some introduction when you lose the game.
	system("cls");
    printf("Game over!!!\n");
    printf("Do you want to continue? y or n\n");
    char start; // in order to judge whether you still want to play the game.
    while (1) {
	    start = getch();
        if (start == 'y') {
        	system("cls");
        	initial_the_game();
		    break;
	    } else if (start == 'n') {
	    	system("cls");
	    	con = 0;  // in order to let the game end.
	    	printf("See you next time!  ^-^\n");
	    	break;
	    } else {
	    	printf("Please press the correct buttom.\n");
		}
   	}
}

void output(void) { // put the cuttent game map.
	printf("THE INTERESTING SNAKE GAME CREATED BY LONGJ =,=\n");
	printf("use w~s~a~d to control the snake's movement\n");
	printf("ATTENTION: the @ can speed up your lovely snake~~\n");
	int i, j;
	for (i = 0; i < 12; i++) {
		for (j = 0; j < 12; j++) {	
		    printf("%c", map[i][j]);
		    if (j == 11)
		        printf("\n");
	    }
	}
	printf("Your current_speed is %d\n", current_speed);
	printf("The number of your food undigested is %d  (when it comes to 5, your speed will be accelerated!) \n", energy);
	printf("SCORE = %d\n", score);
	return;
}

void snakemove(int dx, int dy) { // all the conditions are comparing the head and the next position.
	int i;
	if (snakeY[snakeLength - 1] + dy == snakeY[snakeLength - 2] && snakeX[snakeLength - 1] + dx == snakeX[snakeLength - 2])
		return;  // to prevent it go to itslef.
	if (map[snakeY[snakeLength - 1] + dy][snakeX[snakeLength - 1] + dx] == 'X') {
	    gamestate = 0;
	    return;
	}
	if (map[snakeY[snakeLength - 1] + dy][snakeX[snakeLength - 1] + dx] == '*') {
	    gamestate = 0;
	    return;
    }
	if (map[snakeY[snakeLength - 1] + dy][snakeX[snakeLength - 1] + dx] == ' '
	    || map[snakeY[snakeLength - 1] + dy][snakeX[snakeLength - 1] + dx] == '@') {
		map[snakeY[0]][snakeX[0]] = ' '; // clear the former_tail
		if (map[snakeY[snakeLength - 1] + dy][snakeX[snakeLength - 1] + dx] == '@'
		&& current_speed > 100) {  // what will happen when your snake eats the @
		    current_speed -= 100;
		    put_accelerate();
	    }
    	for (i = 0; i < snakeLength - 1; ++i) {
    		snakeX[i] = snakeX[i + 1];
    		snakeY[i] = snakeY[i + 1];
    	}
        snakeX[snakeLength - 1] += dx;
    	snakeY[snakeLength - 1] += dy;
    	for (i = 0; i < snakeLength - 1; i++) // write down the current snake location
    		map[snakeY[i]][snakeX[i]] = 'X';
    	map[snakeY[snakeLength - 1]][snakeX[snakeLength - 1]] = 'H';
    }
    if (map[snakeY[snakeLength - 1] + dy][snakeX[snakeLength - 1] + dx] == '$') {
    	map[snakeY[snakeLength - 1]][snakeX[snakeLength - 1]] = 'X';
    	snakeLength++;
    	snakeX[snakeLength - 1] = snakeX[snakeLength - 2] + dx;
    	snakeY[snakeLength - 1] = snakeY[snakeLength - 2] + dy;
    	map[snakeY[snakeLength - 1]][snakeX[snakeLength - 1]] = 'H';
    	score++;
    	energy++;
    	if (energy == 5 && current_speed > 50) {
    		current_speed -= 50;
    		energy = 0;
		}
    	put_money();
	}
	system("cls");
	output();
	return;
}

void put_money(void) {  /// ai will change the code
	int flag = 1;
	while (flag) {
    	srand(time(NULL));
    	fx = rand() % 12;
	    fy = rand() % 12;
	    if (map[fy][fx] == ' ') {
	        map[fy][fx] = '$';
	        flag = 0;
    	}
    	if (edition_choose == 'p') {
    	    int i;
    	    for (i = 0; i< 4; i++)
    		    distance[i] = 9999;
        }
    }
    return;
}

void put_accelerate(void) {
	int x, y, flag = 1;
	while (flag) {
    	srand(time(NULL));
    	x = rand() % 12;
	    y = rand() % 12;
	    if (map[x][y] == ' ') {
	        map[x][y] = '@';
	        flag = 0;
    	}
    }
    return;
}

void initial_the_game(void) {
    int i, j, count = 1;
    snakeLength = 5;
    gamestate = 1;
    fx = fy = 6;
    current_speed = 600;
    for (i = 0; i < 5; i++)
        snakeY[i] = 1;
    for (i = 0; i < 5; i++) {
    	snakeX[i] = count++;
	}
    for (j = 0; j < 12; j++) {
        map[0][j] = '*';
        map[11][j] = '*';
    }
    for (i = 1; i < 11; i++) {
    	map[i][0] = map[i][11] = '*';
    	for (j = 1; j < 11; j++)
    		map[i][j] = ' ';
	}
	map[fy][fx] ='$';
	map[8][4] = '@';
	for (i = 0; i< 4; i++) {
    		distance[i] = 9999;
	}
	for (i = 0; i < 4; i++) 
	    map[snakeY[i]][snakeX[i]] = 'X';
	map[snakeY[4]][snakeX[4]] = 'H';
	return;
}

int dis(int dx, int dy) {
	return abs(fx - snakeX[snakeLength - 1] - dx) + abs(fy - snakeY[snakeLength - 1] - dy);
}

int judge(int dx, int dy) {
	if (map[snakeY[snakeLength - 1] + dy][snakeX[snakeLength - 1] + dx] == ' ')
        return 1;
    else if (map[snakeY[snakeLength - 1] + dy][snakeX[snakeLength - 1] + dx] == '$')
        return 1;
    else if (map[snakeY[snakeLength - 1] + dy][snakeX[snakeLength - 1] + dx] == '@')
        return 1;
    else 
        return 0;
}

void edition_presentation(void) { // for ai
    system("cls");
	int i, min = 10000;
    output();
	char ch;
	char quit = 'o';
	int k;
    while (gamestate) { // find the shortest way;
        min = 10000;
	    if (judge(-1, 0)) distance[0] = dis(-1, 0);
	    if (judge(1, 0)) distance[1] = dis(1, 0);
	    if (judge(0, 1)) distance[2] = dis(0, 1);
	    if (judge(0, -1)) distance[3] = dis(0, -1);
 		for (i = 0; i < 4; i++) {
			if (min >= distance[i]) {
				min = distance[i];
				k = i;
	    	}
	 	}
	 	Sleep(current_speed);
	    switch (movable[k]) {
		    case 'a': // go left
			    snakemove(-1, 0);
		    	break;
			case 'd': // go right
	    		snakemove(1, 0);
		    	break;
			case 's': // go down
				snakemove(0, 1);
    			break;
	    	case 'w': // go up
		    	snakemove(0, -1);
			    break;	
	   	}
	    if (gamestate == 0)
		    break;
	 	system("cls");
	    	output();
	}
	return;
}

