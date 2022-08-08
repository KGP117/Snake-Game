#include <conio.h>
#include <cstdlib>
#include <iostream>
#include <time.h>
#include <windows.h>
using namespace std;

// Created from tutorial by NVitanovic: https://www.youtube.com/watch?v=E_-lMZDi7Uw

// Sets the playable dimensions of the game
const int width = 20;
const int height = 10;

int x, y;
int fruitX, fruitY;
int score;

int tailX[100], tailY[100];
int sizeTail;

bool gameOver;

// Direction of Snake
enum eDirection {STOP = 0, UP, DOWN, LEFT, RIGHT};
eDirection dir;



void setup(){
	
	gameOver = false;
	
	dir = STOP;

	x = width/2;
	y = height/2;
	
	fruitX = rand() % width;
	fruitY = rand() % height;
	
	score = 0;
	
	return;
}



void draw(){
	
	system("cls");
	//system("clear")
	
	for (int i=0; i<width+2; i++){
		cout << "_";
	}
	cout << endl;
	
	for (int i=0; i<height; i++){
		for (int j=0; j<width; j++){
			
			if (j == 0){
				cout << "|";
			}
			
			if (i==y && j==x){
				cout << "O";
			}
			
			else if (i == fruitY && j == fruitX){
				cout << "x";
			}
			
			else {
				
				bool print = false;
				
				for (int k=0; k<sizeTail; k++){
					
					if (tailX[k] == j && tailY[k] == i){
						cout << "o";
						print = true;
					}
				}
				
				if (!print){
					cout << " ";	
				}
			}
			
			
			if (j == width-1){
				cout << "|";
			}
		}
		cout << endl;
	}
	
	for (int i=0; i<width+2; i++){
		cout << "_";
	}
	
	cout << endl << endl;
	cout << " Score: " << score << endl << endl;
	
	// Slows down the snakes movement
	if (dir == LEFT || dir == RIGHT){
		Sleep(5);
	}
	if (dir == UP || dir == DOWN){
		Sleep(60);
	}
	
	// Makes the walls refresh less
	Sleep(100);
	
	return;
}



void input(){
	
	// Detects keyboard input
	if (_kbhit()){
		
		switch (_getch()){
			
			case'w': 
				dir = UP;
				break;
			
			case's': 
				dir = DOWN;
				break;
				
			case'a': 
				dir = LEFT;
				break;
				
			case'd': 
				dir = RIGHT;
				break;
				
			case'x': 
				gameOver = true;
				break;
		}
	}
	
	return;
}



void logic(){
	
	int prev2X, prev2Y;
	
	int prevX = tailX[0];
	int prevY = tailY[0];
	
	tailX[0] = x;
	tailY[0] = y;

	for (int i=1; i<sizeTail; i++){
		
		prev2X = tailX[i];
		prev2Y = tailY[i];
		
		tailX[i] = prevX;
		tailY[i] = prevY;
		
		prevX = prev2X;
		prevY = prev2Y;
	}
		

	switch (dir){
		
		case UP:
			y--;
			break;
			
		case DOWN:
			y++;
			break;
			
		case LEFT:
			x--;
			break;
			
		case RIGHT:
			x++;
			break;
			
		default:
			break;
	}
	
	if (x > width || x < 0){
		gameOver = true;
	}
	
	if (y > height || x < 0){
		gameOver = true;
	}
	
	for (int i=0; i<sizeTail; i++){
		
		if (tailX[i] == x && tailY[i] == y){
			gameOver = true;
		}
	}
	
	if (x == fruitX && y == fruitY){
		
		fruitX = rand() % width;
		fruitY = rand() % height;
		
		sizeTail++;
		score += 10;
	}
	
	return;
}



int main(){
	
	srand(time(NULL));
	
	setup();
	
	while (!gameOver){
		draw();
		input();
		logic();
		//Sleep(10);
	}
	
	cout << " Game Over!" << endl << endl;
	cout << " ";
	
	system("pause");
	
	main();
	
	return 0;
}
