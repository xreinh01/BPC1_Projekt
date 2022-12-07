#include "SnakeC.h"
#include "Func.h"
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <string.h>

int main(){
	int quit = 1;

	 // Schovat kurzor
	printf("\033[?25l");
	while (quit!=0) {
		SetConsoleTitle("Had pana Stryka");
		MainMenu();
		switch (getch()) {
		case 's':
			reset();
			system("cls");
			drawSnake();
			while (!game) {
				// Hraci plocha
				drawField();
				movement();
				updateTail();
				appleTime();
				Sleep(difficulty);
				score = length - 2;
			}
			apple = 0;
			system("cls");
			HighScore(score);	
			break;
		case 'a':
			LeaderBoard();
			break;
		case 'q':
			quit = 0;
			break;
		}
	}
	 // Obnovit kurzor
	printf("\033[?25h");

	return 0;
	}

