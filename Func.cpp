#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <string.h>
#include "Func.h"

int field[WIDTH][HEIGHT], x, y, tempx, head = 0, tail = 0, length = 2, dir = 5, ch, apple, applex, appley, difficulty = 100, score = 0, game = 0;

// Hraci plocha
void drawField() {

	for (int j = -1; j < HEIGHT; j++) {
		for (int i = -1; i < WIDTH; i++) {
			if (field[i][j] == -2) printf("#");
			if (field[i][j] == 0) printf(" ");
			if (field[i][j] > 0 && field[i][j] != head) printf("x");   // Tiskne telo hada
			if (field[i][j] == head) printf("0");   // Hlava hada
			if (field[i][j] == -1) printf("P");
		}
		printf("\n");
	}

	// Dolni okraj

	printf("\n");
	printf("score: %d", score);
	printf("\n");


	// Vrati kurzor na zacatek - plocha se vykresli v konzoli na samem miste
	printf("\033[%iA", HEIGHT + 3);
}

void drawSnake() {
	for (int i = -1; i < WIDTH; i++) {
		int j = 0;
		field[i][j] = -2;
	}

	for (int j = 0; j < HEIGHT; j++) {
		int i = -1;
		field[i][j] = -2;
		for (int i = 0; i < WIDTH; i++) {
			field[i][j] = 0;
		}
		i = WIDTH - 1;
		field[i][j] = -2;
	}

	// Dolni okraj
	for (int i = 0; i < WIDTH; i++) {
		int j = HEIGHT - 1;
		field[i][j] = -2;
	}

	x = WIDTH / 2;
	y = HEIGHT / 2;

	tempx = x;
	
	for (int i = 0; i < head; i++) {
		tempx++;
		field[tempx - head][y] = i + 1;

	}
}

void appleTime() {
	if (apple == 0) {
		srand(time(0));
		applex = 1 + rand() % (WIDTH - 2);
		appley = 1 + rand() % (HEIGHT - 2);

		if (field[applex][appley] == 0) {
			field[applex][appley] = -1;
			apple = 1;
		}
	}
	if (x == applex && y == appley) {
		apple = 0;
		length++;
		if (length % 3 > 0) {
			if (difficulty >= 50) difficulty = difficulty - 10;
		}
	}
}

int returnLastKeyInput() {
	if (_kbhit()) {
		if (ch = getch() == 224) {
			switch (getch()) {
			case 72:
				ch = 1;
				break;
			case 80:
				ch = 2;
				break;
			case 75:
				ch = 4;
				break;
			case 77:
				ch = 5;
				break;
			}
			return ch;
		}
	}
	else
		return -1;
}

void movement() {
	int var = returnLastKeyInput();

	if ((var != -1) && abs(dir - var) > 1) dir = var;
	if (dir == 1) {
		y--;
		head++;
		if (field[x][y] == -2 || (field[x][y] < head - 1 && field[x][y] != 0 && field[x][y] != -1))
			game = 1;
		field[x][y] = head;
	}
	if (dir == 4) {
		x--;
		head++;
		if (field[x][y] == -2 || (field[x][y] < head - 1 && field[x][y] != 0 && field[x][y] != -1))
			game = 1;
		field[x][y] = head;
	}
	if (dir == 2) {
		y++;
		head++;
		if (field[x][y] == -2 || (field[x][y] < head - 1 && field[x][y] != 0 && field[x][y] != -1))
			game = 1;
		field[x][y] = head;
	}
	if (dir == 5) {
		x++;
		head++;
		if (field[x][y] == -2 || (field[x][y] < head - 1 && field[x][y] != 0 && field[x][y] != -1))
			game = 1;
		field[x][y] = head;
	}
}

// Udrzuje delku hada
void updateTail() {
	for (int i = 0; i < WIDTH; i++) {
		for (int j = 0; j < HEIGHT; j++) {
			if (field[i][j] == tail) {
				field[i][j] = 0;
			}
		}
	}
	tail = head - length;
}

void HighScore(int score) {
	char plname[20] = "";
	FILE* Data;
	Data = fopen("HighScores.txt", "a+");
	printf("Zadejte jmeno hrace\n");
	gets_s(plname);
	if (strcmp(plname, "") != 0) {
		fprintf(Data, "\n%s: %d", plname, score);
		fclose(Data);
	}
	fclose(Data);
}

void LeaderBoard() {
	system("cls");
	FILE* SortFile;
	fopen_s(&SortFile, "HighScores.txt", "r+");
	struct score* newScore;
	struct score* pointer = NULL;
	struct score* firstScore = NULL;
	char Line[32];

	while (!feof(SortFile)) {
		newScore = (struct score*)malloc(sizeof(struct score));

		fscanf(SortFile, "%[^:]s", Line, 32);
		strcpy_s(newScore->name, 32, Line);
		fscanf(SortFile, "%s", Line, 32);
		fscanf(SortFile, "%[^\n]s", Line, 32);
		newScore->score = atoi(Line);
		newScore->next = NULL;


		if (firstScore == NULL) {
			firstScore = newScore;
		}
		else if (newScore->score > firstScore->score) {
			newScore->next = firstScore;
			firstScore = newScore;
		}
		else {

			pointer = firstScore;
			while (pointer) {
				if (pointer->next == NULL || pointer->next == pointer) {
					pointer->next = newScore;
					pointer = pointer->next;
					break;
				}
				else if (newScore->score > pointer->next->score) {
					newScore->next = pointer->next;
					pointer->next = newScore;
					break;
				}
				pointer = pointer->next;
			}
		}
	}
	int counter = 0;
	freopen("HighScores.txt", "w", SortFile);
	fseek(SortFile, 0, SEEK_SET);
	while (firstScore && counter < 10) {
		printf("\n%s: %d", firstScore->name, firstScore->score);
		fprintf(SortFile, "%s:", firstScore->name);
		fprintf(SortFile, " %d", firstScore->score);
		firstScore = firstScore->next;
		counter++;
	}
	fclose(SortFile);
	getch();
}

void reset() {
	game = 0;
	dir = 5;
	score = 0;
	head = 3;
	length = 2;
	tail = head - length;
	difficulty = 160;
}

void MainMenu() {
	system("cls");
	printf("          SNAKE          ");
	printf("\n for Start press S");
	printf("\n for HighScores press A");
	printf("\n for Quit press Q");
}